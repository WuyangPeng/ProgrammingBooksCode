/* sif_getn.c - sif_getn */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>

/*------------------------------------------------------------------------
 * sif_getn - perform a getnext on a variable in the Interfaces Table.
 *------------------------------------------------------------------------
 */
int
sif_getn(struct snbentry *bindl, struct mib_info *mip, int numifaces)
{
	int	oidi, field, iface;


	if (sif_match(bindl, &iface, &field, numifaces) == SYSERR) {
		return SERR_NO_SUCH;
	}
	if (++iface > numifaces) {
		iface = 1;
		if (++field > SNUMF_IFTAB) {
			return (*mip->mi_next->mi_func)
				(bindl, mip->mi_next, SOP_GETF);
		}
	}
	oidi = SIF_OIDLEN;	/* 2.2.1 */

	bindl->sb_oid.id[oidi++] = (u_short) field;
	bindl->sb_oid.id[oidi++] = (u_short) iface;
	bindl->sb_oid.len = oidi;

	return sif_get(bindl, numifaces);
}
#endif	/* SNMP */
