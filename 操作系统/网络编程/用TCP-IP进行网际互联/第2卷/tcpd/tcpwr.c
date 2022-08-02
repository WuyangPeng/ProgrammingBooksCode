/* tcpwr.c - tcpwr */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <network.h>

int tcpgetspace(struct tcb *, unsigned);

/*------------------------------------------------------------------------
 *  tcpwr  -  write urgent and normal data to TCP buffers
 *------------------------------------------------------------------------
 */
int
tcpwr(struct devsw *pdev, u_char *pch, unsigned len, Bool isurg)
{
	struct	tcb	*ptcb = (struct tcb *)pdev->dvioblk;
	int		state = ptcb->tcb_state;
	unsigned	sboff;
	int		tocopy;

	if (state != TCPS_ESTABLISHED && state != TCPS_CLOSEWAIT)
		return SYSERR;
	tocopy = tcpgetspace(ptcb, len);	/* acquires tcb_mutex	*/
	if (tocopy <= 0)
		return tocopy;
	sboff = (ptcb->tcb_sbstart+ptcb->tcb_sbcount) % ptcb->tcb_sbsize;
	if (isurg) {
		ptcb->tcb_supseq = ptcb->tcb_snext + len - 1;
		ptcb->tcb_flags |= TCBF_SUPOK;
	}
	while (tocopy--) {
		ptcb->tcb_sndbuf[sboff] = *pch++;
		++ptcb->tcb_sbcount;
		if (++sboff >= ptcb->tcb_sbsize)
			sboff = 0;
	}
	ptcb->tcb_flags |= TCBF_NEEDOUT;
	tcpwakeup(WRITERS, ptcb);
	signal(ptcb->tcb_mutex);

	if (isurg || ptcb->tcb_snext == ptcb->tcb_suna)
		tcpkick(ptcb);
	return len;
}
