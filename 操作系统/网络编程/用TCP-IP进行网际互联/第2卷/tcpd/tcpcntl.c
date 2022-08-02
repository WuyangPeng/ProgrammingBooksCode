/* tcpcntl.c - tcpcntl */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ports.h>

int tcpuopt(struct tcb *, int, u_int);

/*------------------------------------------------------------------------
 *  tcpcntl - control function for TCP pseudo-devices
 *------------------------------------------------------------------------
 */
int
tcpcntl(struct devsw *pdev, int func, void *arg, void *arg2)
{
	struct	tcb	*ptcb = (struct tcb *)pdev->dvioblk;
	int		rv;

	if (ptcb == NULL || ptcb->tcb_state == TCPS_FREE)
		return SYSERR;

	wait(ptcb->tcb_mutex);
	if (ptcb->tcb_state == TCPS_FREE) /* verify no state change */
		return SYSERR;

	switch (func) {
	case TCPC_ACCEPT:	if (ptcb->tcb_type != TCPT_SERVER) {
					rv = SYSERR;
					break;
				}
				signal(ptcb->tcb_mutex);
				return preceive(ptcb->tcb_listenq);
	case TCPC_LISTENQ:	rv = tcplq(ptcb, (int)arg);
				break;
	case TCPC_STATUS:	rv = tcpstat(ptcb, (struct tcpstat *)arg);
				break;
	case TCPC_SOPT:
	case TCPC_COPT:		rv = tcpuopt(ptcb, func, (u_int)arg);
				break;
	case TCPC_SENDURG:	/*
				 * tcpwr acquires and releases tcb_mutex
				 * itself.
				 */
				signal(ptcb->tcb_mutex);
				return tcpwr(pdev, (u_char *)arg,
					(unsigned)arg2, TWF_URGENT);
	default:
		rv = SYSERR;
	}
	signal(ptcb->tcb_mutex);
	return rv;
}
