/* dgmcntl.c - dgmcntl */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  dgmcntl  -  control the network and datagram pseudo devices
 *------------------------------------------------------------------------
 */
int
dgmcntl(struct devsw *pdev, int com, void *arg1, void *arg2)
{
	int	status;

	switch (com)	{
	default:
		status = SYSERR;
	}
	return status;
}
