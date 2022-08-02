/* ospf_in.c - ospf_in */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ports.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  ospf_in - deliver an inbound OSPF packet to the OSPF input process
 *------------------------------------------------------------------------
 */
int
ospf_in(struct netif *pni, struct ep *pep)
{
	/* drop instead of blocking on psend */ 

	if (pcount(ospf_iport) >= OSPFQLEN) {
		freebuf(pep);
		return SYSERR;
	}
	psend(ospf_iport, (int)pep);
	return OK;
}
