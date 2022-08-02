/* dgwrite.c - dgwrite */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  dgwrite  -  write one datagram to a datagram pseudo-device
 *------------------------------------------------------------------------
 */
int
dgwrite(struct devsw *pdev, unsigned char *pxg0, unsigned len)
{
	struct	xgram	*pxg = (struct xgram *)pxg0;
	struct	ep	*pep;
	struct	ip	*pip;
	struct	udp	*pudp;
	struct	dgblk	*pdg;
	int		ipa;
	int		dst;		/* destination UDP port		*/

	if (len > U_MAXLEN)
		return SYSERR;
	pdg = (struct dgblk *) pdev->dvioblk;
	pep = (struct ep *) getbuf(Net.netpool);
	if ((int)pep == SYSERR)
		return SYSERR;
	pep->ep_order = ~0;
	pip = (struct ip *) pep->ep_data;
	pudp = (struct udp *) pip->ip_data;
	dst = pdg->dg_fport;
	ipa = pdg->dg_fip;
	if ((pdg->dg_mode & DG_NMODE) != 0) {
		if (dst == 0) {
			dst = pxg->xg_fport;
			ipa = pxg->xg_fip;
		}
		memcpy(pudp->u_data, pxg->xg_data, len);
	} else {
		if ( dst == 0) {
			freebuf(pep);
			return SYSERR;
		}
		memcpy(pudp->u_data, pxg, len);
	}
	return udpsend(ipa, dst, pdg->dg_lport, pep, len,
		pdg->dg_mode & DG_CMODE);
}
