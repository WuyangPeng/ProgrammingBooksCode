/* snb2a.c - snb2a */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <mem.h>

#ifdef	 SNMP

#include <snmp.h>
#include <asn1.h>

extern u_char snmpbuff[];

/*------------------------------------------------------------------------
 * snb2a - convert the list of bindings from internal form into ASN.1
 *------------------------------------------------------------------------
 */
int
snb2a(struct req_desc *rqdp)
{
	register u_char *bp;
	int		len;
	struct snbentry	*bl;
	u_char		*ap;

	for (bl = rqdp->bindlf; bl; bl = bl->sb_next) {
		bp = snmpbuff;	/* used for temporary working space */
		*bp++ = ASN1_OBJID;
		bp += a1writeoid(bp, &bl->sb_oid);
		bp += a1writeval(bl, bp);
		/*
		 * We need to allocate bytes in sb_a1str but can't do it
		 * until we know how many bytes it takes to write the
		 * length of the binding,  so we write that length into
		 * snmpbuff at the end of the binding. Then we can alloc
		 * space, and transfer the data.
		 */
		len = a1writelen(bp, bp - snmpbuff);
		bl->sb_a1slen = bp - snmpbuff + len + 1;
		ap = bl->sb_a1str = (u_char *) getmem(bl->sb_a1slen);
		bl->sb_a1dynstr = TRUE;	/* dynamically allocated */
		*ap++ = ASN1_SEQ;
		memcpy(ap, bp, len);  /* write in the length spec.	*/
		ap += len;
		memcpy(ap, snmpbuff, bp - snmpbuff);
	}
	return OK;
}
#endif	/* SNMP */
