/* ipfinit.c - ipfinit */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 * ipfinit  -  initialize IP fragment queue data structures
 *------------------------------------------------------------------------
 */
void
ipfinit(void)
{
	int	i;

	ipfmutex = screate(1);
	for (i=0; i<IP_FQSIZE; ++i)
		ipfqt[i].ipf_state = IPFF_FREE;
}
