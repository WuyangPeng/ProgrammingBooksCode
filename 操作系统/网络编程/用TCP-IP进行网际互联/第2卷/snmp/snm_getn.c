/* snm_getn.c - snm_getn */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>

/*------------------------------------------------------------------------
 * snm_getn - do a getnext on a variable in the IP NetToMedia Table
 *------------------------------------------------------------------------
 */
int
snm_getn(struct snbentry *bindl, struct mib_info *mip, int numifaces)
{
	int 	entry, iface, field, oidi;
	


	if (snm_match(bindl, &iface, &entry, &field, numifaces) == SYSERR) {
		return SERR_NO_SUCH;
	}
	while (field <= SNUMF_NMTAB) {
		if ((entry = snm_findnext(entry, iface)) >= 0)
			break;
		if (++iface > numifaces) {
			iface = 1;
			++field;
		}
	}
	if (entry < 0) {
		return (*mip->mi_next->mi_func)
				(bindl, mip->mi_next, SOP_GETF);
	}
	oidi = SNM_OIDLEN;	/* 4.22.1 */

	bindl->sb_oid.id[oidi++] = (u_short) field;
	bindl->sb_oid.id[oidi++] = (u_short) iface;
	bindl->sb_oid.id[oidi++] = (u_short) 1;
	sip2ocpy(&bindl->sb_oid.id[oidi],
		 *((IPaddr *)arptable[entry].ae_pra));
	bindl->sb_oid.len = oidi + IP_ALEN;
	
	return snm_get(bindl, numifaces);
}
#endif	/* SNMP */
