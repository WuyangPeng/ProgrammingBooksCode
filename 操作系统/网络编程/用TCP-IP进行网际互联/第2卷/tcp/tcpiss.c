/* tcpiss.c - tcpiss */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#define	TCPINCR		904

/*------------------------------------------------------------------------
 *  tcpiss -  set the ISS for a new connection
 *------------------------------------------------------------------------
 */
int
tcpiss(void)
{
	static	int	seq = 0;
	extern	long	clktime;		/* the system ticker	*/

	if (seq == 0)
		seq = clktime;
	seq += TCPINCR;
	return seq;
}
