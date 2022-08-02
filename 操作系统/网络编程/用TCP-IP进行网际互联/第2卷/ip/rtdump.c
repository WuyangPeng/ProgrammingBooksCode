/* rtdump.c - rtdump */

#include <conf.h>
#include <kernel.h>
#include <sleep.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  rtdump  -  dump the routing table to the console
 *------------------------------------------------------------------------
 */
void
rtdump(void)
{
	struct route *srt;
	int	i;

	if (!Route.ri_valid)
		rtinit();
	wait(Route.ri_mutex);
	kprintf("net      mask     gateway  metric intf ttl  refs  use\n");
	for(i=0; i<RT_TSIZE; ++i) {
		for (srt=rttable[i]; srt != NULL; srt=srt->rt_next)
			kprintf("%08X %08X %08X %4d    %1d %4d %4d %4d\n",
				*((int *)srt->rt_net),
				*((int *)srt->rt_mask),
				*((int *)srt->rt_gw),
				srt->rt_metric,
				srt->rt_ifnum,
				srt->rt_ttl,
				srt->rt_refcnt,
				srt->rt_usecnt);
	}
	if (Route.ri_default)
		kprintf("%08X %08X %08X %4d    %1d %4d %4d %4d\n",
			*((int *)Route.ri_default->rt_net),
			*((int *)Route.ri_default->rt_mask),
			*((int *)Route.ri_default->rt_gw),
			Route.ri_default->rt_metric,
			Route.ri_default->rt_ifnum,
			Route.ri_default->rt_ttl,
			Route.ri_default->rt_refcnt,
			Route.ri_default->rt_usecnt);
	signal(Route.ri_mutex);
}
