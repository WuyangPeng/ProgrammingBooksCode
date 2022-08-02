/* tcprmss.c - tcprmss */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcprmss - set receive MSS option
 *------------------------------------------------------------------------
 */
int
tcprmss(struct tcb *ptcb, struct ip *pip)
{
	struct	tcp	*ptcp = (struct tcp *)pip->ip_data;
	int		mss, hlen, olen, i;

	hlen = TCP_HLEN(ptcp);
	olen = 2 + sizeof(short);
	pip->ip_data[hlen] = TPO_MSS;		/* option kind		*/
	pip->ip_data[hlen+1] = olen;		/* option length	*/
	mss = ptcb->tcb_rmss;
	for (i=olen-1; i>1; i--) {
		pip->ip_data[hlen+i] = mss & LOWBYTE;
		mss >>= 8;
	}
	hlen += olen + 3;	/* +3 for proper rounding below */
	/* header length is high 4 bits of tcp_offset, in longs	*/
	ptcp->tcp_offset = ((hlen<<2) & 0xf0) | ptcp->tcp_offset & 0xf;
}
