/* tcpsynsent.c - tcpsynsent */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpsynsent -  do SYN_SENT state processing
 *------------------------------------------------------------------------
 */
int
tcpsynsent(struct tcb *ptcb, struct ep *pep)
{
	struct	ip	*pip = (struct ip *)pep->ep_data;
	struct	tcp	*ptcp = (struct tcp *)pip->ip_data;

	if ((ptcp->tcp_code & TCPF_ACK) &&
	    ((ptcp->tcp_ack - ptcb->tcb_iss <= 0) ||
	    (ptcp->tcp_ack - ptcb->tcb_snext) > 0))
		return tcpreset(pep);
	if (ptcp->tcp_code & TCPF_RST) {
		ptcb->tcb_state = TCPS_CLOSED;
		ptcb->tcb_error = TCPE_RESET;
		TcpAttemptFails++;
		tcpkilltimers(ptcb);
		signal(ptcb->tcb_ocsem);
		return OK;
	}
	if ((ptcp->tcp_code & TCPF_SYN) == 0)
		return OK;
	ptcb->tcb_swindow = ptcp->tcp_window;
	ptcb->tcb_lwseq = ptcp->tcp_seq;
	ptcb->tcb_rnext = ptcp->tcp_seq;
	ptcb->tcb_cwin = ptcb->tcb_rnext + ptcb->tcb_rbsize;
	tcpacked(ptcb, pep);
	tcpdata(ptcb, pep);
	ptcp->tcp_code &= ~TCPF_FIN;
	if (ptcb->tcb_code & TCPF_SYN)		/* our SYN not ACKed	*/
		ptcb->tcb_state = TCPS_SYNRCVD;
	else {
		TcpCurrEstab++;
		ptcb->tcb_state = TCPS_ESTABLISHED;
		signal(ptcb->tcb_ocsem);	/* return in open	*/
	}
	return OK;
}
