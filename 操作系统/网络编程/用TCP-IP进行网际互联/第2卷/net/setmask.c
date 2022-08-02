/* setmask.c - setmask */

#include <conf.h>
#include <kernel.h>
#include <network.h>

extern	int	bsdbrc;		/* use Berkeley (all-0's) broadcast	*/
/*------------------------------------------------------------------------
 *  setmask - set the net mask for an interface
 *------------------------------------------------------------------------
 */
int
setmask(unsigned ifn, IPaddr mask)
{
	IPaddr	defmask;

	if (nif[ifn].ni_svalid) {
		/* one set already-- fix things */

		rtdel(nif[ifn].ni_subnet, nif[ifn].ni_mask);
		rtdel(nif[ifn].ni_brc, ip_maskall);
		rtdel(nif[ifn].ni_subnet, ip_maskall);
	}
	nif[ifn].ni_mask = mask;
	nif[ifn].ni_svalid = TRUE;
	defmask = netmask(nif[ifn].ni_ip);

	nif[ifn].ni_subnet = nif[ifn].ni_ip & nif[ifn].ni_mask; 
	if (bsdbrc)
		nif[ifn].ni_brc = nif[ifn].ni_subnet;
	else
		nif[ifn].ni_brc = nif[ifn].ni_subnet |
				~nif[ifn].ni_mask;
	/* set network (not subnet) broadcast */
	nif[ifn].ni_nbrc = nif[ifn].ni_ip | ~defmask;

	/* install routes */
	/* net */
	rtadd(nif[ifn].ni_subnet, nif[ifn].ni_mask, nif[ifn].ni_ip,
		0, ifn, RT_INF);
	if (bsdbrc) {
		IPaddr	aobrc;		/* all 1's broadcast */

		aobrc = nif[ifn].ni_subnet | ~nif[ifn].ni_mask;
		rtadd(aobrc, ip_maskall, nif[ifn].ni_ip, 0,
			NI_LOCAL, RT_INF);
	} else	/* broadcast (all 1's) */
		rtadd(nif[ifn].ni_brc, ip_maskall, nif[ifn].ni_ip, 0,
			NI_LOCAL, RT_INF);
	/* broadcast (all 0's) */
	rtadd(nif[ifn].ni_subnet, ip_maskall, nif[ifn].ni_ip, 0,
		NI_LOCAL, RT_INF);
	return OK;
}

IPaddr	ip_maskall = 0xffffffff;
