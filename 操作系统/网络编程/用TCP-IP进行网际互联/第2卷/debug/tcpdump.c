/* tcpdump.c - tcpdump */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 * tcpdump - pretty-print a TCP packet to the console
 *------------------------------------------------------------------------
 */
tcpdump(ptcp, dlen, order)
struct tcp	*ptcp;
int		dlen;
{
	int		hlen;
	unsigned short	sport, dport, window, cksum, urgptr;
	unsigned long	seq, ack;

	if (order & EPO_TCP) {
		sport = ptcp->tcp_sport;
		dport = ptcp->tcp_dport;
		window = ptcp->tcp_window;
		cksum = ptcp->tcp_cksum;
		urgptr = ptcp->tcp_urgptr;
		seq = ptcp->tcp_seq;
		ack = ptcp->tcp_ack;
	} else {
		sport = net2hs(ptcp->tcp_sport);
		dport = net2hs(ptcp->tcp_dport);
		window = net2hs(ptcp->tcp_window);
		cksum = net2hs(ptcp->tcp_cksum);
		urgptr = net2hs(ptcp->tcp_urgptr);
		seq = net2hl(ptcp->tcp_seq);
		ack = net2hl(ptcp->tcp_ack);
	}
	kprintf("TCP:\tsrc %d\tdst %d\tseq %X\tack %X\n", sport, dport,
		seq, ack);
	kprintf("TCP: offset %x code %x window %x\n", ptcp->tcp_offset,
		ptcp->tcp_code, window);
	kprintf("TCP: cksum %x urg %d\n", cksum, urgptr);
	hlen = TCP_HLEN(ptcp);
	hexdump((char *)ptcp + hlen, dlen - hlen);
}
