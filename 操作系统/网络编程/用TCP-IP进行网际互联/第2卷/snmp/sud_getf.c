/* sud_getf.c - sud_getf */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>

/*------------------------------------------------------------------------
 * sud_getf - do a getfirst on a variable in the UDP listener table
 *------------------------------------------------------------------------
 */
int
sud_getf(struct snbentry *bindl, struct mib_info *mip, int numifaces)
{
	int	oidi, udpn;
	IPaddr ip_allzero = 0;


	/* find first connection, if any */
	udpn = sud_findnext(-1);
	if (udpn < 0) {
		if (mip->mi_next)
			return((*mip->mi_next->mi_func)
				(bindl, mip->mi_next, SOP_GETF));
		return SERR_NO_SUCH;
	}
	memcpy(bindl->sb_oid.id, mip->mi_objid.id, mip->mi_objid.len*2);
	oidi = mip->mi_objid.len;

	bindl->sb_oid.id[oidi++] = (u_short) 1;  	/* field */

	sip2ocpy(&bindl->sb_oid.id[oidi], ip_allzero);
	oidi += IP_ALEN;
	bindl->sb_oid.id[oidi++] = (u_short) upqs[udpn].up_port;
	bindl->sb_oid.len = oidi;

	return sud_get(bindl, numifaces);
}
#endif	/* SNMP */
