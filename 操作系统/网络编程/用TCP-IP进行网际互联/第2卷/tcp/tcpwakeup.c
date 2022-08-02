/* tcpwakeup.c - tcpwakeup */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpwakeup -  wake up processes sleeping for TCP, if necessary
 *	NB: Called with tcb_mutex HELD
 *------------------------------------------------------------------------
 */
int
tcpwakeup(int type, struct tcb *ptcb)
{
	int		freelen;
	STATWORD	ps;
	disable(ps);
	if (type & READERS) {
		if (((ptcb->tcb_flags & TCBF_RDONE) ||
		    ptcb->tcb_rbcount > 0 ||
		    (ptcb->tcb_flags & TCBF_RUPOK)) &&
		    scount(ptcb->tcb_rsema) <= 0)
			signal(ptcb->tcb_rsema);
	}
	if (type & WRITERS) {
		freelen = ptcb->tcb_sbsize - ptcb->tcb_sbcount;
		if (((ptcb->tcb_flags & TCBF_SDONE) || freelen > 0) &&
		    scount(ptcb->tcb_ssema) <= 0)
			signal(ptcb->tcb_ssema);
		/* special for abort */
		if (ptcb->tcb_error && ptcb->tcb_ocsem > 0)
			signal(ptcb->tcb_ocsem);
	}
	restore(ps);
	return OK;
}
