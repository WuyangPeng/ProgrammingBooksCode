/* ttyread.c - ttyread */

#include <conf.h>
#include <kernel.h>
#include <tty.h>

/*------------------------------------------------------------------------
 * ttyread - read characters from a tty
 *------------------------------------------------------------------------
 */
int
ttyread(struct devsw *pdev, char *buf, unsigned len)
{
	STATWORD	ps;
	struct tty	*ptty = (struct tty *)pdev->dvioblk;
	unsigned	count;

	if (ptty->tty_state != TTYS_ALLOC)
		return SYSERR;
	if ((ptty->tty_iflags & TIF_EOF) && ptty->tty_icount == 0) {
		ptty->tty_iflags &= ~TIF_EOF;
		return EOF;
	}
	if (ptty->tty_iflags & TIF_NOBLOCK)
		if (scount(ptty->tty_isema) <= 0)
			return SYSERR;
	disable(ps);
	wait(ptty->tty_isema);
	count = 0;
	while (count < len && ptty->tty_icount) {
		*buf++ = ptty->tty_in[ptty->tty_istart];
		count++;
		ptty->tty_icount--;
		ptty->tty_istart++;
		if (ptty->tty_istart >= IBLEN)
			ptty->tty_istart = 0;
	}
/* wakeup other readers here */
	restore(ps);
	gettime(&ptty->tty_ctime);
	return count;
}
