/* ipfsend.c - ipfsend */

#include <conf.h>
#include <kernel.h>
#include <network.h>

int ipfhcopy(struct ep *, struct ep *, unsigned);

/*------------------------------------------------------------------------
 *  ipfsend -  send one fragment of an IP datagram
 *------------------------------------------------------------------------
 */
int
ipfsend(struct netif *pni, IPaddr nexthop, struct ep *pep,
	unsigned offset, unsigned maxdlen, unsigned offindg)
{
	struct	ep	*pepnew;
	struct	ip	*pip, *pipnew;
	int		hlen, len;

	pepnew = (struct ep *)getbuf(Net.netpool);
	if (pepnew == (struct ep *)SYSERR)
		return SYSERR;
	pepnew->ep_order = ~0;
	hlen = ipfhcopy(pepnew, pep, offindg);	/* copy the headers */

	pip = (struct ip *)pep->ep_data;
	pipnew = (struct ip *)pepnew->ep_data;
	pipnew->ip_fragoff = IP_MF | (offindg>>3);
	pipnew->ip_len = len = maxdlen + hlen;
	pipnew->ip_cksum = 0;

	iph2net(pipnew);
	pepnew->ep_order &= ~EPO_IP;
	pipnew->ip_cksum = cksum((WORD *)pipnew, hlen);

	memcpy(&pepnew->ep_data[hlen],
		&pep->ep_data[IP_HLEN(pip)+offset], maxdlen);
	pepnew->ep_nexthop = nexthop;

	return netwrite(pni, pepnew, EP_HLEN+len);
}
