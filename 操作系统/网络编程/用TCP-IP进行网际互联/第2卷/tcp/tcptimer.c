/* tcptimer.c - tcptimer */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <tcptimer.h>
#include <sleep.h>
#include <ports.h>
#include <mem.h>
#include <proc.h>

int	tqmutex;
int	tqpid;
struct	tqent	*tqhead;


/*------------------------------------------------------------------------
 *  tcptimer -  TCP timer process
 *------------------------------------------------------------------------
 */
PROCESS
tcptimer(void)
{
	long	now, lastrun;		/* times from system clock	*/
	int	delta;			/* time since last iteration	*/
	struct	tqent	*tq;		/* temporary delta list ptr	*/

	lastrun = ctr100;		/* initialize to "now"		*/
	tqmutex = screate(1);		/* mutual exclusion semaphore	*/
	tqpid = getpid();		/* record timer process id	*/
	signal(Net.sema);		/* start other network processes*/

	while (TRUE) {
		sleep10(TIMERGRAN);	/* real-time delay		*/
		if (tqhead == 0)	/* block timer process if delta	*/
			suspend(tqpid);	/*   list is empty		*/

		wait(tqmutex);
		now = ctr100;
		delta = now - lastrun;	/* compute elapsed time		*/

		/* Note: check for possible clock reset (time moved	*/
		/* backward or delay was over an order of magnitude too	*/
		/* long)						*/

		if (delta < 0 || delta > TIMERGRAN*100)
			delta = TIMERGRAN*10;	/* estimate the delay	*/
		lastrun = now;
		while (tqhead != 0  &&  tqhead->tq_timeleft <= delta) {
			delta -= tqhead->tq_timeleft;
			if (pcount(tqhead->tq_port) <= tqhead->tq_portlen)
				psend(tqhead->tq_port,
					(int)tqhead->tq_msg);
			tq = tqhead;
			tqhead = tqhead->tq_next;
			freemem(tq, sizeof(struct tqent));
		}
		if (tqhead)
			tqhead->tq_timeleft -=delta;
		signal(tqmutex);
	}
}
