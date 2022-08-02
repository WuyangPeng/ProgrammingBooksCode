/* tcpclosewait.c - tcpclosewait */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpclosewait -  do CLOSE_WAIT state input processing
 *------------------------------------------------------------------------
 */
int
tcpclosewait(struct tcb *ptcb, struct ep *pep)
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
	tcpacked(ptcb, pep);
	tcpswindow(ptcb, pep);
	return OK;
}
