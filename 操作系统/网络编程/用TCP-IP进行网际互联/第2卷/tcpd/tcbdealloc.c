/* tcbdealloc.c - tcbdealloc */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <sem.h>
#include <ports.h>
#include <mem.h>

/*------------------------------------------------------------------------
 *  tcbdealloc - deallocate a TCB and free its resources
 *	ASSUMES ptcb->tcb_mutex HELD
 *------------------------------------------------------------------------
 */
int
tcbdealloc(struct tcb *ptcb)
{
	if (ptcb->tcb_state == TCPS_FREE)
		return OK;
	switch (ptcb->tcb_type) {
	case TCPT_CONNECTION:
		tcpkilltimers(ptcb);
		sdelete(ptcb->tcb_ocsem);
		sdelete(ptcb->tcb_ssema);
		sdelete(ptcb->tcb_rsema);
		freemem(ptcb->tcb_sndbuf, ptcb->tcb_sbsize);
		freemem(ptcb->tcb_rcvbuf, ptcb->tcb_rbsize);
		if (ptcb->tcb_rsegq >= 0)
			freeq(ptcb->tcb_rsegq);
		break;
	case TCPT_SERVER:
		pdelete(ptcb->tcb_listenq, 0);
		break;
	default:
		signal(ptcb->tcb_mutex);
		return SYSERR;
	}
	ptcb->tcb_state = TCPS_FREE;
	sdelete(ptcb->tcb_mutex);
	return OK;
}
