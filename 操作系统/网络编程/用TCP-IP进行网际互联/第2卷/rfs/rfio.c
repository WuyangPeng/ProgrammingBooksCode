/* rfio.c - rfio */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  rfio  --  perform input or output using remote file server
 *------------------------------------------------------------------------
 */
rfio(struct devsw *pdev, int rop, u_char *buff, unsigned len)
{
	struct	rfblk	*rfptr;
	int	retcode;

	rfptr = (struct rfblk *)pdev->dvioblk;
	wait(rfptr->rf_mutex);
	if (rfptr->rf_state == RFREE) {
		signal(rfptr->rf_mutex);
		return SYSERR;
	}
	retcode = rfmkpac(rop, rfptr->rf_name, (char *)&rfptr->rf_pos,
			buff, len);
	signal(rfptr->rf_mutex);
	return retcode;
}
