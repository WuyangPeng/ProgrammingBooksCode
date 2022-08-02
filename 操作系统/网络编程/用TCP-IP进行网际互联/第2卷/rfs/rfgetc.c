/* rfgetc.c - rfgetc */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  rfgetc  --  get a character from a remote file
 *------------------------------------------------------------------------
 */
int
rfgetc(struct devsw *pdev)
{
	char	ch;
	int	retcode;

	if ( (retcode=read(pdev->dvnum, &ch, 1)) == 1)
		return(ch);
	else if (retcode != EOF)
		retcode = SYSERR;
	return(retcode);
}
