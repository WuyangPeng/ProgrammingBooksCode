/* ospfnet2h.c - ospfnet2h */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 * ospfnet2h - convert OSPF header from network to host byte order
 *------------------------------------------------------------------------
 */
struct ospf *
ospfnet2h(struct ospf *po)
{
	/* NOTE: only includes fields in the main header */

	po->ospf_len = net2hs(po->ospf_len);
	po->ospf_cksum = net2hs(po->ospf_cksum);
	po->ospf_authtype = net2hs(po->ospf_authtype);
}
