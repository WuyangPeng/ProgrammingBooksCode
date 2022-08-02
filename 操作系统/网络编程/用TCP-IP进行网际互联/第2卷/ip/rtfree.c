/* rtfree.c - rtfree */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  rtfree  -  remove one reference to a route
 *------------------------------------------------------------------------
 */
int
rtfree(struct route *prt)
{
	if (!Route.ri_valid)
		return SYSERR;
	wait(Route.ri_mutex);
	RTFREE(prt);
	signal(Route.ri_mutex);
	return OK;
}
