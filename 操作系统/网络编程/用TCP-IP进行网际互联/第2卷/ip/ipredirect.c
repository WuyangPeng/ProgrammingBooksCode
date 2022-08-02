/* ipredirect.c - ipredirect */

#include <conf.h>
#include <kernel.h>
#include <network.h>

struct	route	*rtget(IPaddr, Bool);
int rtfree(struct route *);
IPaddr netmask(IPaddr);

/*------------------------------------------------------------------------
 *  ipredirect  -  send redirects, if needed
 *------------------------------------------------------------------------
 */
void
ipredirect(struct ep *pep, unsigned ifn, struct route *prt)
{
	struct	ip	*pip = (struct ip *)pep->ep_data;
	struct	route	*tprt;
	int		rdtype, isonehop;
	IPaddr		nmask;	/* network part's mask			*/

	if (ifn == NI_LOCAL || ifn != prt->rt_ifnum)
		return;
	tprt = rtget(pip->ip_src, RTF_LOCAL);
	if (!tprt)
		return;
	isonehop = tprt->rt_metric == 0;
	rtfree(tprt);
	if (!isonehop)
		return;
	/* got one... */

	nmask = netmask(prt->rt_net);	/* get the default net mask	*/
	if (prt->rt_mask == nmask)
		rdtype = ICC_NETRD;
	else
		rdtype = ICC_HOSTRD;
	icmp(ICT_REDIRECT, rdtype, pip->ip_src, pep, (void *)prt->rt_gw);
}
