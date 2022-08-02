/* hgjoin.c - hgjoin */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <sleep.h>
#include <igmp.h>

/*------------------------------------------------------------------------
 *  hgjoin  -  handle application request to join a host group
 *------------------------------------------------------------------------
 */
int
hgjoin(unsigned ifnum, IPaddr ipa, Bool islocal)
{
	struct	hg	*phg;
	int		i;

	if (!IP_CLASSD(ipa))
		return SYSERR;
	/* restrict multicast in multi-homed host to primary interface */
	if (ifnum != NI_PRIMARY)
		return SYSERR;
	wait(HostGroup.hi_mutex);
	if (phg = hglookup(ifnum, ipa)) {
		phg->hg_refs++;
		signal(HostGroup.hi_mutex);
		return OK;	/* already in it */
	}
	signal(HostGroup.hi_mutex);
	/* add to host group and routing tables */
	if (hgadd(ifnum, ipa, islocal) == SYSERR)
		return SYSERR;
	rtadd(ipa, ip_maskall, ipa, 0, NI_LOCAL, RT_INF);
	/*
	 * advertise membership to multicast router(s); don't advertise
	 * 224.0.0.1 (all multicast hosts) membership.
	 */
	if (ipa != ig_allhosts)
		for (i=0; i < IG_NSEND; ++i) {
			igmp(IGT_HREPORT, ifnum, ipa);
			sleep10(IG_DELAY);
		}
	return OK;
}
