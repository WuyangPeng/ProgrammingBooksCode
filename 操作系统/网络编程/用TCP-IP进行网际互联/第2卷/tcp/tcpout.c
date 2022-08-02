/* tcpout.c - tcpout */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ports.h>

/*------------------------------------------------------------------------
 *  tcpout - handle events affecting TCP output processing
 *------------------------------------------------------------------------
 */
PROCESS
tcpout(void)
{
	struct	tcb	*ptcb;
	int		i;

	tcps_oport = pcreate(TCPQLEN);
	signal(Net.sema);		/* synchronize on startup	*/

	while (TRUE) {
		i = preceive(tcps_oport);
		ptcb = &tcbtab[TCB(i)];
		if (ptcb->tcb_state <= TCPS_CLOSED)
			continue;		/* a rogue; ignore it	*/
		wait(ptcb->tcb_mutex);
		if (ptcb->tcb_state <= TCPS_CLOSED)
			continue;		/* TCB deallocated	*/
		if (EVENT(i) == DELETE)		/* same for all states	*/
			tcbdealloc(ptcb);
		else
			tcposwitch[ptcb->tcb_ostate](TCB(i), EVENT(i));
		if (ptcb->tcb_state != TCPS_FREE)
			signal(ptcb->tcb_mutex);
	}
}
