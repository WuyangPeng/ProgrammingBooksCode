/* stc_getf.c - stc_getf */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>

/*------------------------------------------------------------------------
 * stc_getf - do a getfirst on a variable in the TCP connection table
 *------------------------------------------------------------------------
 */
int
stc_getf(struct snbentry *bindl, struct mib_info *mip, int numifaces)
{
	int	oidi, tcbn;


	/* find first connection, if any */
	tcbn = stc_findnext(-1);
	if (tcbn < 0) {
		if (mip->mi_next)
			return((*mip->mi_next->mi_func)
				(bindl, mip->mi_next, SOP_GETF));
		return SERR_NO_SUCH;
	}
	memcpy(bindl->sb_oid.id, mip->mi_objid.id, mip->mi_objid.len*2);	
	oidi = mip->mi_objid.len;

	bindl->sb_oid.id[oidi++] = (u_short) 1;	/* field */
	sip2ocpy(&bindl->sb_oid.id[oidi], tcbtab[tcbn].tcb_lip);
	oidi += IP_ALEN;
	bindl->sb_oid.id[oidi++] = (u_short) tcbtab[tcbn].tcb_lport;
	sip2ocpy(&bindl->sb_oid.id[oidi], tcbtab[tcbn].tcb_rip);
	oidi += IP_ALEN;
	bindl->sb_oid.id[oidi++] = (u_short) tcbtab[tcbn].tcb_rport;
	bindl->sb_oid.len = oidi;

	return stc_get(bindl, numifaces);
}
#endif	/* SNMP */
