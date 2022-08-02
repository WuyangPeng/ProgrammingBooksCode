/* tcpclose.c - tcpclose */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpclose - close a TCP connection
 *------------------------------------------------------------------------
 */
int
tcpclose(struct devsw *pdev)
{
	struct	tcb	*ptcb = (struct tcb *)pdev->dvioblk;
	int		error;

	wait(ptcb->tcb_mutex);
	switch (ptcb->tcb_state) {
	case TCPS_LISTEN:
	case TCPS_ESTABLISHED:
	case TCPS_CLOSEWAIT:
		break;
	case TCPS_FREE:
		return SYSERR;
	default:
		signal(ptcb->tcb_mutex);
		return SYSERR;
	}
	if (ptcb->tcb_error || ptcb->tcb_state == TCPS_LISTEN)
		return tcbdealloc(ptcb);
	/* to get here, we must be in ESTABLISHED or CLOSE_WAIT */

	TcpCurrEstab--;
	ptcb->tcb_flags |= TCBF_SNDFIN;
	ptcb->tcb_slast = ptcb->tcb_suna + ptcb->tcb_sbcount;
	if (ptcb->tcb_state == TCPS_ESTABLISHED)
		ptcb->tcb_state = TCPS_FINWAIT1;
	else	/* CLOSE_WAIT */
		ptcb->tcb_state = TCPS_LASTACK;
	ptcb->tcb_flags |= TCBF_NEEDOUT; 
	tcpkick(ptcb);
	signal(ptcb->tcb_mutex);
	wait(ptcb->tcb_ocsem);		/* wait for FIN to be ACKed	*/
	error = ptcb->tcb_error;
	if (ptcb->tcb_state == TCPS_LASTACK)
		tcbdealloc(ptcb);
	return error;
}
