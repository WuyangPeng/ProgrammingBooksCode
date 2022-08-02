/* rfputc.c - rfputc */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  rfputc  --  put a single character into a remote file
 *------------------------------------------------------------------------
 */
int
rfputc(struct devsw *pdev, unsigned char ch)
{
	char	outch;

	outch = ch;
	if ( write(pdev->dvnum, &outch, 1) == 1)
		return OK;
	else
		return SYSERR;
}
