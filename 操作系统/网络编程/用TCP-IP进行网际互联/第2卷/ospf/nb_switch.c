/* nb_switch.c - nb_switch */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

SYSCALL gettime(unsigned long *);

/*------------------------------------------------------------------------
 *  nb_switch - handle neighbor state changes on HELLO packet input
 *------------------------------------------------------------------------
 */
int
nb_switch(struct ospf_if *pif, struct ospf_nb *pnb, struct ep *pep)
{
	struct ip		*pip;
	struct ospf		*po;
	struct ospf_hello	*poh;
	Bool			found = FALSE;
	int			nn, maxn;

	pip = (struct ip *)pep->ep_data;
	po = (struct ospf *)((char *)pip + IP_HLEN(pip));
	poh = (struct ospf_hello *)po->ospf_data;

	maxn = (po->ospf_len - MINHELLOLEN) / sizeof(long);
	for (nn=0; nn<maxn; ++nn)
		if (found = (pif->if_rid == poh->oh_neighbor[nn]))
			break;
	if (!found) {
		if (pnb->nb_state >= NBS_2WAY) {
			pnb->nb_state = NBS_INIT;
			nb_clearl(pnb);
		}
		return 0;
	} else if (pnb->nb_state == NBS_INIT) {
		pnb->nb_state = NBS_2WAY;
		if (nb_aok(pif, pnb)) {
			gettime(&pnb->nb_seq);	/* set initial seq */
			pnb->nb_state = NBS_EXSTART;
			nb_makel(pnb);
			dd_queue(pif, pnb);
		}
	}
	return 1;
}
