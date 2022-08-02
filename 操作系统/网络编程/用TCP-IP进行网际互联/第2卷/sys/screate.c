/* screate.c - screate, newsem */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>

static newsem(void);
struct sema_stat sema_stat;

/*------------------------------------------------------------------------
 * screate  --  create and initialize a semaphore, returning its id
 *------------------------------------------------------------------------
 */
SYSCALL
screate(unsigned count)
{
	STATWORD ps;    
	int	sem;

	disable(ps);
	if ((sem=newsem())==SYSERR) {
		sema_stat.failures++;
		restore(ps);
		return(SYSERR);
	}
	semaph[sem].semcnt = count;
	/* sqhead and sqtail were initialized at system startup */
	sema_stat.inuse++;
	if (sema_stat.inuse > sema_stat.maxuse)
		sema_stat.maxuse = sema_stat.inuse;
	restore(ps);
	return sem;
}

/*------------------------------------------------------------------------
 * newsem  --  allocate an unused semaphore and return its index
 *------------------------------------------------------------------------
 */
static int
newsem()
{
	int	sem;
	int	i;

	for (i=0 ; i<NSEM ; i++) {
		sem=nextsem--;
		if (nextsem < 0)
			nextsem = NSEM-1;
		if (semaph[sem].sstate==SFREE) {
			semaph[sem].sstate = SUSED;
			return(sem);
		}
	}
	return(SYSERR);
}
