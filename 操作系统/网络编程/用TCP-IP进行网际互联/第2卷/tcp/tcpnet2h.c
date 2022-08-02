/* tcpnet2h.c - tcpnet2h */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpnet2h -  convert TCP header fields from net to host byte order
 *------------------------------------------------------------------------
 */
struct tcp *
tcpnet2h(struct tcp *ptcp)
{
	/* NOTE: does not include TCP options */

	ptcp->tcp_sport = net2hs(ptcp->tcp_sport);
	ptcp->tcp_dport = net2hs(ptcp->tcp_dport);
	ptcp->tcp_seq = net2hl(ptcp->tcp_seq);
	ptcp->tcp_ack = net2hl(ptcp->tcp_ack);
	ptcp->tcp_window = net2hs(ptcp->tcp_window);
	ptcp->tcp_urgptr = net2hs(ptcp->tcp_urgptr);
	return ptcp;
}
