/* ospfifinit.c - ospfifinit */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

int hgjoin(unsigned, IPaddr, Bool);

/*------------------------------------------------------------------------
 * ospfifinit - initialize OSPF interface data
 *------------------------------------------------------------------------
 */
void
ospfifinit(int aindex, unsigned ifn)
{
	struct ospf_if	*pif = &ospf_if[ifn];
	struct ospf_nb	*pnb;
	int		i;

	pif->if_type = IFT_BROADCAST;
	pif->if_state = IFS_DOWN;
	pif->if_area = &ospf_ar[aindex];
	pif->if_hintv = HELLOINTV;
	pif->if_rdintv = DEADINTV;
	pif->if_xdelay = 1;
	pif->if_prio = 1;
	pif->if_rid = nif[NI_PRIMARY].ni_ip;
	pif->if_drid	= pif->if_brid    = 0;
	pif->if_metric = 1;
	pif->if_opts = NBO_E;

	pif->if_rintv = RXMTINTV;
	memset(pif->if_auth, 0, AUTHLEN);

	pif->if_nbmutex = screate(0);
	/* "neighbor" 0 is the entry for this interface */

	pnb = &pif->if_nbtab[0];
	pnb->nb_state = NBS_FULL;
	++pnb;

	for (i=1; i<MAXNBR; ++i, ++pnb)
		pnb->nb_state = NBS_DOWN;
	signal(pif->if_nbmutex);
	if (ifn == NI_PRIMARY)
		hgjoin(NI_PRIMARY, AllSPFRouters, TRUE);
}

struct ospf_if	ospf_if[NIF];
