/* tcpxmit.c - tcpxmit */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpxmit - handle TCP output events while we are transmitting
 *------------------------------------------------------------------------
 */
int
tcpxmit(int tcbnum, int event)
{
	struct	tcb	*ptcb = &tcbtab[tcbnum];
	void		*tv;
	int		tosend, pending, window;

	if (event == RETRANSMIT) {
		tmclear(tcps_oport, MKEVENT(SEND, tcbnum));
		tcprexmt(tcbnum, event);
		ptcb->tcb_ostate = TCPO_REXMT;
		return OK;
	} /* else SEND */
	tosend = tcphowmuch(ptcb);
	if (tosend == 0) {
		if (ptcb->tcb_flags & TCBF_NEEDOUT)
			tcpsend(tcbnum, TSF_NEWDATA);	/* just an ACK */
		if (ptcb->tcb_snext == ptcb->tcb_suna)
			return OK;
		/* still unacked data; restart transmit timer	*/
		tv = MKEVENT(RETRANSMIT, tcbnum);
		if (!tmleft(tcps_oport, tv))
			tmset(tcps_oport, TCPQLEN, tv, ptcb->tcb_rexmt);
		return OK;
	} else if (ptcb->tcb_swindow == 0) {
		ptcb->tcb_ostate = TCPO_PERSIST;
		ptcb->tcb_persist = ptcb->tcb_rexmt;
		tcpsend(tcbnum, TSF_NEWDATA);
		tmset(tcps_oport, TCPQLEN, MKEVENT(PERSIST,tcbnum),
			ptcb->tcb_persist);
		return OK;
	}	/* else, we have data and window */
	ptcb->tcb_ostate = TCPO_XMIT;
	window = min(ptcb->tcb_swindow, ptcb->tcb_cwnd);
	pending = ptcb->tcb_snext - ptcb->tcb_suna;
	while (tcphowmuch(ptcb) > 0 && pending < window) {
		tcpsend(tcbnum, TSF_NEWDATA);
		pending = ptcb->tcb_snext - ptcb->tcb_suna;
	}
	tv = MKEVENT(RETRANSMIT, tcbnum);
	if (!tmleft(tcps_oport, tv))
		tmset(tcps_oport, TCPQLEN, tv, ptcb->tcb_rexmt);
	return OK;
}
