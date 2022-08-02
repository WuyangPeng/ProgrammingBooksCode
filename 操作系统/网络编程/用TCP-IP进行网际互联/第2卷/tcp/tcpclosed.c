/* tcpclosed.c - tcpclosed */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpclosed -  do CLOSED state processing
 *------------------------------------------------------------------------
 */
int
tcpclosed(struct tcb *ptcb, struct ep *pep)
{
	tcpreset(pep);
	return	SYSERR;
}
