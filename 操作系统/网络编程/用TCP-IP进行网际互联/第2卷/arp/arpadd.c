/* arpadd.c - arpadd */

#include <conf.h>
#include <kernel.h>
#include <network.h>

struct arpentry *arpalloc(void);

/*------------------------------------------------------------------------
 * arpadd - Add a RESOLVED entry to the ARP cache
 * 	N.B. Assumes interrupts disabled
 *------------------------------------------------------------------------
 */
struct	arpentry *
arpadd(struct netif *pni, struct arp *parp)
{
	struct	arpentry	*pae;

	pae = arpalloc();

	pae->ae_hwtype = parp->ar_hwtype;
	pae->ae_prtype = parp->ar_prtype;
	pae->ae_hwlen = parp->ar_hwlen;
	pae->ae_prlen = parp->ar_prlen;
	pae->ae_pni = pni;
	pae->ae_queue = EMPTY;
	memcpy(pae->ae_hwa, SHA(parp), parp->ar_hwlen);
	memcpy(pae->ae_pra, SPA(parp), parp->ar_prlen);
	pae->ae_ttl = ARP_TIMEOUT;
	pae->ae_state = AS_RESOLVED;
	return pae;
}
