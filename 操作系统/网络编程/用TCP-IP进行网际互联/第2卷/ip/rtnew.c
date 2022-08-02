/* rtnew.c - rtnew */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  rtnew  -  create a route structure
 *------------------------------------------------------------------------
 */
struct route *
rtnew(IPaddr net, IPaddr mask, IPaddr gw, unsigned metric,
	unsigned ifnum, unsigned ttl)
{
	struct	route *prt;

	prt = (struct route *)getbuf(Route.ri_bpool);
	if (prt == (struct route *)SYSERR) {
		IpRoutingDiscards++;
		return (struct route *)SYSERR;
	}

	prt->rt_net = net;
	prt->rt_mask = mask;
	prt->rt_gw = gw;
	prt->rt_metric = metric;
	prt->rt_ifnum = ifnum;
	prt->rt_ttl = ttl;
	prt->rt_refcnt = 1;	/* our caller */
	prt->rt_usecnt = 0;
	prt->rt_next = NULL;
	return prt;
}
