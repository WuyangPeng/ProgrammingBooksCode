/* ip_in.c - ip_in */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <proc.h>

/*------------------------------------------------------------------------
 *  ip_in - IP input function
 *------------------------------------------------------------------------
 */
int
ip_in(struct netif *pni, struct ep *pep)
{
	struct	ip	*pip = (struct ip *)pep->ep_data;

	IpInReceives++;
	if (enq(pni->ni_ipinq, pep, pip->ip_tos & IP_PREC) < 0) {
		IpInDiscards++;
		freebuf(pep);
	}
	send(ippid, (pni-&nif[0]));
	return OK;
}
