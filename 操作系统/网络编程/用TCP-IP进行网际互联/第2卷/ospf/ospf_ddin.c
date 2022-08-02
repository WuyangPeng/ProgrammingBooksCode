/* ospf_ddin.c - ospf_ddin */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 * ospf_ddin - handled input of OSPF Data Description packets
 *------------------------------------------------------------------------
 */
void
ospf_ddin(struct ep *pep)
{
	struct ospf_if	*pif = &ospf_if[pep->ep_ifn];
	struct ospf_nb	*pnb;
	struct ip	*pip;
	struct ospf	*po;
	struct ospf_dd	*pdd;

	pip = (struct ip *)pep->ep_data;
	po = (struct ospf *)((char *)pip + IP_HLEN(pip));

	pdd = (struct ospf_dd *)po->ospf_data;
	pdd->dd_seq = net2hl(pdd->dd_seq);

	pnb = nb_add(pif, po);
	if (pnb == 0)
		return;
	switch (pnb->nb_state) {
	case NBS_INIT:
		pnb->nb_state = NBS_2WAY;
		if (nb_aok(pif, pnb)) {
			pnb->nb_seq++;
			pnb->nb_state = NBS_EXSTART;
			nb_makel(pnb);
			dd_queue(pif, pnb);
		}
		break;
	case NBS_2WAY:
		return;
	case NBS_EXSTART:
		ddi_exstart(pif, pnb, pep);
		break;
	case NBS_EXCHNG:
		ddi_exchng(pif, pnb, pep);
		break;
	case NBS_LOADING:
	case NBS_FULL:
		ddi_full(pif, pnb, pep);
		break;
	}
}
