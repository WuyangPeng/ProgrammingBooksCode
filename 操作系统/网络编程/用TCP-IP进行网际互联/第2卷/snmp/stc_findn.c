/* stc_findn.c - stc_findnext, sntcpcmp */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP
#include <snmp.h>

/*------------------------------------------------------------------------
 * stc_findnext - search the TCP connection table for the next valid entry
 *------------------------------------------------------------------------
 */
int
stc_findnext(int tcbn)
{
	int	i, next;

	for (i = 0, next = -1; i < Ntcp; ++i) {
		if (tcbtab[i].tcb_state == TCPS_FREE ||
		   (tcbn >= 0 && sntcpcmp(i, tcbn) <= 0))
			continue;
		if (next < 0 || sntcpcmp(i, next) < 0)
			next = i;
	}
	return next;
}

/*------------------------------------------------------------------------
 * sntcpcmp - compare two TCP connections in SNMP lexical ordering
 *------------------------------------------------------------------------
 */
int
sntcpcmp(int tcb1, int tcb2)
{
	int	rv;

	if ((rv=(tcbtab[tcb1].tcb_lip - tcbtab[tcb2].tcb_lip)))
		return rv;
	if ((rv = (tcbtab[tcb1].tcb_lport - tcbtab[tcb2].tcb_lport)))
		return rv;
	if ((rv=(tcbtab[tcb1].tcb_rip - tcbtab[tcb2].tcb_rip)))
		return rv;
	if ((rv = (tcbtab[tcb1].tcb_rport - tcbtab[tcb2].tcb_rport)))
		return rv;
	return 0;
}
#endif	/* SNMP */
