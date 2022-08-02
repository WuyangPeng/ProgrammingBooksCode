/* x_timerq.c - x_timerq */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  x_timerq  -  command to print (TCP) timer queue
 *------------------------------------------------------------------------
 */
COMMAND	x_timerq(stdin, stdout, stderr, nargs, args)
int	stdin, stdout, stderr, nargs;
char	*args[];
{
	return tqwrite(stdout);
}
