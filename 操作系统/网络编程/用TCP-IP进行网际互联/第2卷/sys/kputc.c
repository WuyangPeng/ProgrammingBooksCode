/* kputc.c - kputc */

#include <conf.h>
#include <kernel.h>
#include <tty.h>

/*------------------------------------------------------------------------
 * kputc - do a synchronous kernel write to the console tty
 *------------------------------------------------------------------------
 */
int
kputc(dev, c)
int		dev;	/* fake dev-- always the console */
unsigned char	 c;
{
	kbmputc(&devtab[KBMON], c);
	comsputc(&devtab[SERIAL1], c);
#ifdef notdef
	if (devtab[CONSOLE].dvioblk)
		putc(CONSOLE, c);
	else /* no tty yet; put it on SERIAL0 */
		comsputc(&devtab[SERIAL0], c);
#endif
	return OK;
}
