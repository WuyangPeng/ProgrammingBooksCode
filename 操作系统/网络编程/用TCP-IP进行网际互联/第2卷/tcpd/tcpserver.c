/* tcpserver.c - tcpserver */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ports.h>

/*------------------------------------------------------------------------
 *  tcpserver - do a TCP passive open
 *------------------------------------------------------------------------
 */
int
tcpserver(struct tcb *ptcb, u_short lport)
{
	if (lport == ANYLPORT) {
		ptcb->tcb_state = TCPS_FREE;
		sdelete(ptcb->tcb_mutex);
		return SYSERR;
	}
	ptcb->tcb_type = TCPT_SERVER;
	ptcb->tcb_lport = lport;
	ptcb->tcb_state = TCPS_LISTEN;
	ptcb->tcb_lqsize = tcps_lqsize;
	ptcb->tcb_listenq = pcreate(ptcb->tcb_lqsize);
	ptcb->tcb_smss = 0;
	signal(ptcb->tcb_mutex);
	return ptcb->tcb_dvnum;
}
