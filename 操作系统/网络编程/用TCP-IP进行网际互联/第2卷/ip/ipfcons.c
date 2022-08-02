/* ipfcons.c - ipfcons */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  ipfcons  -  construct a single packet from an IP fragment queue
 *------------------------------------------------------------------------
 */
struct ep *
ipfcons(struct ipfq *iq)
{
	struct	ep	*pep, *peptmp;
	struct	ip	*pip;
	int		off, seq;

	pep = (struct ep *)getbuf(Net.lrgpool);
	if (pep == (struct ep *)SYSERR) {
		while (peptmp = (struct ep *)deq(iq->ipf_q)) {
			IpReasmFails++;
			freebuf(peptmp);
		}
		freeq(iq->ipf_q);
		iq->ipf_state = IPFF_FREE;
		return 0;
	}
	/* copy the Ether and IP headers */

	peptmp = (struct ep *)deq(iq->ipf_q);
	pip = (struct ip *)peptmp->ep_data;
	off = IP_HLEN(pip);
	seq = 0;
	memcpy(pep, peptmp, EP_HLEN+off);

	/* copy the data */
	while (peptmp != 0) {
		int dlen, doff;

		pip = (struct ip *)peptmp->ep_data;
		doff = IP_HLEN(pip) + seq
			- ((pip->ip_fragoff&IP_FRAGOFF)<<3);
		dlen = pip->ip_len - doff;
		memcpy(pep->ep_data+off, peptmp->ep_data+doff, dlen);
		off += dlen;
		seq += dlen;
		freebuf(peptmp);
		peptmp = (struct ep *)deq(iq->ipf_q);
	}

	/* fix the large packet header */
	pip = (struct ip *)pep->ep_data;
	pip->ip_len = off;
	pip->ip_fragoff = 0;

	/* release resources */
	freeq(iq->ipf_q);
	iq->ipf_state = IPFF_FREE;
	IpReasmOKs++;
	return pep;
}
