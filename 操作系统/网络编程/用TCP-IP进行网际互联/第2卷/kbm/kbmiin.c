/* kbmiin.c kbmiin */

#include <conf.h>
#include <kernel.h>
#include <io.h>
#include <tty.h>
#include <kbd.h>

static	int	state;
unsigned char	inb(void *);
unsigned int	kbtoa(unsigned char);

/*------------------------------------------------------------------------
 *  kbmiin  --  lower-half kbm device driver for input interrupts
 *------------------------------------------------------------------------
 */
INTPROC
kbmiin(void)
{
	struct devsw	*pdev = &devtab[KBMON];
	unsigned int	ch;
	unsigned char	code;

	if ((inb(KB_CSR) & KBS_HASDAT) == 0) {
		kprintf("interrupt without data\n");
		return;
	}
	code = inb(KB_DAT);
	if (pdev->dvioblk == 0)
		return;		/* no tty associated */
	ch = kbtoa(code);
	if (ch == NOCHAR)
		return;
	pdev = (struct devsw *)pdev->dvioblk;	/* get tty dev pointer */
	(pdev->dviint)(pdev, ch);
}
