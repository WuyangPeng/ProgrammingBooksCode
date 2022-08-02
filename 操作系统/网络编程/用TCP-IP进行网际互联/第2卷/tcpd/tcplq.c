/* tcplq.c - tcplq */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <mark.h>
#include <ports.h>

/*------------------------------------------------------------------------
 *  tcplq - set the listen queue size for a TCP pseudo device
 *------------------------------------------------------------------------
 */
int
tcplq(struct tcb *ptcb, unsigned lqsize)
{
	if (ptcb->tcb_state == TCPS_FREE)
		return SYSERR;
	ptcb->tcb_lqsize = lqsize;
	if (ptcb->tcb_type == TCPT_SERVER) {
		pdelete(ptcb->tcb_listenq, PTNODISP);
		ptcb->tcb_listenq = pcreate(ptcb->tcb_lqsize);
	}
	return OK;
}
