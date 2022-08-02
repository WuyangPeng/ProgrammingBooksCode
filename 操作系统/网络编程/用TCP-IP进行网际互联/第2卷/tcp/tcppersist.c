/* tcppersist.c - tcppersist */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcppersist - handle events while the send window is closed
 *------------------------------------------------------------------------
 */
int
tcppersist(int tcbnum, int event)
{
	struct	tcb	*ptcb = &tcbtab[tcbnum];

	if (event != PERSIST && event != SEND)
		return OK;	/* ignore everything else */
	tcpsend(tcbnum, TSF_REXMT);
	ptcb->tcb_persist = min(ptcb->tcb_persist<<1, TCP_MAXPRS);
	tmset(tcps_oport, TCPQLEN, MKEVENT(PERSIST, tcbnum),
		ptcb->tcb_persist);
	return OK;
}
