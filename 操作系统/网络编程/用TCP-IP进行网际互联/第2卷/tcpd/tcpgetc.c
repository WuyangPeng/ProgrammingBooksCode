/* tcpgetc.c - tcpgetc */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpgetc  -  read one character from a TCP pseudo-device
 *------------------------------------------------------------------------
 */
int
tcpgetc(struct devsw *pdev)
{
	char	ch;
	int	cc;

	cc = tcpread(pdev, &ch, 1);
	if (cc < 0)
		return SYSERR;
	else if (cc == 0)
		return EOF;
	/* else, valid data */
	return ch;
}
