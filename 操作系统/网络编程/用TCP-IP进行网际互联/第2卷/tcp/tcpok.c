/* tcpok.c - tcpok */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpok -  determine if a received segment is acceptable
 *------------------------------------------------------------------------
 */
Bool
tcpok(struct tcb *ptcb, struct ep *pep)
{
	struct	ip	*pip = (struct ip *)pep->ep_data;
	struct	tcp	*ptcp = (struct tcp *) pip->ip_data;
	int		seglen, rwindow;
	tcpseq		wlast, slast, sup;
	Bool		rv;

	if (ptcb->tcb_state < TCPS_SYNRCVD)
		return TRUE;
	seglen = pip->ip_len - IP_HLEN(pip) - TCP_HLEN(ptcp);

	/* add SYN and FIN */
	if (ptcp->tcp_code & TCPF_SYN)
		++seglen;
	if (ptcp->tcp_code & TCPF_FIN)
		++seglen;
	rwindow = ptcb->tcb_rbsize - ptcb->tcb_rbcount; 
	if (rwindow == 0 && seglen == 0)
		return ptcp->tcp_seq == ptcb->tcb_rnext;
	wlast = ptcb->tcb_rnext + rwindow - 1;
	rv = (ptcp->tcp_seq - ptcb->tcb_rnext) >= 0 &&
		(ptcp->tcp_seq - wlast) <= 0;
	if (seglen == 0)
		return rv;
	slast = ptcp->tcp_seq + seglen - 1;
	rv |= (slast - ptcb->tcb_rnext) >= 0 && (slast - wlast) <= 0;

	/* If no window, strip data but keep ACK, RST and URG		*/
	if (rwindow == 0)
		pip->ip_len = IP_HLEN(pip) + TCP_HLEN(ptcp);
	return rv;
}
