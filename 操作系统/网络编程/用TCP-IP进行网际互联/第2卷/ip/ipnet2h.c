/* ipnet2h.c - ipnet2h */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  ipnet2h - convert an IP packet header from net to host byte order
 *------------------------------------------------------------------------
 */
struct ip *
ipnet2h(struct ip *pip)
{
	/* NOTE: does not include IP options	*/

	pip->ip_len = net2hs(pip->ip_len);
	pip->ip_id = net2hs(pip->ip_id);
	pip->ip_fragoff = net2hs(pip->ip_fragoff);
	return pip;
}
