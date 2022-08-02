/* tcpsend.c - tcpsend */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpsend -  compute and send a TCP segment for the given TCB
 *------------------------------------------------------------------------
 */
int
tcpsend(int tcbnum, Bool rexmt)
{
	struct	tcb	*ptcb = &tcbtab[tcbnum];
	struct	ep	*pep;
	struct	ip	*pip;
	struct	tcp	*ptcp;
	u_char		*pch;
	unsigned	i, datalen, tocopy, off;
	int		newdata;

	pep = (struct ep *)getbuf(Net.netpool);
	if ((int)pep == SYSERR)
		return SYSERR;
	pep->ep_order = ~0;
	pip = (struct ip *)pep->ep_data;
	pip->ip_src = ptcb->tcb_lip;
	pip->ip_dst = ptcb->tcb_rip;
	datalen = tcpsndlen(ptcb, rexmt, &off);	/* get length & offset	*/
	ptcp = (struct tcp *)pip->ip_data;
	ptcp->tcp_sport = ptcb->tcb_lport;
	ptcp->tcp_dport = ptcb->tcb_rport;
	if (!rexmt)
		ptcp->tcp_seq = ptcb->tcb_snext;
	else
		ptcp->tcp_seq = ptcb->tcb_suna;
	ptcp->tcp_ack = ptcb->tcb_rnext;

	if ((ptcb->tcb_flags & TCBF_SNDFIN) &&
	    SEQCMP(ptcp->tcp_seq+datalen, ptcb->tcb_slast) == 0)
		ptcb->tcb_code |= TCPF_FIN;
	ptcp->tcp_code = ptcb->tcb_code;
	ptcp->tcp_offset = TCPHOFFSET;
	if ((ptcb->tcb_flags & TCBF_FIRSTSEND) == 0)
		ptcp->tcp_code |= TCPF_ACK;
	if (ptcp->tcp_code & TCPF_SYN)
		tcprmss(ptcb, pip);
	if (datalen > 0)
		ptcp->tcp_code |= TCPF_PSH;
	ptcp->tcp_window = tcprwindow(ptcb);
	if (ptcb->tcb_flags & TCBF_SUPOK) {
		short up = ptcb->tcb_supseq - ptcp->tcp_seq;

		if (up >= 0) {
#ifdef	BSDURG
			ptcp->tcp_urgptr = up + 1;	/* 1 past end	*/
#else	/* BSDURG */
			ptcp->tcp_urgptr = up;
#endif	/* BSDURG */
			ptcp->tcp_code |= TCPF_URG;
		} else
			ptcp->tcp_urgptr = 0;
	} else
		ptcp->tcp_urgptr = 0;
	pch = &pip->ip_data[TCP_HLEN(ptcp)];
	i = (ptcb->tcb_sbstart+off) % ptcb->tcb_sbsize;
	for (tocopy=datalen; tocopy > 0; --tocopy) {
		*pch++ = ptcb->tcb_sndbuf[i];
		if (++i >= ptcb->tcb_sbsize)
			i = 0;
	}
	ptcb->tcb_flags &= ~TCBF_NEEDOUT;	/* we're doing it	*/
	if (rexmt) {
		newdata = ptcb->tcb_suna + datalen - ptcb->tcb_snext;
		if (newdata < 0)
			newdata = 0;
		TcpRetransSegs++;
	} else {
		newdata = datalen;
		if (ptcb->tcb_code & TCPF_SYN)
			newdata++; /* SYN is part of the sequence	*/
		if (ptcb->tcb_code & TCPF_FIN)
			newdata++; /* FIN is part of the sequence	*/
	}
	ptcb->tcb_snext += newdata;
	if (newdata >= 0)
		TcpOutSegs++;
	if (ptcb->tcb_state == TCPS_TIMEWAIT)	/* final ACK		*/
		tcpwait(ptcb);
	datalen += TCP_HLEN(ptcp);
	tcph2net(ptcp);
	pep->ep_order &= ~EPO_TCP;
	ptcp->tcp_cksum = 0;
	ptcp->tcp_cksum = tcpcksum(pep, datalen);
	return ipsend(ptcb->tcb_rip, pep, datalen, IPT_TCP, IPP_NORMAL,
		IP_TTL);
}
