/* sdelete.c - sdelete */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>

extern struct sema_stat sema_stat;

/*------------------------------------------------------------------------
 * sdelete  --  delete a semaphore by releasing its table entry
 *------------------------------------------------------------------------
 */
SYSCALL sdelete(sem)
	int	sem;
{
	STATWORD ps;    
	int	pid;
	struct	sentry	*sptr;

	disable(ps);
	if (isbadsem(sem) || semaph[sem].sstate==SFREE) {
		restore(ps);
		return(SYSERR);
	}
	sptr = &semaph[sem];
	sptr->sstate = SFREE;
	sema_stat.inuse--;
	if (sema_stat.inuse < 0)
		panic("sdelete(%d)\n", sem);
	if (nonempty(sptr->sqhead)) {
		while( (pid=getfirst(sptr->sqhead)) != EMPTY)
			ready(pid,RESCHNO);
		resched();
	}
	restore(ps);
	return(OK);
}
