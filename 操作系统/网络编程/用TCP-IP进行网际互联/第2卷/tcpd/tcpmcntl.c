/* tcpmcntl.c - tcpmcntl */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpmcntl - control function for the master TCP pseudo-device
 *------------------------------------------------------------------------
 */
int
tcpmcntl(struct devsw *pdev, int func, void *arg, void *arg2)
{
	int	rv;

	if (pdev != &devtab[TCP])
		return SYSERR;

	switch (func) {
	case TCPC_LISTENQ:
		tcps_lqsize = (int)arg;
		rv = OK;
		break;
	default:
		rv = SYSERR;
	}
	return rv;
}
