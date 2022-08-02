/* tcpsynrcvd.c - tcpsynrcvd */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ports.h>

/*------------------------------------------------------------------------
 *  tcpsynrcvd -  do SYN_RCVD state input processing
 *------------------------------------------------------------------------
 */
int
tcpsynrcvd(struct tcb *ptcb, struct ep *pep)
{
	struct	ip	*pip = (struct ip *)pep->ep_data;
	struct	tcp	*ptcp = (struct tcp *)pip->ip_data;
	struct	tcb	*pptcb;

	if (ptcp->tcp_code & TCPF_RST) {
		TcpAttemptFails++;
		if (ptcb->tcb_pptcb != 0)
			return tcbdealloc(ptcb);
		else
			return tcpabort(ptcb, TCPE_REFUSED);
	}
	if (ptcp->tcp_code & TCPF_SYN) {
		TcpAttemptFails++;
		tcpreset(pep);
		return tcpabort(ptcb, TCPE_RESET);
	}
	if (tcpacked(ptcb, pep) == SYSERR)
		return OK;
	if (ptcb->tcb_pptcb != 0) {		/* from a passive open	*/
		pptcb = ptcb->tcb_pptcb;
		if (wait(pptcb->tcb_mutex) != OK) {
			TcpAttemptFails++;
			tcpreset(pep);
			return tcbdealloc(ptcb);
		}
		if (pptcb->tcb_state != TCPS_LISTEN) {
			TcpAttemptFails++;
			tcpreset(pep);
			signal(pptcb->tcb_mutex);
			return tcbdealloc(ptcb);
		}
	    	if (pcount(pptcb->tcb_listenq) >= pptcb->tcb_lqsize) {
			TcpAttemptFails++;
			tcpreset(pep);
			signal(pptcb->tcb_mutex);
			return tcbdealloc(ptcb);
		}
		psend(pptcb->tcb_listenq, ptcb->tcb_dvnum);
		signal(pptcb->tcb_mutex);
	} else					/* from an active open	*/
		signal(ptcb->tcb_ocsem);
	TcpCurrEstab++;
	ptcb->tcb_state = TCPS_ESTABLISHED;
	tcpdata(ptcb, pep);
	if (ptcb->tcb_flags & TCBF_RDONE)
		ptcb->tcb_state = TCPS_CLOSEWAIT;
	return OK;
}
