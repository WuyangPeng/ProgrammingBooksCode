/* tcpestablished.c - tcpestablished */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpestablished -  do ESTABLISHED state input processing
 *------------------------------------------------------------------------
 */
int
tcpestablished(struct tcb *ptcb, struct ep *pep)
{
	struct	ip	*pip = (struct ip *)pep->ep_data;
	struct	tcp	*ptcp = (struct tcp *)pip->ip_data;

	if (ptcp->tcp_code & TCPF_RST) {
		TcpEstabResets++;
		TcpCurrEstab--;
		return tcpabort(ptcb, TCPE_RESET);
	}
	if (ptcp->tcp_code & TCPF_SYN) {
		TcpEstabResets++;
		TcpCurrEstab--;
		tcpreset(pep);
		return tcpabort(ptcb, TCPE_RESET);
	}
	if (tcpacked(ptcb, pep) == SYSERR)
		return OK;
	tcpdata(ptcb, pep);
	tcpswindow(ptcb, pep);
	if (ptcb->tcb_flags & TCBF_RDONE)
		ptcb->tcb_state = TCPS_CLOSEWAIT;
	return OK;
}
