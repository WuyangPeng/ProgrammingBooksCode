/* rfseek.c - rfseek */

#include <conf.h>
#include <kernel.h>
#include <fserver.h>
#include <rfile.h>
#include <sem.h>

/*------------------------------------------------------------------------
 *  rfseek  --  seek to a specified position of a remote file
 *------------------------------------------------------------------------
 */
int
rfseek(struct devsw *pdev, long offset)
{
	struct	rfblk	*rfptr;

	rfptr = (struct rfblk *)pdev->dvioblk;
	wait(rfptr->rf_mutex);
	rfptr->rf_pos = offset;
	signal(rfptr->rf_mutex);
	return(OK);
}
