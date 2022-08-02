/* dndump.c - dndump */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 * dndump - pretty-print a DNS packet
 *------------------------------------------------------------------------
 */
int dndump(pdn, dlen, order)
struct dn_mesg	*pdn;
int		dlen;
int		order;
{
	unsigned short	dn_id, dn_opparm, dn_qcount, dn_ncount, dn_dcount;

	if (order & EPO_DNS) {
		dn_id = pdn->dn_id;
		dn_opparm = pdn->dn_opparm;
		dn_qcount = pdn->dn_qcount;
		dn_ncount = pdn->dn_ncount;
		dn_dcount = pdn->dn_dcount;
	} else {
		dn_id = net2hs(pdn->dn_id);
		dn_opparm = net2hs(pdn->dn_opparm);
		dn_qcount = net2hs(pdn->dn_qcount);
		dn_ncount = net2hs(pdn->dn_ncount);
		dn_dcount = net2hs(pdn->dn_dcount);
	}
	kprintf("DNS:\tid %d opparm %x qcnt %d ncnt %d dcnt %d\n", dn_id,
		dn_opparm, dn_qcount, dn_ncount, dn_dcount);
UNDER CONSTRUCTION
}
