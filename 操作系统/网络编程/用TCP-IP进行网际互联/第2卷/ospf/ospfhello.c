/* ospfhello.c - ospfhello */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <sleep.h>
#include <ospf.h>

#define	OSPFDELTA	10	/* OSPF "stagger" bounds (1/10 secs)	*/

int ospf_hsend(unsigned);

/*------------------------------------------------------------------------
 * ospfhello - send OSPF hello packets
 *------------------------------------------------------------------------
 */
PROCESS
ospfhello(void)
{
	struct ospf_if	*pif;
	int		ifn, rnd;

	/* select initial "random" offset to stagger hello's */
	rnd = nif[NI_PRIMARY].ni_ip % OSPFDELTA;

	/* do state changes first so we can receive while waiting */
	for (ifn=0; ifn<Net.nif; ++ifn) {
		if (ifn == NI_LOCAL)
			continue;
		if (nif[ifn].ni_state != NIS_UP)
			continue;
		pif = &ospf_if[ifn];
		switch (pif->if_type) {
		case IFT_MULTI:
		case IFT_BROADCAST:
			if (pif->if_prio > 0) {
				pif->if_twait = pif->if_rdintv;
				pif->if_state = IFS_WAITING;
			} else
				pif->if_state = IFS_DROTHER;
			break;
		case IFT_PT2PT:
		case IFT_VIRTUAL:
			pif->if_state = IFS_PT2PT;
			break;
		default:
			break;
		}
	}

	while (1) {
		sleep10(HELLOINTV*10 + rnd);
		if (++rnd == OSPFDELTA)
			rnd = -OSPFDELTA;

		for (ifn=0; ifn<Net.nif; ++ifn) {
			if (ifn == NI_LOCAL)
				continue;
			if (nif[ifn].ni_state != NIS_UP)
				continue;
			ospf_hsend(ifn);
		}
	}
}
