/* udph2net.c - udph2net */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  udph2net -  convert UDP header fields from host to net byte order
 *------------------------------------------------------------------------
 */
void
udph2net(struct udp *pudp)
{
	pudp->u_src = hs2net(pudp->u_src);
	pudp->u_dst = hs2net(pudp->u_dst);
	pudp->u_len = hs2net(pudp->u_len);
}
