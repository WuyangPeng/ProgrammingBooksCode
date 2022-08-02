/* sud_findn.c - sud_findnext, snudpcmp */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>

/*------------------------------------------------------------------------
 * sud_findnext - search the UDP connection table for the next valid entry
 *------------------------------------------------------------------------
 */
int
sud_findnext(int udpn)
{
	int	i, next;


	for (i = 0, next = -1; i < UPPS; ++i) {
		if (!upqs[i].up_valid)
			continue;
		/* had one before, and this one isn't bigger */
		if ((udpn >= 0) &&
		    (upqs[i].up_port <= upqs[udpn].up_port))
			continue;
		/* haven't found one yet, or we did, but this one smaller */
		if ((next < 0) ||
		    (upqs[i].up_port < upqs[next].up_port))
			next = i;
	}
	return next;
}
#endif	/* SNMP */
