/* ripok.c - ripok */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	RIP
/*------------------------------------------------------------------------
 *  ripok  -  determine if a received RIP route is ok to install
 *------------------------------------------------------------------------
 */
Bool
ripok(struct riprt *rp)
{
	u_char	net;

	if (rp->rr_family != AF_INET)
		return FALSE;
	if (rp->rr_metric > RIP_INFINITY)
		return FALSE;
	if (IP_CLASSD(rp->rr_ipa) || IP_CLASSE(rp->rr_ipa))
		return FALSE;
	net = (net2hl(rp->rr_ipa) & 0xff000000) >> 24;
	if (net == 0 && rp->rr_ipa != ip_anyaddr)
		return FALSE;		/* net 0, host non-0		*/
	if (net == 127)
		return FALSE;		/* loopback net			*/
	return TRUE;
}
#endif	/* RIP */
