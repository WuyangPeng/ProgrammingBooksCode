/* slowtimer.c - slowtimer */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <sleep.h>
#include <date.h>
#include <network.h>

#define	STGRAN	1		/* Timer granularity (delay) in seconds	*/

void arptimer(unsigned), ipftimer(unsigned), rttimer(unsigned);
#ifdef OSPF
void ospftimer(unsigned);
#endif /*OSPF*/

/*------------------------------------------------------------------------
 * slowtimer - handle long-term periodic maintenance of network tables
 *------------------------------------------------------------------------
 */
PROCESS
slowtimer(void)
{
	unsigned long	lasttime, now;	/* prev and current times (secs)*/
	int		delay;		/* actual delay in seconds	*/

	signal(Net.sema);

	gettime(&lasttime);
	while (1) {
		sleep(STGRAN);
		gettime(&now);
		delay = now - lasttime;
		if (delay <= 0 || delay > 4*STGRAN)
			delay = STGRAN;	/* likely clock reset */
		lasttime = now;
		arptimer(delay);
		ipftimer(delay);
		rttimer(delay);
#ifdef OSPF
		ospftimer(delay);
#endif /* OSPF */
	}
}
