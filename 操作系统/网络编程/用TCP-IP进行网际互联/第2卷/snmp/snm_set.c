/* snm_set.c - snm_set */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>

/*------------------------------------------------------------------------
 * snm_set - do a set on a variable in the IP NetToMedia Table
 *------------------------------------------------------------------------
 */
int
snm_set(struct snbentry *bindl, struct mib_info *mip, int numifaces)
{
	int 	iface, entry, field;
	
	if (snm_match(bindl, &iface, &entry, &field, numifaces) == SYSERR)
		return SERR_NO_SUCH;
	switch (field) {
	case 1:		/* ipNetToMediaIfIndex */
		if (SVTYPE(bindl) != ASN1_INT)
			return SERR_BAD_VALUE;
		if (SVINT(bindl) <= 0)
			return SERR_BAD_VALUE;
		if (SVINT(bindl) > numifaces)
			return SERR_BAD_VALUE;
		arptable[entry].ae_pni = &nif[SVINT(bindl)];
		return SNMP_OK;
	case 2:		/* ipNetToMediaPhysAddress */
		if (SVTYPE(bindl) != ASN1_OCTSTR)
			return SERR_BAD_VALUE;
		if (SVSTRLEN(bindl) != EP_ALEN)
			return SERR_BAD_VALUE;
		memcpy(arptable[entry].ae_hwa, SVSTR(bindl), EP_ALEN);
		return SNMP_OK;
	case 3:		/* ipNetToMediaNetAddress */
		if (SVTYPE(bindl) != ASN1_IPADDR)
			return SERR_BAD_VALUE;
		memcpy(arptable[entry].ae_pra, &SVIPADDR(bindl), IP_ALEN);
		return SNMP_OK;
	case 4:		/*  ipNetToMediaType */
		if (SVTYPE(bindl) != ASN1_INT)
			return SERR_BAD_VALUE;
		/* only invalid(2) may be set */
		if (SVINT(bindl) != 2)
			return SERR_BAD_VALUE;
		/* invalidate this entry */
		arptable[entry].ae_state = AS_FREE;
		return SNMP_OK;
	default:
		break;
	}
	return SERR_NO_SUCH;
}
#endif	/* SNMP */
