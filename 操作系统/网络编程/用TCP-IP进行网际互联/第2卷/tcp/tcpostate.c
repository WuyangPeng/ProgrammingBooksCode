/* tcpostate.c - tcpostate */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpostate - do TCP output state processing after an ACK
 *------------------------------------------------------------------------
 */
int
tcpostate(struct tcb *ptcb, int acked)
{
	if (acked <= 0)
		return OK;	/* no state change */
	if (ptcb->tcb_ostate == TCPO_REXMT) {
		ptcb->tcb_rexmtcount = 0;
		ptcb->tcb_ostate = TCPO_XMIT;
	}
	if (ptcb->tcb_sbcount == 0) {
		ptcb->tcb_ostate = TCPO_IDLE;
		return OK;
	}
	tcpkick(ptcb);
	return OK;
}
