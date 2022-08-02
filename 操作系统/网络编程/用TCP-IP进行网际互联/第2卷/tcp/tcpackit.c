/* tcpackit.c - tcpackit */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpackit -  generate an ACK for a received TCP packet
 *------------------------------------------------------------------------
 */
int
tcpackit(struct tcb *ptcb, struct ep *pepin)
{
	struct ep	*pepout;
	struct ip	*pipin = (struct ip *)pepin->ep_data, *pipout;
	struct tcp	*ptcpin = (struct tcp *)pipin->ip_data, *ptcpout;

	if (ptcpin->tcp_code & TCPF_RST)
		return OK;
	if (pipin->ip_len <= IP_HLEN(pipin) + TCP_HLEN(ptcpin) &&
			!(ptcpin->tcp_code & (TCPF_SYN|TCPF_FIN)))
		return OK;	/* duplicate ACK */
	pepout = (struct ep *)getbuf(Net.netpool);
	if ((int)pepout == SYSERR)
		return SYSERR;
	pepout->ep_order = ~0;
	pipout = (struct ip *)pepout->ep_data;
	pipout->ip_src = pipin->ip_dst;
	pipout->ip_dst = pipin->ip_src;
	ptcpout = (struct tcp *)pipout->ip_data;
	ptcpout->tcp_sport = ptcpin->tcp_dport;
	ptcpout->tcp_dport = ptcpin->tcp_sport;
	ptcpout->tcp_seq = ptcb->tcb_snext;
	ptcpout->tcp_ack = ptcb->tcb_rnext;
	ptcpout->tcp_code = TCPF_ACK;
	ptcpout->tcp_offset = TCPHOFFSET;
	ptcpout->tcp_window = tcprwindow(ptcb);
	ptcpout->tcp_urgptr = 0;
	ptcpout->tcp_cksum = 0;
	tcph2net(ptcpout);
	pepout->ep_order &= ~EPO_TCP;
	ptcpout->tcp_cksum = tcpcksum(pepout, TCPMHLEN);
	TcpOutSegs++;
	return ipsend(pipin->ip_src, pepout, TCPMHLEN, IPT_TCP,
		IPP_NORMAL, IP_TTL);
}
