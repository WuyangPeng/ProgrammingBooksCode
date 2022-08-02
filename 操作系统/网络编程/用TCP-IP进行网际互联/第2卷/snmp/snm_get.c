/* snm_get.c - snm_get */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <mem.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>

/*------------------------------------------------------------------------
 * snm_get - do a get on a variable in the IP NetToMedia Table
 *------------------------------------------------------------------------
 */
int
snm_get(struct snbentry *bindl, int numifaces)
{
	int 	iface, entry, field;



	if (snm_match(bindl, &iface, &entry, &field, numifaces) == SYSERR)
		return SERR_NO_SUCH;
	switch(field) {
	case 1:		/* ipNetToMediaIfIndex */
		SVTYPE(bindl) = ASN1_INT;
		SVINT(bindl) = iface;
		return SNMP_OK;
	case 2:		/* ipNetToMediaPhysAddress */
		SVTYPE(bindl) = ASN1_OCTSTR;
		SVSTR(bindl) = (char *) getmem(EP_ALEN);
		memcpy(SVSTR(bindl), arptable[entry].ae_hwa,
			EP_ALEN);
		SVSTRLEN(bindl) = EP_ALEN;
		return SNMP_OK;
	case 3:		/* ipNetToMediaNetAddress */
		SVTYPE(bindl) = ASN1_IPADDR;
		memcpy(&SVIPADDR(bindl), arptable[entry].ae_pra,
			IP_ALEN);
		return SNMP_OK;
	case 4:		/* ipNetToMediaType */
		SVTYPE(bindl) = ASN1_INT;
		if (arptable[entry].ae_state == AS_FREE)
		    SVINT(bindl) = 2;  /* invalid(2) */
		else
		    SVINT(bindl) = 3;  /* dynamic(3) */
		return SNMP_OK;
	default:
		break;
	}
	return SERR_NO_SUCH;
}
#endif	/* SNMP */
