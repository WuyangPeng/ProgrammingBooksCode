/* tcpwait.c - tcpwait */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpwait - (re)schedule a DELETE event for 2MSL from now
 *------------------------------------------------------------------------
 */
int
tcpwait(struct tcb *ptcb)
{
	int	tcbnum = ptcb - &tcbtab[0];

	tcpkilltimers(ptcb);
	tmset(tcps_oport, TCPQLEN, MKEVENT(DELETE, tcbnum), TCP_TWOMSL);
	return OK;
}
