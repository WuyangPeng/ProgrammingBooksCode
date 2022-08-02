/* tcpuopt.c - tcpuopt, ISUOPT */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#define ISUOPT(flags)	(!((flags) & ~(TCBF_DELACK|TCBF_BUFFER)))

/*------------------------------------------------------------------------
 *  tcpuopt - set/clear TCP user option flags  
 *------------------------------------------------------------------------
 */
int
tcpuopt(struct tcb *ptcb, u_int func, u_int flags)
{
	if (!ISUOPT(flags))
		return SYSERR;
	if (func == TCPC_SOPT)
		ptcb->tcb_flags |= flags;
	else
		ptcb->tcb_flags &= ~flags;
	return OK;
}
