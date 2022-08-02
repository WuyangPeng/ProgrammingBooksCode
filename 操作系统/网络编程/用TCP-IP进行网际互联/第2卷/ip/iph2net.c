/* iph2net.c - iph2net */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  iph2net - convert an IP packet header from host to net byte order
 *------------------------------------------------------------------------
 */
struct ip *
iph2net(struct ip *pip)
{
	/* NOTE: does not include IP options	*/

	pip->ip_len = hs2net(pip->ip_len);
	pip->ip_id = hs2net(pip->ip_id);
	pip->ip_fragoff = hs2net(pip->ip_fragoff);
	return pip;
}
