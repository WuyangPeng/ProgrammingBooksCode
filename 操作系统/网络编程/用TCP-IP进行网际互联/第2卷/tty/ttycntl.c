/* ttycntl.c - ttycntl */

#include <conf.h>
#include <kernel.h>
#include <tty.h>

/*------------------------------------------------------------------------
 * ttycntl - control function for TTY pseudo devices
 *------------------------------------------------------------------------
 */
int
ttycntl(struct devsw *pdev, int func, void *arg1, void *arg2)
{
	struct tty	*ptty = (struct tty *)pdev->dvioblk;
	unsigned char	ch;
	STATWORD	PS;

	switch (func) {
	case TTC_CPID:	ptty->tty_cpid = (int) arg1;
			return OK;
	case TTC_SYNC:	if (arg1)
				ptty->tty_oflags |= TOF_SYNC;
			else
				ptty->tty_oflags &= ~TOF_SYNC;
			return OK;
	case TTC_GIF:	return ptty->tty_iflags;
	case TTC_GOF:	return ptty->tty_oflags;
	case TTC_NEXTC:
			disable(PS);
			wait(ptty->tty_isema);
			ch = ptty->tty_in[ptty->tty_istart];
			signal(ptty->tty_isema);
			restore(PS);
			return ch;
	case TTC_SUSER:
			ptty->tty_uid = (int) arg1;
			gettime(&ptty->tty_ltime);
			ptty->tty_ctime = ptty->tty_ltime;
			return OK;
	case TTC_CUSER:
			ptty->tty_uid = -1;
			return OK;
	case TTC_MODER:		/* RAW input */
	  		ptty->tty_iflags |= TIF_RAW;
	  		ptty->tty_iflags &= ~TIF_CBREAK;
	  		ptty->tty_iflags |= TIF_NOECHO; /* disable echo */
			return OK;
	case TTC_MODEC:		/* COOKED input */
	  		ptty->tty_iflags &= ~TIF_RAW;
	  		ptty->tty_iflags &= ~TIF_CBREAK;
	  		ptty->tty_iflags &= ~TIF_NOECHO; /* enable echo */
			return OK;
	case TTC_MODEK:		/* CBREAK input */
	  		ptty->tty_iflags |= TIF_CBREAK;
	  		ptty->tty_iflags &= ~TIF_RAW;
	  		ptty->tty_iflags &= ~TIF_NOECHO; /* enable echo */
			return OK;
	}
	return SYSERR;
}
