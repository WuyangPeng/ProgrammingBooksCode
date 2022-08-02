/* tcpmopen.c - tcpmopen */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <proc.h>

int tcpserver(struct tcb *, u_short);
int tcpbind(struct tcb *, char *, u_short);
int tcpcon(struct tcb *);

/*------------------------------------------------------------------------
 *  tcpmopen  -  open a fresh TCP pseudo device and return descriptor
 *------------------------------------------------------------------------
 */
int
tcpmopen(struct devsw *pdev, void *fport0, void *lport0)
{
	char		*fport = (char *)fport0;
	int		lport = (int)lport0;
	struct	tcb	*ptcb;
	int		error;

	ptcb = (struct tcb *)tcballoc();
	if (ptcb == (struct tcb *)SYSERR)
		return SYSERR;
	ptcb->tcb_error = 0;
	proctab[currpid].ptcpumode = FALSE;
	if (fport == ANYFPORT)
		return tcpserver(ptcb, lport);

	if (tcpbind(ptcb, fport, lport) != OK ||
	    tcpsync(ptcb) != OK) {
		ptcb->tcb_state = TCPS_FREE;
		sdelete(ptcb->tcb_mutex);
		return SYSERR;
	}
	if (error = tcpcon(ptcb))
		return error;
	return ptcb->tcb_dvnum;
}
