/* tcpacked.c - tcpacked */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpacked - handle in-bound ACKs and do round trip estimates
 *------------------------------------------------------------------------
 */
int
tcpacked(struct tcb *ptcb, struct ep *pep)
{
	struct	ip	*pip = (struct ip *)pep->ep_data;
	struct	tcp	*ptcp = (struct tcp *)pip->ip_data;
	int		acked, tcbnum, cacked;
	STATWORD	ps;

	if (!(ptcp->tcp_code & TCPF_ACK))
		return SYSERR;
	acked = ptcp->tcp_ack - ptcb->tcb_suna;
	cacked = 0;
	if (acked <= 0)
		return 0;	/* duplicate ACK */
	if (SEQCMP(ptcp->tcp_ack, ptcb->tcb_snext) > 0)
		if (ptcb->tcb_state == TCPS_SYNRCVD)
			return tcpreset(pep);
		else
			return tcpackit(ptcb, pep);
	tcprtt(ptcb);
	ptcb->tcb_suna = ptcp->tcp_ack;
	if (acked && ptcb->tcb_code & TCPF_SYN) {
		acked--;
		cacked++;
		ptcb->tcb_code &= ~TCPF_SYN;
		ptcb->tcb_flags &= ~TCBF_FIRSTSEND;
	}
	if ((ptcb->tcb_code & TCPF_FIN) &&
	    SEQCMP(ptcp->tcp_ack, ptcb->tcb_snext) == 0) {
		acked--;
		cacked++;
		ptcb->tcb_code &= ~TCPF_FIN;
		ptcb->tcb_flags &= ~TCBF_SNDFIN;
	}
	if ((ptcb->tcb_flags & TCBF_SUPOK) &&
	    SEQCMP(ptcp->tcp_ack, ptcb->tcb_supseq) >= 0)
		ptcb->tcb_flags &= ~TCBF_SUPOK;
	ptcb->tcb_sbstart = (ptcb->tcb_sbstart+acked) % ptcb->tcb_sbsize;
	ptcb->tcb_sbcount -= acked;
	if (acked) {
		disable(ps);
		if (scount(ptcb->tcb_ssema) <= 0)
			signal(ptcb->tcb_ssema);
		restore(ps);
	}
	tcpostate(ptcb, acked+cacked);
	return acked;
}
