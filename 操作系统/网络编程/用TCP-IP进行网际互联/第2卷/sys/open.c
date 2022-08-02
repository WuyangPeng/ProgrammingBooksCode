/* open.c - open */

#include <conf.h>
#include <kernel.h>
#include <io.h>

/*------------------------------------------------------------------------
 *  open  -  open a connection to a device/file (parms 2 &3 are optional)
 *------------------------------------------------------------------------
 */
int
open(int descrp, const void *nam0, const void *mode0)
{
	char *nam = (char *)nam0;
	char *mode = (char *)mode0;
	struct	devsw	*pdev;

	if ( isbaddev(descrp) )
		return(SYSERR);
	pdev = &devtab[descrp];
	return(	(*pdev->dvopen)(pdev, nam, mode) );
}
