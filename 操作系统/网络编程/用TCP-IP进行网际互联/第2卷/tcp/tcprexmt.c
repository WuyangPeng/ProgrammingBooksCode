/* tcprexmt.c - tcprexmt */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcprexmt - handle TCP output events while we are retransmitting
 *------------------------------------------------------------------------
 */
int
tcprexmt(int tcbnum, int event)
{
	struct	tcb	*ptcb = &tcbtab[tcbnum];

	if (event != RETRANSMIT)
		return OK;	/* ignore others while retransmitting	*/
	if (++ptcb->tcb_rexmtcount > TCP_MAXRETRIES) {
		tcpabort(ptcb, TCPE_TIMEDOUT);
		return OK;
	}
	tcpsend(tcbnum, TSF_REXMT);
	tmset(tcps_oport, TCPQLEN, MKEVENT(RETRANSMIT, tcbnum),
		min(ptcb->tcb_rexmt<<ptcb->tcb_rexmtcount, TCP_MAXRXT));
	if (ptcb->tcb_ostate != TCPO_REXMT)
		ptcb->tcb_ssthresh = ptcb->tcb_cwnd;	/* first drop	*/
	ptcb->tcb_ssthresh = min(ptcb->tcb_swindow,ptcb->tcb_ssthresh)/2;
	if (ptcb->tcb_ssthresh < ptcb->tcb_smss)
		ptcb->tcb_ssthresh = ptcb->tcb_smss;
	ptcb->tcb_cwnd = ptcb->tcb_smss;
	return OK;
}
