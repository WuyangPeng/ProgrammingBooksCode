/* udpnet2h.c - udpnet2h */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  udpnet2h -  convert UDP header fields from net to host byte order
 *------------------------------------------------------------------------
 */
void
udpnet2h(struct udp *pudp)
{
	pudp->u_src = net2hs(pudp->u_src);
	pudp->u_dst = net2hs(pudp->u_dst);
	pudp->u_len = net2hs(pudp->u_len);
}
