/* tmleft.c - tmleft */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <tcptimer.h>

/*------------------------------------------------------------------------
 *  tmleft -  how much time left for this timer?
 *------------------------------------------------------------------------
 */
int
tmleft(int port, void *msg)
{
	struct	tqent	*tq;
	int		timeleft = 0;

	if (tqhead == NULL)
		return 0;
	wait(tqmutex);
	for (tq = tqhead; tq != NULL; tq = tq->tq_next) {
		timeleft += tq->tq_timeleft;
		if (tq->tq_port == port && tq->tq_msg == msg) {
			signal(tqmutex);
			return timeleft;
		}
	}
	signal(tqmutex);
	return 0;
}
