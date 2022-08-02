/* tcpclosing.c - tcpclosing */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpclosing -  do CLOSING state input processing
 *------------------------------------------------------------------------
 */
int
tcpclosing(struct tcb *ptcb, struct ep *pep)
{
	struct	ip	*pip = (struct ip *)pep->ep_data;
	struct	tcp	*ptcp = (struct tcp *)pip->ip_data;

	if (ptcp->tcp_code & TCPF_RST)
		return tcbdealloc(ptcb);
	if (ptcp->tcp_code & TCPF_SYN) {
		tcpreset(pep);
		return tcbdealloc(ptcb);
	}
	tcpacked(ptcb, pep);
	if ((ptcb->tcb_code & TCPF_FIN) == 0) {
		ptcb->tcb_state = TCPS_TIMEWAIT;
		signal(ptcb->tcb_ocsem);		/* wake closer	*/
		tcpwait(ptcb);
	}
	return OK;
}
