/* dgcntl.c - dgcntl */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ports.h>

/*------------------------------------------------------------------------
 *  dgcntl  -  control function for datagram pseudo-devices
 *------------------------------------------------------------------------
 */
int
dgcntl(struct devsw *pdev, int func, void *arg1, void *arg2)
{
	STATWORD	ps;    
	struct	dgblk	*pdg;
	int		ret;

	disable(ps);
	pdg = (struct dgblk *)pdev->dvioblk;
	ret = OK;
	switch (func) {

		case DG_SETMODE:	/* set mode bits */
			pdg->dg_mode = (int)arg1;
			break;

		case DG_CLEAR:		/* clear queued packets */
			preset(pdg->dg_xport, (void (*)())freebuf);
			break;

		default:
			ret = SYSERR;
	}
	restore(ps);
	return ret;
}
