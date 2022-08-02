/* arpqsend.c - arpqsend */

#include <conf.h>
#include <kernel.h>
#include <network.h>

int netwrite(struct netif *, struct ep *, unsigned);

/*------------------------------------------------------------------------
 * arpqsend - write packets queued waiting for an ARP resolution
 *------------------------------------------------------------------------
 */
void
arpqsend(struct arpentry *pae)
{
	struct	ep	*pep;
	struct	netif	*pni;

	if (pae->ae_queue == EMPTY)
		return;

	pni = pae->ae_pni;
	while (pep = (struct ep *)deq(pae->ae_queue))
		netwrite(pni, pep, pep->ep_len);
	freeq(pae->ae_queue);
	pae->ae_queue = EMPTY;
}
