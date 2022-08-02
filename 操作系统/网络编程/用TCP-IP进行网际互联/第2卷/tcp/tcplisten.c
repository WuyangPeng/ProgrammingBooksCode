/* tcplisten.c - tcplisten */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcplisten -  do LISTEN state processing
 *------------------------------------------------------------------------
 */
int
tcplisten(struct tcb *ptcb, struct ep *pep)
{
	struct	tcb	*newptcb, *tcballoc();
	struct	ip	*pip = (struct ip *)pep->ep_data;
	struct	tcp	*ptcp = (struct tcp *)pip->ip_data;

	if (ptcp->tcp_code & TCPF_RST)
		return OK;		/* "parent" TCB still in LISTEN */
	if ((ptcp->tcp_code & TCPF_ACK) ||
	    (ptcp->tcp_code & TCPF_SYN) == 0)
		return tcpreset(pep);
	newptcb = tcballoc();
	if ((int)newptcb == SYSERR || tcpsync(newptcb) == SYSERR)
		return SYSERR;
	newptcb->tcb_state = TCPS_SYNRCVD;
	newptcb->tcb_ostate = TCPO_IDLE;
	newptcb->tcb_error = 0;
	newptcb->tcb_pptcb = ptcb;			/* for ACCEPT	*/

	newptcb->tcb_rip = pip->ip_src;
	newptcb->tcb_rport = ptcp->tcp_sport;
	newptcb->tcb_lip = pip->ip_dst;
	newptcb->tcb_lport = ptcp->tcp_dport;

	tcpwinit(ptcb, newptcb, pep);	/* initialize window data	*/

	newptcb->tcb_finseq = newptcb->tcb_pushseq = 0;
	newptcb->tcb_flags = TCBF_NEEDOUT;
	TcpPassiveOpens++;
	tcpdata(newptcb, pep);
	signal(newptcb->tcb_mutex);
	return OK;
}
