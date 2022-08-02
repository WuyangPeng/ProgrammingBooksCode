/* sud_set.c - sud_set */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>

/*------------------------------------------------------------------------
 * sud_set - return error: the UDP Listener Table is read-only
 *------------------------------------------------------------------------
 */
int
sud_set(struct snbentry *bindl, struct mib_info *mip, int numifaces)
{
	return SERR_NO_SUCH;
}
#endif	/* SNMP */
