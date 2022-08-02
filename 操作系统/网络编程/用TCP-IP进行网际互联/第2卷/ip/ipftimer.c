/* ipftimer.c - ipftimer */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 * ipftimer - update time-to-live fields and delete expired fragments
 *------------------------------------------------------------------------
 */
void
ipftimer(int gran)
{
	struct	ep	*pep;
	struct	ip	*pip;
	int		i;

	wait(ipfmutex);
	for (i=0; i<IP_FQSIZE; ++i) {
		struct ipfq *iq = &ipfqt[i];

		if (iq->ipf_state == IPFF_FREE)
			continue;
		iq->ipf_ttl -= gran;
		if (iq->ipf_ttl <= 0) {
			if (iq->ipf_state == IPFF_BOGUS) {
				/* resources already gone */
				iq->ipf_state = IPFF_FREE;
				continue;
			}
			if (pep = (struct ep *)deq(iq->ipf_q)) {
				IpReasmFails++;
				pip = (struct ip *)pep->ep_data;
				icmp(ICT_TIMEX, ICC_FTIMEX,
					pip->ip_src, pep, 0);
			}
			while (pep = (struct ep *)deq(iq->ipf_q)) {
				IpReasmFails++;
				freebuf(pep);
			}
			freeq(iq->ipf_q);
			iq->ipf_state = IPFF_FREE;
		}
	}
	signal(ipfmutex);
}
