/* tmclear.c - tmclear */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <tcptimer.h>
#include <mem.h>

/*------------------------------------------------------------------------
 *  tmclear -  clear the indicated timer
 *------------------------------------------------------------------------
 */
int
tmclear(int port, void *msg)
{
	struct	tqent	*prev, *ptq;
	int		timespent;

	wait(tqmutex);
	prev = 0;
	for (ptq = tqhead; ptq != NULL; ptq = ptq->tq_next) {
		if (ptq->tq_port == port && ptq->tq_msg == msg) {
			timespent = ctr100 - ptq->tq_time;
			if (prev)
				prev->tq_next = ptq->tq_next;
			else
				tqhead = ptq->tq_next;
			if (ptq->tq_next)
				ptq->tq_next->tq_timeleft +=
						ptq->tq_timeleft;
			signal(tqmutex);
			freemem(ptq, sizeof(struct tqent));
			return timespent;
		}
		prev = ptq;
	}
	signal(tqmutex);
	return SYSERR;
}
