/* arpdq.c - arpdq */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 * arpdq - destroy an arp queue that has expired
 *------------------------------------------------------------------------
 */
void
arpdq(struct arpentry *pae)
{
	struct	ep	*pep;
	struct	ip	*pip;

	if (pae->ae_queue < 0)		/* nothing to do */
		return;

	while (pep = (struct ep *)deq(pae->ae_queue)) {
		if (gateway && pae->ae_prtype == EPT_IP) {
			pip = (struct ip *)pep->ep_data;
			icmp(ICT_DESTUR, ICC_HOSTUR, pip->ip_src, pep, 0);
		} else
			freebuf(pep);
	}
	freeq(pae->ae_queue);
	pae->ae_queue = EMPTY;
}
