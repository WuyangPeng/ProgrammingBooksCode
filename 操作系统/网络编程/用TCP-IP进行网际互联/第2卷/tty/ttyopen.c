/* ttyopen.c - ttyopen */

#include <conf.h>
#include <kernel.h>
#include <tty.h>

/*------------------------------------------------------------------------
 * ttyopen - associate a tty with a hardware device
 *------------------------------------------------------------------------
 */
int
ttyopen(struct devsw *pdev, void *dvnum0, void *unused)
{
	int		dvnum = (int)dvnum0;
	struct tty	*ptty, *ttynew();

	if (pdev->dvioblk) {	/* already open */
		ptty = (struct tty *)pdev->dvioblk;
		if (ptty->tty_iflags & TIF_EXCLUSIVE)
			return SYSERR;
		else
			return OK;
	}
	ptty = ttynew();
	if (ptty == 0)
		return SYSERR;
	pdev->dvioblk = (char *)ptty;
	ptty->tty_pdev = (struct devsw *)pdev;
	ptty->tty_phw = (struct devsw *) &devtab[dvnum];
	devtab[dvnum].dvioblk = (char *)pdev;
	ptty->tty_iflags = ptty->tty_oflags = 0;
	ptty->tty_uid = -1;
	return OK;
}
