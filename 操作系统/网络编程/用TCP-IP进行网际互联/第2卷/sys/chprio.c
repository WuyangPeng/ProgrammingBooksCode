/* chprio.c - chprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>

/*------------------------------------------------------------------------
 * chprio  --  change the scheduling priority of a process
 *------------------------------------------------------------------------
 */
SYSCALL
chprio(int pid, unsigned newprio)
{
	STATWORD ps;    
	int	oldprio;
	struct	pentry	*pptr;

	disable(ps);
	if (isbadpid(pid) ||
	    (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		return SYSERR;
	}
	oldprio = pptr->pprio;
	pptr->pprio = newprio;
	switch (pptr->pstate) {
	case PRREADY:
		insert( dequeue(pid), rdyhead, newprio);
	case PRCURR:
		resched();
	default:
		break;
	}
	restore(ps);
	return oldprio;
}
