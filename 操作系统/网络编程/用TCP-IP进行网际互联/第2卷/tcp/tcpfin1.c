/* tcpfin1.c - tcpfin1 */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpfin1 -  do FIN_WAIT_1 state input processing
 *------------------------------------------------------------------------
 */
int
tcpfin1(struct tcb *ptcb, struct ep *pep)
{
	struct	ip	*pip	= (struct ip *)pep->ep_data;
	struct	tcp	*ptcp	= (struct tcp *)pip->ip_data;

	if (ptcp->tcp_code & TCPF_RST)
		return tcpabort(ptcb, TCPE_RESET);
	if (ptcp->tcp_code & TCPF_SYN) {
		tcpreset(pep);
		return tcpabort(ptcb, TCPE_RESET);
	}
	if (tcpacked(ptcb, pep) == SYSERR)
		return OK;
	tcpdata(ptcb, pep);
	tcpswindow(ptcb, pep);

	if (ptcb->tcb_flags & TCBF_RDONE) {
		if (ptcb->tcb_code & TCPF_FIN)		/* FIN not ACKed*/
			ptcb->tcb_state = TCPS_CLOSING;
		else {
			ptcb->tcb_state = TCPS_TIMEWAIT;
			signal(ptcb->tcb_ocsem);	/* wake closer	*/
			tcpwait(ptcb);
		}
	} else if ((ptcb->tcb_code & TCPF_FIN) == 0) {
		signal(ptcb->tcb_ocsem);		/* wake closer	*/
		ptcb->tcb_state = TCPS_FINWAIT2;
	}
	return OK;
}
