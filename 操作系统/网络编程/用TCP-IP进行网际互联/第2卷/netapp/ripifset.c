/* ripifset.c - ripifset */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	RIP
/*------------------------------------------------------------------------
 * ripifset - set the per-interface data for a RIP update
 *------------------------------------------------------------------------
 */
int
ripifset(struct rq rqinfo[], IPaddr gw, unsigned short port)
{
	struct	route	*prt;
	int		ifn;

	if (gw != ip_maskall) {
		for (ifn=0; ifn<Net.nif; ++ifn)
			rqinfo[ifn].rq_active = FALSE;
		prt = rtget(gw, RTF_LOCAL);
		if (prt == 0)
			return SYSERR;
		ifn = prt->rt_ifnum;
		rtfree(prt);
		if (ifn == NI_LOCAL)
			return SYSERR;
		rqinfo[ifn].rq_ip = gw;
		rqinfo[ifn].rq_port = port;
		rqinfo[ifn].rq_active = TRUE;
		rqinfo[ifn].rq_cur = -1;
		rqinfo[ifn].rq_nrts = MAXRIPROUTES;
		return OK;
	}
	/* else, all interfaces */
	for (ifn=0; ifn<Net.nif; ++ifn) {
		rqinfo[ifn].rq_ip = nif[ifn].ni_brc;
		rqinfo[ifn].rq_port = port;
		rqinfo[ifn].rq_active = TRUE;
		rqinfo[ifn].rq_cur = -1;
		rqinfo[ifn].rq_nrts = MAXRIPROUTES;
	}
	rqinfo[NI_LOCAL].rq_active = FALSE;	/* never do this one	*/
	return OK;
}
#endif	/* RIP */
