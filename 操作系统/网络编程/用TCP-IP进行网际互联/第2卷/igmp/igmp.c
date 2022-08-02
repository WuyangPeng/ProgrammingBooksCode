/* igmp.c - igmp */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <igmp.h>

/*------------------------------------------------------------------------
 *  igmp  -  send IGMP requests/responses
 *------------------------------------------------------------------------
 */
int
igmp(int typ, unsigned ifnum, IPaddr hga)
{
	struct	ep	*pep;
	struct	ip	*pip;
	struct	igmp	*pig;

	pep = (struct ep *)getbuf(Net.netpool);
	if (pep == (struct ep *)SYSERR)
		return SYSERR;
	pip = (struct ip *)pep->ep_data;
	pig = (struct igmp *) pip->ip_data;
	pig->ig_vertyp = (IG_VERSION<<4) | (typ & 0xf);
	pig->ig_unused = 0;
	pig->ig_cksum = 0;
	pig->ig_gaddr = hga;
	pig->ig_cksum = cksum((WORD *)pig, IG_HLEN>>1);

	ipsend(hga, pep, IG_HLEN, IPT_IGMP, IPP_INCTL, 1);
	return OK;
}

/* special IGMP-relevant address & mask */

#if	BYTE_ORDER == LITTLE_ENDIAN
IPaddr	ig_allhosts = 0x010000E0; 		/* 224.0.0.1 */
IPaddr  ig_allDmask = 0xF0;		/* 240.0.0.0 */
#else	/* BYTE_ORDER */
IPaddr	ig_allhosts = 0xE0000001; 	/* 224.0.0.1 */
IPaddr  ig_allDmask = 0xF0000000;	/* 240.0.0.0 */
#endif	/* BYTE_ORDER */
