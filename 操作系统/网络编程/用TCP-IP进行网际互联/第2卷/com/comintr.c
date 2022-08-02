/* comintr.c -- comintr */

#include <conf.h>
#include <kernel.h>
#include <tty.h>
#include <com.h>
#include <sem.h>

unsigned char	inb(void *);
void		outb(void *, unsigned char);

/*------------------------------------------------------------------------
 *  comintr -- handle a serial line interrupt
 *------------------------------------------------------------------------
 */
void
comintr(void)
{
	STATWORD	ps;
	struct devsw	*pdev;
	unsigned char	iir;
	int		i;

	disable(ps);
	for (i=0; i<Nserial; ++i) {
		pdev = comtab[i].com_pdev;
		iir = inb(pdev->dvcsr + IIR);
		if (iir & IIR_NOINT)
			continue;
		break;
	}
	if (i < Nserial)
		switch (iir & IIR_IID) {
		case	IID_RSTAT:	(void) inb(pdev->dvcsr + LSR);
					break;
		case	IID_MSTAT:	(void) inb(pdev->dvcsr + MSR);
					break;
		case	IID_RDAT:	comiin(&comtab[i]);
					break;
		case	IID_THRE:	comwstrt(&comtab[i]);
					break;
		}
	restore(ps);
}

void
comwstrt(struct comsoft *pcom)
{
	void	*csr;

	if (pcom->com_count == 0)
		return;
	csr = pcom->com_pdev->dvcsr;

	if (inb(csr+LSR) & LSR_THRE) {
		outb(csr+IER, 0xf);
		outb(csr+DATA, pcom->com_buf[pcom->com_start]);
		pcom->com_count--;
		pcom->com_start++;
		if (pcom->com_start >= COMBUFSZ)
			pcom->com_start = 0;
		signal(pcom->com_osema);
	}
}
