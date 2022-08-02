/* udpdump.c - udpdump */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 * udpdump - pretty-print a UDP packet to the console
 *------------------------------------------------------------------------
 */
udpdump(pudp, dlen, order)
struct udp	*pudp;
int		dlen;
int		order;
{
	unsigned short	u_src, u_dst, u_len, u_cksum;

	if (order & EPO_UDP) {
		u_src = pudp->u_src;
		u_dst = pudp->u_dst;
		u_len = pudp->u_len;
		u_cksum = pudp->u_cksum;
	} else {
		u_src = hs2net(pudp->u_src);
		u_dst = hs2net(pudp->u_dst);
		u_len = hs2net(pudp->u_len);
		u_cksum = hs2net(pudp->u_cksum);
	}
	kprintf("UDP:\tsrc %5u dst %5u len %d cksum %04x\n",
		u_src,u_dst, u_len, u_cksum);
	hexdump((char *)pudp+U_HLEN, dlen - U_HLEN);
}
