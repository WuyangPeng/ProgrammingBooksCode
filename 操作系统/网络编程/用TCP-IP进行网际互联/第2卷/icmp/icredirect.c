/* icredirect.c - icredirect */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  icredirect -  handle an incoming ICMP redirect
 *------------------------------------------------------------------------
 */
int
icredirect(struct ep *pep)
{
	struct	route	*prt;
	struct	ip	*pip, *pip2;
	struct	icmp	*pic;
	IPaddr		mask;

	pip = (struct ip *)pep->ep_data;
	pic = (struct icmp *)pip->ip_data;
	pip2 = (struct ip *)pic->ic_data;

	if (pic->ic_code == ICC_HOSTRD)
		mask = ip_maskall;
	else
		mask = netmask(pip2->ip_dst);
	prt = rtget(pip2->ip_dst, RTF_LOCAL);
	if (prt == 0) {
		freebuf(pep);
		return OK;
	}
	if (pip->ip_src == prt->rt_gw) {
		rtdel(pip2->ip_dst, mask);
		rtadd(pip2->ip_dst, mask, pic->ic_gw, prt->rt_metric,
			prt->rt_ifnum, IC_RDTTL);
	}
	rtfree(prt);
	freebuf(pep);
	return OK;
}
