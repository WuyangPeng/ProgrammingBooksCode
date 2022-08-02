/* lsa_add.c - lsa_add */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  lsa_add - add a link state advertisement to a link state update pkt.
 *------------------------------------------------------------------------
 */
void
lsa_add(struct ospf_if *pif, struct ep *pep, struct ospf_db *pdb)
{
	struct ip	*pip = (struct ip *)pep->ep_data;
	struct ospf	*po = (struct ospf *)pip->ip_data;
	struct ospf_lsu	*plsu = (struct ospf_lsu *)po->ospf_data;
	int		len;

	plsu->lsu_nads++;
	len = pdb->db_lsa.lsa_len;
	memcpy((char *)po + po->ospf_len, &pdb->db_lsa, len);
	po->ospf_len += pdb->db_lsa.lsa_len;
}
