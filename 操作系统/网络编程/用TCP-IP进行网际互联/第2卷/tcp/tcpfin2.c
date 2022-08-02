/* tcpfin2.c - tcpfin2 */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpfin2 -  do FIN_WAIT_2 state input processing
 *------------------------------------------------------------------------
 */
int
tcpfin2(struct tcb *ptcb, struct ep *pep)
{
	struct	ip	*pip = (struct ip *)pep->ep_data;
	struct	tcp	*ptcp = (struct tcp *)pip->ip_data;

	if (ptcp->tcp_code & TCPF_RST)
		return tcpabort(ptcb, TCPE_RESET);
	if (ptcp->tcp_code & TCPF_SYN) {
		tcpreset(pep);
		return tcpabort(ptcb, TCPE_RESET);
	}
	if (tcpacked(ptcb, pep) == SYSERR)
		return OK;
	tcpdata(ptcb, pep);	/* for data + FIN ACKing */

	if (ptcb->tcb_flags & TCBF_RDONE) {
		ptcb->tcb_state = TCPS_TIMEWAIT;
		tcpwait(ptcb);
	}
	return OK;
}
