/* sif_set.c - sif_set */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>

/*------------------------------------------------------------------------
 * sif_set - perform a set on a variable in the Interfaces Table
 *------------------------------------------------------------------------
 */
int
sif_set(struct snbentry *bindl, struct mib_info *mip, int numifaces)
{
	int iface, field;

	if (sif_match(bindl, &iface, &field, numifaces) == SYSERR)
		return SERR_NO_SUCH;
	/* the only settable object here is ifAdminStatus (ifEntry 7) */
	if (field != 7)
		return SERR_NO_SUCH;
	if (SVTYPE(bindl) != ASN1_INT)
		return SERR_BAD_VALUE;
	if (SVINT(bindl) < 0 || SVINT(bindl) > 1)
		return SERR_BAD_VALUE;
	/* value is OK, so install it */
	nif[iface].ni_admstate = SVINT(bindl);
	return SNMP_OK;
}
#endif	/* SNMP */
