/* arpalloc.c - arpalloc */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <network.h>

void arpdq(struct arpentry *);

/*------------------------------------------------------------------------
 * arpalloc - allocate an entry in the ARP table
 *	N.B. Assumes interrupts DISABLED
 *------------------------------------------------------------------------
 */
struct arpentry *arpalloc()
{
	static	int	aenext = 0;
	struct	arpentry *pae;
	int	i;

	for (i=0; i<ARP_TSIZE; ++i) {
		if (arptable[aenext].ae_state == AS_FREE)
			break;
		aenext = (aenext + 1) % ARP_TSIZE;
	}
	pae = & arptable[aenext];
	aenext = (aenext + 1) % ARP_TSIZE;

	if (pae->ae_state == AS_PENDING && pae->ae_queue >= 0)
		arpdq(pae);
	pae->ae_state = AS_PENDING;
	return pae;
}
