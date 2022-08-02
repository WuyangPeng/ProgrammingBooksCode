/* rfclose.c - rfclose */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  rfclose  --  close a remote file by deallocating pseudo device
 *------------------------------------------------------------------------
 */
int
rfclose(struct devsw *pdev)
{
	struct	rfblk	*rfptr;
	char	junk;		/* argument to rfmkpac; not really used	*/

	rfptr = (struct rfblk *)pdev->dvioblk;
	if (rfptr->rf_state == RFREE)
		return SYSERR;
	wait(rfptr->rf_mutex);
	junk = 0L; /* 0L is long zero constant */
	rfmkpac(FS_CLOSE, rfptr->rf_name, &junk, (u_char *)&junk, 0);
	rfptr->rf_state = RFREE;
	signal(rfptr->rf_mutex);
	return OK;
}
