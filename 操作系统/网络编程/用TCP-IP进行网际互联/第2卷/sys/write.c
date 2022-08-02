/* write.c - write */

#include <conf.h>
#include <kernel.h>
#include <io.h>

/*------------------------------------------------------------------------
 *  write  -  write 1 or more bytes to a device
 *------------------------------------------------------------------------
 */
int
write(int descrp, const void *buff, unsigned count)
{
	struct	devsw	*pdev;

	if (isbaddev(descrp) )
		return SYSERR;
	pdev = &devtab[descrp];
	return	(*pdev->dvwrite)(pdev, buff, count);
}
