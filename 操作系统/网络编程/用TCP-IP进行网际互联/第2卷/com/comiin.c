/* comiin.c comiin */

#include <conf.h>
#include <kernel.h>
#include <tty.h>
#include <com.h>

static	int	state;
unsigned char	inb(void *);

/*------------------------------------------------------------------------
 *  comiin  --  lower-half com device driver for input interrupts
 *------------------------------------------------------------------------
 */
INTPROC
comiin(struct comsoft *pcom)
{
	struct devsw	*pdev = pcom->com_pdev;
	unsigned int	ch;

	ch = inb((void *)pdev->dvcsr + DATA);
	if (pdev->dvioblk == 0)
		return;			/* no tty device associated */
	pdev = (struct devsw *)pdev->dvioblk;	/* get tty dev pointer */
	if (pdev == 0)
		return;			/* no tty structure associated */
	(pdev->dviint)(pdev, ch);
}
