/* tcballoc.c - tcballoc */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 * tcballoc - allocate a Transmission Control Block
 *------------------------------------------------------------------------
 */
struct tcb *
tcballoc(void)
{
	struct	tcb	*ptcb;
	int		slot;

	wait(tcps_tmutex);
	/* look for a free TCB */

	for (ptcb=&tcbtab[0], slot=0; slot<Ntcp; ++slot, ++ptcb)
		if (ptcb->tcb_state == TCPS_FREE)
			break;
	if (slot < Ntcp) {
		ptcb->tcb_state = TCPS_CLOSED;
		ptcb->tcb_mutex = screate(0);
	} else 
		ptcb = (struct tcb *)SYSERR;
	signal(tcps_tmutex);
	return ptcb;
}
