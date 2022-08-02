/* hginit.c - hginit */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <sleep.h>
#include <network.h>
#include <igmp.h>

extern	int	hgseed;
struct	hginfo	HostGroup;
struct	hg	hgtable[HG_TSIZE];

/*------------------------------------------------------------------------
 *  hginit  -  initialize the host group table
 *------------------------------------------------------------------------
 */
void
hginit(void)
{
	int i;

	HostGroup.hi_mutex = screate(0);
	HostGroup.hi_valid = TRUE;
	resume(create(igmp_update, IGUSTK, IGUPRI, IGUNAM, IGUARGC));
	for (i=0; i<HG_TSIZE; ++i)
		hgtable[i].hg_state = HGS_FREE;
	hgseed = nif[NI_PRIMARY].ni_ip;
	signal(HostGroup.hi_mutex);
	rtadd(ig_allhosts, ig_allDmask, ig_allhosts, 0, NI_PRIMARY,
		RT_INF);
	hgjoin(NI_PRIMARY, ig_allhosts, TRUE);
}
