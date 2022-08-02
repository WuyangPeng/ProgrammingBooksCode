/* tcpread.c - tcpread */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <network.h>

int tcpgetdata(struct tcb *, u_char *, unsigned);

/*------------------------------------------------------------------------
 *  tcpread  -  read one buffer from a TCP pseudo-device
 *------------------------------------------------------------------------
 */
int
tcpread(struct devsw *pdev, char *pch, unsigned len)
{
	struct	tcb	*ptcb = (struct tcb *)pdev->dvioblk;
	int		state = ptcb->tcb_state;
	int		cc;

	if (state != TCPS_ESTABLISHED && state != TCPS_CLOSEWAIT)
		return SYSERR;
retry:
	wait(ptcb->tcb_rsema);
	wait(ptcb->tcb_mutex);

	if (ptcb->tcb_state == TCPS_FREE)
		return SYSERR;			/* gone		*/
	if (ptcb->tcb_error) {
		tcpwakeup(READERS, ptcb);	/* propagate it */
		signal(ptcb->tcb_mutex);
		return ptcb->tcb_error;
	}
	if (ptcb->tcb_flags & TCBF_RUPOK) {
		if (!proctab[currpid].ptcpumode) {
			proctab[currpid].ptcpumode = TRUE;
			cc = TCPE_URGENTMODE;
		} else
			cc = tcpgetdata(ptcb, pch, len);
	} else {
		if (proctab[currpid].ptcpumode) {
			proctab[currpid].ptcpumode = FALSE;
			cc = TCPE_NORMALMODE;
		} else if (len > ptcb->tcb_rbcount &&
		    ptcb->tcb_flags & TCBF_BUFFER &&
		    (ptcb->tcb_flags & (TCBF_PUSH|TCBF_RDONE)) == 0) {
			signal(ptcb->tcb_mutex);
			goto retry;
		} else
			cc = tcpgetdata(ptcb, pch, len);
	}
	tcpwakeup(READERS, ptcb);
	signal(ptcb->tcb_mutex);
	return cc;
}
