/* ptclear.c - _ptclear */

#include <conf.h>
#include <kernel.h>
#include <mark.h>
#include <ports.h>

/*------------------------------------------------------------------------
 *  _ptclear  --  used by pdelete and preset to clear a port
 *------------------------------------------------------------------------
 */
_ptclear(struct pt *ppt, int newstate, void (*dispose)())
{
	struct	ptnode	*p;

	/* put port in limbo until done freeing processes */
	ppt->ptstate = PTLIMBO;
	ppt->ptseq++;
	if ( (p=ppt->pthead) != (struct ptnode *)NULL ) {
		if (dispose != PTNODISP)
			for(; p != (struct ptnode *) NULL ; p=p->ptnext)
				(*dispose)( p->ptmsg );
		(ppt->pttail)->ptnext = ptfree;
		ptfree = ppt->pthead;
	}
	if (newstate == PTALLOC) {
		ppt->pttail = ppt->pthead = (struct ptnode *) NULL;
		sreset(ppt->ptssem, ppt->ptmaxcnt);
		sreset(ppt->ptrsem, 0);
	} else {
		sdelete(ppt->ptssem);
		sdelete(ppt->ptrsem);
	}
	ppt->ptstate = newstate;
}
