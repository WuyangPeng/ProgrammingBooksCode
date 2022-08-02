/* comoutput.c - computc, comwrite */

#include <conf.h>
#include <kernel.h>
#include <tty.h>
#include <com.h>    
#include <sem.h>

unsigned char inb(void *);
void outb(void *, unsigned char);

/*------------------------------------------------------------------------
 *  computc - write one character to the PC physical monitor
 *------------------------------------------------------------------------
 */
int
computc(struct devsw *pdev, unsigned char c)
{
	STATWORD	ps;
	struct devsw	*pttydev;
	struct comsoft	*pcom = &comtab[pdev->dvminor];
	struct tty	*ptty = 0;
	int		pos, rv;

	disable(ps);
	if (pttydev = (struct devsw *)pdev->dvioblk)
		ptty = (struct tty *) pttydev->dvioblk;
	if (ptty && (ptty->tty_oflags & TOF_SYNC)) {
/*		comflush(pdev); */
		rv = comsputc(pdev, c);
		restore(ps);
		return rv;
	}
	wait(pcom->com_osema);
	if (c == '\n') {
		wait(pcom->com_osema);	/* need 2 for \r\n */
		pos = pcom->com_start + pcom->com_count;
		if (pos >= COMBUFSZ)
			pos -= COMBUFSZ;
		pcom->com_buf[pos] = '\r';
		pcom->com_count++;
		++pos;
	} else
		pos = pcom->com_start + pcom->com_count;
	if (pos >= COMBUFSZ)
		pos -= COMBUFSZ;
	pcom->com_buf[pos] = c;
	pcom->com_count++;
	comwstrt(&comtab[pdev->dvminor]);
	restore(ps);
	return OK;
}

/*------------------------------------------------------------------------
 * comflush - flush output buffer synchronously
 *------------------------------------------------------------------------
 */
int
comflush(struct devsw *pdev)
{
	struct comsoft	*pcom = &comtab[pdev->dvminor];
	void		*csr = pdev->dvcsr;
	int		ier;

	ier = inb(csr + MCR);
	ier &= ~IER_TX;
	outb(csr + IER, ier);
	while (pcom->com_count) {
		while ((inb(csr+LSR) & LSR_THRE) == 0)
			/* empty */;
		outb(csr+DATA, pcom->com_buf[pcom->com_start]);
		pcom->com_start++;
		if (pcom->com_start >= COMBUFSZ)
			pcom->com_start = 0;
		pcom->com_count--;
		signal(pcom->com_osema);
	}
	ier = inb(csr + MCR);
	ier |= IER_TX;
	outb(csr + IER, ier);
	return OK;
}

/*------------------------------------------------------------------------
 * comsputc - do synchronous putc to a com device
 *------------------------------------------------------------------------
 */
int
comsputc(struct devsw *pdev, unsigned char c)
{
	void		*csr = pdev->dvcsr;

	while ((inb(csr+LSR) & LSR_THRE) == 0)
		/* empty */;
	outb(csr+DATA, c);
	if (c == '\n') {
		while ((inb(csr+LSR) & LSR_THRE) == 0)
			/* empty */;
		outb(csr+DATA, '\r');
	}
	return OK;
}


/*------------------------------------------------------------------------
 *  comwrite - write to the PC physical monitor
 *------------------------------------------------------------------------
 */
int
comwrite(struct devsw *pdev, unsigned char *buf, unsigned count)
{
	if (count == 0)
		return OK;

	for (; count>0 ; count--)
		computc(pdev, *buf++);
	return OK;
}
