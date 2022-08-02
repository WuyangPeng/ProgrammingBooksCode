/* sna2b.c - sna2b */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <asn1.h>

/*------------------------------------------------------------------------
 * sna2b - convert an ASN.1 encoded binding into internal form
 *------------------------------------------------------------------------
 */
int
sna2b(struct req_desc *rqdp)
{
	register u_char	*sp;
	struct snbentry *bl;
	int 		lenlen, objidlen, vallen;
	u_char 		type;
	
	for (bl = rqdp->bindlf; bl; bl = bl->sb_next) {
		sp = bl->sb_a1str;
		/* match the sequence operator and length of bindings */
		if (*sp++ != ASN1_SEQ ||
		    a1readlen(sp, (unsigned *)&lenlen) < 0) {
			return SYSERR;
		}
		sp += lenlen;
		/* object identifier type, length, objid */
		if (*sp++ != ASN1_OBJID)
			return SYSERR;
		if ((objidlen = a1readlen(sp, (unsigned *)&lenlen)) < 0)
			return SYSERR;
		sp += lenlen;
		if (a1readoid(sp, objidlen, &bl->sb_oid) == SYSERR) {
			return SYSERR;
		}
		sp += objidlen;
		/* object's value */
		type = *sp++;
		if ((vallen = a1readlen(sp, (unsigned *)&lenlen)) < 0) {
			return SYSERR;
		}
		sp += lenlen;
		if (a1readval(&bl->sb_val, type, vallen, sp) == SYSERR) {
			return SYSERR;
		}
		sp += vallen;
		bl->sb_a1slen = 0;
	}
	return OK;
}
#endif	/* SNMP */
