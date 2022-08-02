/* tcplastack.c - tcplastack */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcplastack -  do LAST_ACK state input processing
 *------------------------------------------------------------------------
 */
int
tcplastack(struct tcb *ptcb, struct ep *pep)
{
	struct	ip	*pip = (struct ip *)pep->ep_data;
	struct	tcp	*ptcp = (struct tcp *)pip->ip_data;

	if (ptcp->tcp_code & TCPF_RST)
		return tcpabort(ptcb, TCPE_RESET);
	if (ptcp->tcp_code & TCPF_SYN) {
		tcpreset(pep);
		return tcpabort(ptcb, TCPE_RESET);
	}
	tcpacked(ptcb, pep);
	if ((ptcb->tcb_code & TCPF_FIN) == 0)
		signal(ptcb->tcb_ocsem);	/* close() deallocs	*/
	return OK;
}
