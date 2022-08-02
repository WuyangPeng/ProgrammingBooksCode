/* tcpbind.c - tcpbind */

#include <conf.h>
#include <kernel.h>
#include <network.h>

u_short tcpnxtp(void);

/*------------------------------------------------------------------------
 *  tcpbind - bind a TCP pseudo device to its addresses and port
 *------------------------------------------------------------------------
 */
int
tcpbind(struct tcb *ptcb, char *fport, u_short lport)
{
	struct	route	*prt;
	struct	tcb	*ptcb2;
	int		slot;

	if (dnparse(fport, &ptcb->tcb_rip, &ptcb->tcb_rport) == SYSERR)
		return SYSERR;
	prt = rtget(ptcb->tcb_rip, RTF_LOCAL);
	if (prt == 0)
		return SYSERR;
	if (prt->rt_ifnum == NI_LOCAL)
		ptcb->tcb_lip = ptcb->tcb_rip;
	else
		ptcb->tcb_lip = nif[prt->rt_ifnum].ni_ip;
	ptcb->tcb_pni = &nif[prt->rt_ifnum];
	rtfree(prt);
	if (lport == ANYLPORT) {
		ptcb->tcb_lport = tcpnxtp();	/* pick one */
		return OK;
	}
	ptcb->tcb_lport = lport;
	for (slot=0, ptcb2=&tcbtab[0]; slot<Ntcp; ++slot, ++ptcb2) {
		if (ptcb == ptcb2 ||
		    ptcb2->tcb_state == TCPS_FREE ||
		    ptcb->tcb_rport != ptcb2->tcb_rport ||
		    ptcb->tcb_lport != ptcb2->tcb_lport ||
		    ptcb->tcb_rip != ptcb2->tcb_rip ||
		    ptcb->tcb_lip != ptcb2->tcb_lip)
			continue;
		return SYSERR;
	}
	return OK;
}
