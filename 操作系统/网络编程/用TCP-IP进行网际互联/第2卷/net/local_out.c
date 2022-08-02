/* local_out.c - local_out */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <network.h>

struct ep	*ipreass(struct ep *);

typedef int (infunc_t)(struct netif *, struct ep *);

infunc_t icmp_in, igmp_in, tcp_in, udp_in, ipdstopts;
#ifdef OSPF
infunc_t ospf_in;
#endif /*OSPF*/


/*------------------------------------------------------------------------
 *  local_out  -  handle an IP datagram headed for a local process
 *------------------------------------------------------------------------
 */
int
local_out(struct ep *pep)
{
	struct	netif	*pni = &nif[NI_LOCAL];
	struct	ip	*pip = (struct ip *)pep->ep_data;
	int		rv;

	ipnet2h(pip);
	pep->ep_order |= EPO_IP;
	pep = ipreass(pep);
	if (pep == 0)
		return OK;
	pip = (struct ip *)pep->ep_data;
	ipdstopts(pni, pep);		/* do IP option processing	*/
	switch (pip->ip_proto) {
	case IPT_ICMP:
		rv = icmp_in(pni, pep);
		break;
	case IPT_IGMP:
		rv = igmp_in(pni, pep);
		break;
	case IPT_TCP:
		rv = tcp_in(pni, pep);
		break;
	case IPT_UDP:
		rv = udp_in(pni, pep);
		break;
#ifdef OSPF
	case IPT_OSPF:
		rv = ospf_in(pni, pep);
		break;
#endif
	default:
		IpInUnknownProtos++;
		icmp(ICT_DESTUR, ICC_PROTOUR, pip->ip_src, pep, 0);
		return OK;
	}
	IpInDelivers++;
	return rv;
}
