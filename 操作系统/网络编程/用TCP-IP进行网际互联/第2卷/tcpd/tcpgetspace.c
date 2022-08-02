/* tcpgetspace.c - tcpgetspace */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpgetspace  -  wait for space in the send buffer
 *	N.B. - returns with tcb_mutex HELD
 *------------------------------------------------------------------------
 */
int
tcpgetspace(struct tcb *ptcb, unsigned len)
{
	if (len > ptcb->tcb_sbsize)
		return TCPE_TOOBIG;	/* we'll never have this much	*/
	while (1) {
		wait(ptcb->tcb_ssema);
		wait(ptcb->tcb_mutex);
		if (ptcb->tcb_state == TCPS_FREE)
			return SYSERR;			/* gone		*/
		if (ptcb->tcb_error) {
			tcpwakeup(WRITERS, ptcb);	/* propagate it */
			signal(ptcb->tcb_mutex);
			return ptcb->tcb_error;
		}
		if (len <= ptcb->tcb_sbsize - ptcb->tcb_sbcount)
			return len;
		signal(ptcb->tcb_mutex);
	}
}
