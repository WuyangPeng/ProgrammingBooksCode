/* sae_match.c - sae_match */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>
#include <snhash.h>
#include <stdarg.h>

/*------------------------------------------------------------------------
 * sae_match - check if a variable exists in the IP Address Entry Table
 *------------------------------------------------------------------------
 */
int
sae_match(struct snbentry *bindl,
	  ... /* int *iface, int *field, int numifaces */ )
{
	int 	oidi;
	va_list ap;
	int *iface, *field, numifaces;

	va_start(ap,bindl);
	iface = va_arg(ap,int *);
	field = va_arg(ap,int *);
	numifaces = va_arg(ap,int);
	va_end(ap);

	oidi = SAE_OIDLEN;	/* skip over fixed part of objid */

	if ((*field = bindl->sb_oid.id[oidi++]) > SNUMF_AETAB)
		return SYSERR;
	for (*iface = 1; *iface <= numifaces; (*iface)++)
		if (soipequ(&bindl->sb_oid.id[oidi],
				nif[*iface].ni_ip, IP_ALEN))
			break;
	if (*iface > numifaces)
		return SYSERR;
	oidi += IP_ALEN;
	if (oidi != bindl->sb_oid.len)	/* verify oidi at end of objid	*/
		return SYSERR;
	return OK;
}
#endif	/* SNMP */
