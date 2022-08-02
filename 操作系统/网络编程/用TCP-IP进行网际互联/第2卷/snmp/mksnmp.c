/* mksnmp.c - mksnmp */

#include <conf.h>
#include <kernel.h>
#include <sleep.h>
#include <network.h>

#ifdef SNMP

#include <snmp.h>
#include <asn1.h>

char SNVCBACK[] = SNVCBACK_CHARS;
#define SNVCLEN 	sizeof(SNVCBACK) /* length of SNVCBACK 		*/



#define SNMAXHLEN	32	/* length of a "maximum" SNMP header	*/

u_char 	snmpbuff[SNMPMAXSZ];	/* global scratch buffer		*/

/*------------------------------------------------------------------------
 * mksnmp - make an snmp packet and return its length
 *------------------------------------------------------------------------
 */
int
mksnmp(struct req_desc *rqdp, u_char *snmppack, u_char pdutype)
{
	register u_char		*pp, *cp;
	struct 	snbentry	*bl;
	u_char			tmpbuff[40];
	int			len, mtu, estlen;

	pp = snmpbuff;
	if (rqdp->reqidlen == 0) {  /* if id len == 0, get new reqid	*/
		memcpy(rqdp->reqid, (char *) &clktime, sizeof(clktime));
		rqdp->reqidlen = sizeof(clktime);
	}
	snb2a(rqdp);	/* convert bindings to ASN.1 notation		*/

	/* check total length of the packet to be created		*/
	mtu = IP_MAXLEN;

	/* add up total length of ASN.1 representations of variables	*/
	for (estlen=0, bl=rqdp->bindlf; estlen<mtu && bl; bl=bl->sb_next) 
		estlen += bl->sb_a1slen;
	/*
	 * if too long, or if adding the header makes it too long,
	 * set error status to tooBig and return
	*/
	if (bl || (estlen + SNMAXHLEN >= mtu)) {
		rqdp->err_stat = SERR_TOO_BIG;
		rqdp->err_idx = 0;
		return SYSERR;
	}
	/* go backwards through snbentry, writing out the bindings	*/
	for (bl=rqdp->bindle; bl; bl=bl->sb_prev) {
		cp = &bl->sb_a1str[bl->sb_a1slen-1];
		while (cp >= bl->sb_a1str)
			*pp++ = *cp--;
	}
	/* write the length of the bindings and an ASN1_SEQ type	*/
	len = a1writelen(tmpbuff, pp - snmpbuff);
	for (cp = &tmpbuff[len-1]; cp >= tmpbuff; ) 
		*pp++ = *cp--;
	*pp++ = ASN1_SEQ;

	/* write the error index and error status -- 1 byte integers */
	*pp++ = (u_char) rqdp->err_idx;
	*pp++ = (u_char) 1;
	*pp++ = ASN1_INT;
	*pp++ = (u_char) rqdp->err_stat;
	*pp++ = (u_char) 1;
	*pp++ = ASN1_INT;

	/* write the request id, its length, and its type */
	for (cp = &rqdp->reqid[rqdp->reqidlen-1]; cp >= rqdp->reqid; )
		*pp++ = *cp--;
	*pp++ = rqdp->reqidlen;
	*pp++ = ASN1_INT;

	/* write the packet length and pdutype */
	len = a1writelen(tmpbuff, pp - snmpbuff);
	for (cp = &tmpbuff[len-1]; cp >= tmpbuff; )
		*pp++ = *cp--;
	*pp++ = pdutype;

	/* write the community and the version */
	memcpy(pp, SNVCBACK, SNVCLEN);
	pp += SNVCLEN;

	/* write the total packet length */
	len = a1writelen(tmpbuff, pp - snmpbuff);
	for (cp = &tmpbuff[len-1]; cp >= tmpbuff; )
		*pp++ = *cp--;
	*pp++ = ASN1_SEQ;

	/* reverse the entire finished packet */
	for (--pp, cp = snmppack; pp >= snmpbuff; )
		*cp++ = *pp--;
	return cp - snmppack;
}
#endif	/* SNMP */
