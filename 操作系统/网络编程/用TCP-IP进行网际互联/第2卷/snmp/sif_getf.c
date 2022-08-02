/* sif_getf.c - sif_getf */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>

/*------------------------------------------------------------------------
 * sif_getf - perform a getfirst on a variable in the Interfaces Table
 *------------------------------------------------------------------------
 */
int
sif_getf(struct snbentry *bindl, struct mib_info *mip, int numifaces)
{
	int	oidi;

	memcpy(bindl->sb_oid.id, mip->mi_objid.id, mip->mi_objid.len*2);
	oidi = mip->mi_objid.len;

	bindl->sb_oid.id[oidi++] = (u_short) 1;		/* field 	*/
	bindl->sb_oid.id[oidi++] = (u_short) 1;		/* interface	*/
	bindl->sb_oid.len = oidi;
	
	return sif_get(bindl, numifaces);
}
#endif	/* SNMP */
