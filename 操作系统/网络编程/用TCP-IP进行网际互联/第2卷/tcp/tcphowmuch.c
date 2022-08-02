/* tcphowmuch.c.c - tcphowmuch */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcphowmuch.c - compute how much data is available to send
 *------------------------------------------------------------------------
 */
int
tcphowmuch(struct tcb *ptcb)
{
	int	tosend;

	tosend = ptcb->tcb_suna + ptcb->tcb_sbcount - ptcb->tcb_snext;
	if (ptcb->tcb_code & TCPF_SYN)
		++tosend;
	if (ptcb->tcb_flags & TCBF_SNDFIN)
		++tosend;
	return tosend;
}
