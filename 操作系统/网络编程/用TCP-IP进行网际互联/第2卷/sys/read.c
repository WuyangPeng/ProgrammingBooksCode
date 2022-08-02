/* read.c - read */

#include <conf.h>
#include <kernel.h>
#include <io.h>

/*------------------------------------------------------------------------
 *  read  -  read one or more bytes from a device
 *------------------------------------------------------------------------
 */
int
read(int descrp, void *buff, unsigned count)
{
	struct	devsw	*pdev;

	if (isbaddev(descrp) )
		return(SYSERR);
	pdev = &devtab[descrp];
	return (*pdev->dvread)(pdev, buff, count);
}
