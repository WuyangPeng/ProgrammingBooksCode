/* tcpdodat.c - tcpdodat */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpdodat -  do input data processing
 *------------------------------------------------------------------------
 */
int
tcpdodat(struct tcb *ptcb,struct tcp *ptcp,tcpseq first,unsigned datalen)
{
	int	wakeup = 0;

	if (ptcb->tcb_rnext == first) {
		if (datalen > 0) {
			tfcoalesce(ptcb, datalen, ptcp);
			ptcb->tcb_flags |= TCBF_NEEDOUT;
			wakeup++;
		}
		if (ptcp->tcp_code & TCPF_FIN) {
			ptcb->tcb_flags |= TCBF_RDONE|TCBF_NEEDOUT;
			ptcb->tcb_rnext++;
			wakeup++;
		}
		if (ptcp->tcp_code & (TCPF_PSH | TCPF_URG)) {
			ptcb->tcb_flags |= TCBF_PUSH;
			wakeup++;
		}
		if (wakeup)
			tcpwakeup(READERS, ptcb);
	} else {
		/* process delayed controls */
		if (ptcp->tcp_code & TCPF_FIN)
			ptcb->tcb_finseq = ptcp->tcp_seq + datalen;
		if (ptcp->tcp_code & (TCPF_PSH | TCPF_URG))
			ptcb->tcb_pushseq = ptcp->tcp_seq + datalen;
		ptcp->tcp_code &= ~(TCPF_FIN|TCPF_PSH);
		tfinsert(ptcb, first, datalen);
	}
	return OK;
}
