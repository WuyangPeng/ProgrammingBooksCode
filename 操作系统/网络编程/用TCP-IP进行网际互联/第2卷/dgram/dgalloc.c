/* dgalloc.c - dgalloc */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  dgalloc  -  allocate a datagram psuedo device; return its descriptor
 *------------------------------------------------------------------------
 */
int
dgalloc(void)
{
	struct	dgblk	*pdg;
	int		i;

	wait(dgmutex);
	for (i=0 ; i<Ndg ; ++i) {
		pdg = &dgtab[i];
		if (pdg->dg_state == DGS_FREE) {
			pdg->dg_state = DGS_INUSE;
			signal(dgmutex);
			return i;
		}
	}
	signal(dgmutex);
	return SYSERR;
}
