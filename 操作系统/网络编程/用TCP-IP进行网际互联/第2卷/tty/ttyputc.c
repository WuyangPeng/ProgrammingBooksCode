/* ttyputc.c - ttyputc */

#include <conf.h>
#include <kernel.h>
#include <tty.h>

/*------------------------------------------------------------------------
 * ttyputc - write a single character to a tty
 *------------------------------------------------------------------------
 */
int
ttyputc(pdev, ch)
struct devsw	*pdev;
unsigned char	ch;
{
	return ttywrite(pdev, &ch, 1);
}
