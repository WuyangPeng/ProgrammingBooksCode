/* igmp_update.c - igmp_update */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ports.h>
#include <igmp.h>

/*------------------------------------------------------------------------
 *  igmp_update  -  send (delayed) IGMP host group updates
 *------------------------------------------------------------------------
 */
PROCESS
igmp_update(void)
{
	struct hg	*phg;

	HostGroup.hi_uport = pcreate(HG_TSIZE);
	while (1) {
		phg = (struct hg *)preceive(HostGroup.hi_uport);
		wait(HostGroup.hi_mutex);
		if (phg->hg_state == HGS_DELAYING) {
			phg->hg_state = HGS_IDLE;
			igmp(IGT_HREPORT, phg->hg_ifnum, phg->hg_ipa);
		}
		signal(HostGroup.hi_mutex);
	}
}
