/* sud_match.c - sud_match */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>
#include <stdarg.h>

/*---------------------------------------------------------------------
 * sud_match - check if a variable exists in the UDP listener table
 *---------------------------------------------------------------------
 */
int
sud_match(struct snbentry *bindl,
	  ... /* int *field, int *udpn */ )
{
	int 	oidi = SUD_OIDLEN;
	int 	lport;
	va_list ap;
	int *field, *udpn;

	va_start(ap,bindl);
	field = va_arg(ap,int *);
	udpn = va_arg(ap,int *);
	va_end(ap);

	if ((*field = bindl->sb_oid.id[oidi++]) > SNUMF_UDTAB)
	 	return SYSERR;

	oidi += IP_ALEN;  /* skip the IP address */
	lport = bindl->sb_oid.id[oidi++];

	for (*udpn = 0; *udpn < UPPS; ++(*udpn)) {
		if (!upqs[*udpn].up_valid)
			continue;
		if (lport == upqs[*udpn].up_port)
			break;
	}
	if (*udpn >= UPPS || oidi != bindl->sb_oid.len)
	 	return SYSERR;
	return OK;
}
#endif	/* SNMP */
