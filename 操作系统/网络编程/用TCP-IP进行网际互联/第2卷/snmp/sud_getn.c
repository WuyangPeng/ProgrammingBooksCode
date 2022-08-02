/* sud_getn.c - sud_getn */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>

/*------------------------------------------------------------------------
 * sud_getn - do a getnext on a variable in the UDP listener table
 *------------------------------------------------------------------------
 */
int
sud_getn(struct snbentry *bindl, struct mib_info *mip, int numifaces)
{
	int	oidi, field, udpn;
	IPaddr ip_allzero = 0;


	if (sud_match(bindl,&field,&udpn) == SYSERR) {
		return SERR_NO_SUCH;
	}
	/* search for next connection */
	if ((udpn = sud_findnext(udpn)) < 0) {
		udpn = sud_findnext(-1);
		if (++field > SNUMF_UDTAB) {
		        /* end of table, go to next variable */
		        if (mip->mi_next == (void *)NULLPTR) {
			    /* end of mib */
			    return SERR_NO_SUCH;
			}
			return((*mip->mi_next->mi_func)
			       (bindl, mip->mi_next, SOP_GETF));
		}
	}
	oidi = SUD_OIDLEN; 	/* 7.5.1 */

	bindl->sb_oid.id[oidi++] = (u_short) field;

	sip2ocpy(&bindl->sb_oid.id[oidi], ip_allzero);
	oidi += IP_ALEN;
	bindl->sb_oid.id[oidi++] = (u_short) upqs[udpn].up_port;
	bindl->sb_oid.len = oidi;

	return sud_get(bindl, numifaces);
}
#endif	/* SNMP */
