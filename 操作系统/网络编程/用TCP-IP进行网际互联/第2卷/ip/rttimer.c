/* rttimer.c - rttimer */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <network.h>

extern	Bool	dorip;		/* TRUE if we're running RIP output	*/
extern	int	rippid;		/* RIP output pid, if running		*/

/*------------------------------------------------------------------------
 * rttimer - update ttls and delete expired routes
 *------------------------------------------------------------------------
 */
void
rttimer(unsigned int delta)
{
	struct	route	*prt, *prev;
	Bool		ripnotify;
	int		i;

	if (!Route.ri_valid)
		return;
	wait(Route.ri_mutex);
	
	ripnotify = FALSE;
	for (i=0; i<RT_TSIZE; ++i) {
		if (rttable[i] == 0)
			continue;
		for (prev = NULL, prt = rttable[i]; prt != NULL;) {
			if (prt->rt_ttl != RT_INF)
				prt->rt_ttl -= delta;
			if (prt->rt_ttl <= 0) {
#ifdef	RIP
				if (dorip && prt->rt_metric < RTM_INF) {
					prt->rt_metric = RTM_INF;
					prt->rt_ttl = RIPZTIME;
					ripnotify = TRUE;
					continue;
				}
#endif	/* RIP */
				if (prev) {
					prev->rt_next = prt->rt_next;
					RTFREE(prt);
					prt = prev->rt_next;
				} else {
					rttable[i] = prt->rt_next;
					RTFREE(prt);
					prt = rttable[i];
				}
				continue;
			}
			prev = prt;
			prt = prt->rt_next;
		}
	}
	prt = Route.ri_default;
	if (prt && (prt->rt_ttl<RT_INF) && (prt->rt_ttl -= delta) <= 0) {
#ifdef	RIP
		if (dorip && prt->rt_metric < RTM_INF) {
			prt->rt_metric = RTM_INF;
			prt->rt_ttl = RIPZTIME;
		} else
#endif	/* RIP */
		{
			RTFREE(Route.ri_default);
			Route.ri_default = 0;
		}
	}
	signal(Route.ri_mutex);
#ifdef	RIP
	if (dorip && ripnotify)
		send(rippid, 0);	/* send anything but TIMEOUT	*/
#endif	/* RIP */
	return;
}
