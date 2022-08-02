/* snm_getf.c - snm_getf */
    
#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>
#include <snhash.h>

/*------------------------------------------------------------------------
 * snm_getf - do a getfirst on a variable in the IP NetToMedia Table
 *------------------------------------------------------------------------
 */
int
snm_getf(struct snbentry *bindl, struct mib_info *mip, int numifaces)
{
	int 	iface, entry, oidi;
	
	for (iface=1; iface <= numifaces; ++iface)
		if ((entry = snm_findnext(-1, iface)) >= 0)
			break;
	if (iface > numifaces) {  /* no active interface found */
		if (mip->mi_next)
			return (*mip->mi_next->mi_func)
	 			(bindl, mip->mi_next, SOP_GETF);
		return SERR_NO_SUCH;		/* no next node */
	}
	memcpy(bindl->sb_oid.id, mip->mi_objid.id, mip->mi_objid.len*2);
	oidi = mip->mi_objid.len;

	bindl->sb_oid.id[oidi++] = (u_short) 1;		/* field	*/
	bindl->sb_oid.id[oidi++] = (u_short) iface;
	bindl->sb_oid.id[oidi++] = (u_short) 1;
	sip2ocpy(&bindl->sb_oid.id[oidi],
		 *((IPaddr *)arptable[entry].ae_pra));
	bindl->sb_oid.len = oidi + IP_ALEN;

	return snm_get(bindl, numifaces);
}
#endif	/* SNMP */
