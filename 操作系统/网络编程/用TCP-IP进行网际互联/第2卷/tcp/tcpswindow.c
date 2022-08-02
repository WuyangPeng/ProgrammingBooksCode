/* tcpswindow.c - tcpswindow */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpswindow -  handle send window updates from remote
 *------------------------------------------------------------------------
 */
int
tcpswindow(struct tcb *ptcb, struct ep *pep)
{
	struct ip	*pip = (struct ip *)pep->ep_data;
	struct tcp	*ptcp = (struct tcp *)pip->ip_data;
	tcpseq		wlast, owlast;

	if (SEQCMP(ptcp->tcp_seq, ptcb->tcb_lwseq) < 0)
		return OK;
	if (SEQCMP(ptcp->tcp_seq, ptcb->tcb_lwseq) == 0 &&
	    SEQCMP(ptcp->tcp_ack, ptcb->tcb_lwack) < 0)
		return OK;
	/* else, we have a send window update */

	/* compute the last sequences of the new and old windows */

	owlast = ptcb->tcb_lwack + ptcb->tcb_swindow;
	wlast = ptcp->tcp_ack + ptcp->tcp_window;

	ptcb->tcb_swindow = ptcp->tcp_window;
	ptcb->tcb_lwseq = ptcp->tcp_seq;
	ptcb->tcb_lwack = ptcp->tcp_ack;
	if (SEQCMP(wlast, owlast) <= 0)
		return OK;
	/* else,  window increased */
	if (ptcb->tcb_ostate == TCPO_PERSIST) {
		tmclear(tcps_oport, MKEVENT(PERSIST, ptcb-&tcbtab[0]));
		ptcb->tcb_ostate = TCPO_XMIT;
	}
	tcpkick(ptcb);			/* do something with it */
	return OK;
}
