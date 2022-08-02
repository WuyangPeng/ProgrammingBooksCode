/* ipgetp.c - ipgetp */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <proc.h>

static	int	ifnext = NI_LOCAL;

/*------------------------------------------------------------------------
 * ipgetp  --  choose next IP input queue and extract a packet
 *------------------------------------------------------------------------
 */
struct ep *
ipgetp(int *pifnum)
{
	struct	ep	*pep;
	int		i;

	recvclr();	/* make sure no old messages are waiting */
	while (TRUE) {
		for (i=0; i < Net.nif; ++i, ++ifnext) {
			if (ifnext >= Net.nif)
				ifnext = 0;
			if (nif[ifnext].ni_state == NIS_DOWN)
				continue;
			if (pep = NIGET(ifnext)) {
				*pifnum = ifnext;
				return pep;
			}
		}
		ifnext = receive();
	}
	/* can't reach here */
}
