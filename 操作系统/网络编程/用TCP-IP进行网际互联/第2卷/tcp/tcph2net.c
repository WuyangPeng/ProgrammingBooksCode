/* tcph2net.c - tcph2net */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcph2net -  convert TCP header fields from host to net byte order
 *------------------------------------------------------------------------
 */
struct tcp *
tcph2net(struct tcp *ptcp)
{
	/* NOTE: does not include TCP options */

	ptcp->tcp_sport = hs2net(ptcp->tcp_sport);
	ptcp->tcp_dport = hs2net(ptcp->tcp_dport);
	ptcp->tcp_seq = hl2net(ptcp->tcp_seq);
	ptcp->tcp_ack = hl2net(ptcp->tcp_ack);
	ptcp->tcp_window = hs2net(ptcp->tcp_window);
	ptcp->tcp_urgptr = hs2net(ptcp->tcp_urgptr);
	return ptcp;
}
