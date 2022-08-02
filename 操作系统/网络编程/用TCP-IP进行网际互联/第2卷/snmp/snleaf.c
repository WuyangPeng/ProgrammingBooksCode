/* snleaf.c - snleaf */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <mem.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>

/*------------------------------------------------------------------------
 * snleaf - perform the requested operation on the leaf SNMP variable
 *------------------------------------------------------------------------
 */
int
snleaf(struct snbentry *bindl, struct mib_info *mip, int op)
{
	int 		len;
	char		*strp;
	struct oid	*oip;
	

	if (op == SOP_GETN) {
		if (mip->mi_next)
			return((*mip->mi_next->mi_func)
				(bindl, mip->mi_next, SOP_GETF));
		return SERR_NO_SUCH;
	}
	if (op == SOP_SET) {
		if (! mip->mi_writable)
			return SERR_NO_SUCH;
		switch(mip->mi_vartype) {
		case ASN1_INT:
			if (SVTYPE(bindl) != ASN1_INT)
				return SERR_BAD_VALUE;
			if (mip->mi_param == 0)
				return SERR_NO_SUCH;
			*((int *) mip->mi_param) = SVINT(bindl);
			break;
		case ASN1_OCTSTR:
			if (SVTYPE(bindl) != ASN1_OCTSTR)
				return SERR_BAD_VALUE;
			strp = (char *) mip->mi_param;
			memcpy(strp, SVSTR(bindl), SVSTRLEN(bindl));
			*(strp + SVSTRLEN(bindl)) = '\0';
			break;
		case ASN1_OBJID:
			if (SVTYPE(bindl) != ASN1_OBJID)
				return SERR_BAD_VALUE;
			oip = (struct oid *) mip->mi_param;
			oip->len = SVSTRLEN(bindl);
			memcpy(oip->id, SVSTR(bindl), oip->len * 2);
			break;
		}
		return SNMP_OK;
	}
	if (op == SOP_GETF) {
		/* put the correct objid into the binding list. */
		bindl->sb_oid.len = mip->mi_objid.len;
		memcpy(bindl->sb_oid.id, mip->mi_objid.id,
			mip->mi_objid.len * 2);
	}
	SVTYPE(bindl) = mip->mi_vartype;

	switch(mip->mi_vartype) {
	case ASN1_INT:
	case ASN1_TIMETICKS:
	case ASN1_GAUGE:
	case ASN1_COUNTER:
/* kprintf("snleaf: grabbed %d\n", *((int *) mip->mi_param)); */
		SVINT(bindl) = *((int *) mip->mi_param);
		break;
	case ASN1_OCTSTR:
		strp = mip->mi_param;
		if (strp == NULL) {
			SVSTRLEN(bindl) = 0;
			SVSTR(bindl) = NULL;
			break;
		}
		len = SVSTRLEN(bindl) = strlen(strp);
		SVSTR(bindl) = (char *) getmem(len);
		memcpy(SVSTR(bindl), strp, len);
		break;
	case ASN1_OBJID:
		oip = (struct oid *) mip->mi_param;
		SVOIDLEN(bindl) = oip->len;
		memcpy(SVOID(bindl), oip->id, oip->len * 2);
		break;
	}
	return SNMP_OK;
}
#endif	/* SNMP */
