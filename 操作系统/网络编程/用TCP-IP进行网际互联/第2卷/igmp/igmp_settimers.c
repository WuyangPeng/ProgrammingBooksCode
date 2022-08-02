/* igmp_settimers.c - igmp_settimers */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <igmp.h>

/*------------------------------------------------------------------------
 *  igmp_settimers  -  generate timer events to send IGMP reports
 *------------------------------------------------------------------------
 */
int
igmp_settimers(unsigned ifnum)
{
	int		i;

	wait(HostGroup.hi_mutex);
	for (i=0; i<HG_TSIZE; ++i) {
		struct hg	*phg = &hgtable[i];
		if (phg->hg_state != HGS_IDLE || phg->hg_ifnum != ifnum)
			continue;
		phg->hg_state = HGS_DELAYING;
		tmset(HostGroup.hi_uport, HG_TSIZE, phg, hgrand());
	}
	signal(HostGroup.hi_mutex);
	return OK;
}
