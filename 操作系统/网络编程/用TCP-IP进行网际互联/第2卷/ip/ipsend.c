/* ipsend.c - ipsend */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <proc.h>

static ipackid = 1;

/*------------------------------------------------------------------------
 *  ipsend  -  send an IP datagram to the specified address
 *------------------------------------------------------------------------
 */
int
ipsend(IPaddr faddr, struct ep *pep, unsigned datalen,
	u_char proto, u_char ptos, u_char ttl)
{
	struct	ip *pip = (struct ip *) pep->ep_data;

	pep->ep_type = EPT_IP;
	pep->ep_order |= EPO_IP|EPO_NET;
	pip->ip_verlen = (IP_VERSION<<4) | IP_MINHLEN;
	pip->ip_tos = ptos;
	pip->ip_len = datalen+IP_HLEN(pip);
	pip->ip_id = ipackid++;
	pip->ip_fragoff = 0;
	pip->ip_ttl = ttl;
	pip->ip_proto = proto;
	pip->ip_dst = faddr;

	/*
	 * special case for ICMP, so source matches destination
	 * on multi-homed hosts.
	 */
	if (pip->ip_proto != IPT_ICMP)
		pip->ip_src = ip_anyaddr;

	if (enq(nif[NI_LOCAL].ni_ipinq, pep, 0) < 0) {
		freebuf(pep);
		IpOutDiscards++;
	}
	send(ippid, NI_LOCAL);
	IpOutRequests++;
	return OK;
}
/* special IP addresses */

IPaddr	ip_anyaddr = 0;
#if	BYTE_ORDER == LITTLE_ENDIAN
IPaddr	ip_loopback = 0x0100007F;	/* 127.0.0.1 */
#else	/* BYTE_ORDER */
IPaddr	ip_loopback = 0x7F000001;	/* 127.0.0.1 */
#endif	/* BYTE_ORDER */
