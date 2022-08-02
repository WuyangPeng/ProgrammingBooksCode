/* hgleave.c - hgleave */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <igmp.h>

/*------------------------------------------------------------------------
 *  hgleave  -  handle application request to leave a host group
 *------------------------------------------------------------------------
 */
int
hgleave(unsigned ifnum, IPaddr ipa)
{
	struct	hg	*phg;

	if (!IP_CLASSD(ipa))
		return SYSERR;
	wait(HostGroup.hi_mutex);
	if (!(phg = hglookup(ifnum, ipa)) || --(phg->hg_refs)) {
		signal(HostGroup.hi_mutex);
		return OK;
	}
	/* else, it exists & last reference */
	rtdel(ipa, ip_maskall);
	hgarpdel(ifnum, ipa);
	if (phg->hg_state == HGS_DELAYING)
		tmclear(HostGroup.hi_uport, phg);
	phg->hg_state = HGS_FREE;
	signal(HostGroup.hi_mutex);
	return OK;
}
