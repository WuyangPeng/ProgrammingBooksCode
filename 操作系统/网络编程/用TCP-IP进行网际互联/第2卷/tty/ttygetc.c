/* ttygetc.c - ttygetc */

#include <conf.h>
#include <kernel.h>
#include <tty.h>

/*------------------------------------------------------------------------
 * ttygetc - read a single character from a tty
 *------------------------------------------------------------------------
 */
int
ttygetc(pdev)
struct devsw	*pdev;
{
	unsigned char	ch;
	int		cc;

	cc = ttyread(pdev, &ch, 1);
	if (cc < 0)
		return SYSERR;
	else if (cc == 0)
		return EOF;
	return ch;
}
