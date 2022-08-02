/* tcpsync.c - tcpsync */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <mem.h>

/*------------------------------------------------------------------------
 *  tcpsync - initialize TCB for a new connection request
 *------------------------------------------------------------------------
 */
int
tcpsync(struct tcb *ptcb)
{
	ptcb->tcb_state = TCPS_CLOSED;
	ptcb->tcb_type = TCPT_CONNECTION;

	ptcb->tcb_iss = ptcb->tcb_suna = ptcb->tcb_snext = tcpiss();
	ptcb->tcb_lwack = ptcb->tcb_iss;

	ptcb->tcb_sndbuf = (u_char *)getmem(TCPSBS);
	ptcb->tcb_sbsize = TCPSBS;
	ptcb->tcb_sbstart = ptcb->tcb_sbcount = 0;
	ptcb->tcb_ssema = screate(1);

	ptcb->tcb_rcvbuf = (u_char *)getmem(TCPRBS);
	ptcb->tcb_rbsize = TCPRBS;
	ptcb->tcb_rbstart = ptcb->tcb_rbcount = 0;
	ptcb->tcb_rsegq = EMPTY;
	ptcb->tcb_rsema = screate(0);
	ptcb->tcb_ocsem = screate(0);

	/* timer stuff */

	ptcb->tcb_srt = 0;		/* in sec/100	*/
	ptcb->tcb_rtde = 0;		/* in sec/100	*/
	ptcb->tcb_rexmt = 50;		/* in sec/100	*/
	ptcb->tcb_rexmtcount = 0;
	ptcb->tcb_keep = 12000;		/* in sec/100	*/

	ptcb->tcb_code = TCPF_SYN;
	ptcb->tcb_flags = 0;
	return OK;
}
