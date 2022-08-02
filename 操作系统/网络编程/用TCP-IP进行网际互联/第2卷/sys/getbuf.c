/* getbuf.c - getbuf */

#include <conf.h>
#include <kernel.h>
#include <mark.h>
#include <bufpool.h>

/*------------------------------------------------------------------------
 *  getbuf  --  get a buffer from a preestablished buffer pool
 *------------------------------------------------------------------------
 */
void *
getbuf(unsigned poolid)
{
	STATWORD ps;    
	int	*buf, inuse;

#ifdef	MEMMARK
	if ( unmarked(bpmark) )
		return((void *) SYSERR);
#endif
	if (poolid>=nbpools)
		return((void *) SYSERR);
	wait(bptab[poolid].bpsem);
	inuse = bptab[poolid].bptotal - scount(bptab[poolid].bpsem);
	if (inuse > bptab[poolid].bpmaxused)
		bptab[poolid].bpmaxused = inuse;
	disable(ps);
	buf = (int *) bptab[poolid].bpnext;
	bptab[poolid].bpnext = (char *) *buf;
	restore(ps);
	*buf++ = poolid;
	return( (void *) buf );
}

/*------------------------------------------------------------------------
 * nbgetbuf - a non-blocking version of getbuf
 *------------------------------------------------------------------------
 */
int *nbgetbuf(poolid)
int poolid;
{
	STATWORD ps;    
	int	*buf;
	int	inuse;

#ifdef	MEMMARK
	if ( unmarked(bpmark) )
		return((int *) SYSERR);
#endif
	if (poolid<0 || poolid>=nbpools)
		return((int *) SYSERR);
	disable(ps);
	if (scount(bptab[poolid].bpsem) <= 0) {
		restore(ps);
		return 0;
	}
	wait(bptab[poolid].bpsem);	/* shouldn't block */
	inuse = bptab[poolid].bptotal - scount(bptab[poolid].bpsem);
	if (inuse > bptab[poolid].bpmaxused)
		bptab[poolid].bpmaxused = inuse;
	buf = (int *) bptab[poolid].bpnext;
	bptab[poolid].bpnext = (char *) *buf;
	restore(ps);
	*buf++ = poolid;
	return( (int *) buf );
}
