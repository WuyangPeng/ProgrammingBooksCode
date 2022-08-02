/* dgclose.c - dgclose */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <network.h>
#include <ports.h>

/*------------------------------------------------------------------------
 *  dgclose  -  close a datagram pseudo device, making it available again
 *------------------------------------------------------------------------
 */
int
dgclose(struct devsw *pdev)
{
	struct	dgblk	*pdg;
	struct	upq	*pup;
	int		freebuf();

	pdg = (struct dgblk *) pdev->dvioblk;
	pup = &upqs[pdg->dg_upq];
	wait(udpmutex);
	pup->up_port = 0;
	if (pup->up_xport >= 0)
		pdelete(pup->up_xport, (void (*)())freebuf);
	pup->up_valid = FALSE;
	signal(udpmutex);
	pdg->dg_state = DGS_FREE;
	return OK;
}

