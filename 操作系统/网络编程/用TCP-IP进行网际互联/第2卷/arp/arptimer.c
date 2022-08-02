/* arptimer.c - arptimer */

#include <conf.h>
#include <kernel.h>
#include <network.h>

void	arpdq(struct arpentry *);
int	arpsend(struct arpentry *);

/*------------------------------------------------------------------------
 * arptimer - Iterate through ARP cache, aging (possibly removing) entries
 *------------------------------------------------------------------------
 *	gran	- time since last iteration
 */
void
arptimer(int gran)
{
	struct arpentry *pae;
	STATWORD	ps;
	int		i;

	disable(ps);	/* mutex */

	for (i=0; i<ARP_TSIZE; ++i) {
		if ((pae = &arptable[i])->ae_state == AS_FREE)
			continue;
		if (pae->ae_ttl == ARP_INF)
			continue; /* don't time out permanent entry */
		if ((pae->ae_ttl -= gran) <= 0)
			if (pae->ae_state == AS_RESOLVED)
				pae->ae_state = AS_FREE;
			else if (++pae->ae_attempts > ARP_MAXRETRY) {
				pae->ae_state = AS_FREE;
				arpdq(pae);
			} else {
				pae->ae_ttl = ARP_RESEND;
				arpsend(pae);
			}
	}
	restore(ps);
}
