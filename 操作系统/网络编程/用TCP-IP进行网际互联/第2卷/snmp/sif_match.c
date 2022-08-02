/* sif_match.c - sif_match */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <stdarg.h>

/*------------------------------------------------------------------------
 * sif_match - check if a variable exists in the Interfaces Table.
 *------------------------------------------------------------------------
 */
int
sif_match(struct snbentry *bindl,
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

	oidi = SIF_OIDLEN;
	if ((*field = bindl->sb_oid.id[oidi++]) > SNUMF_IFTAB)
		return SYSERR;
	if ((*iface = bindl->sb_oid.id[oidi++]) > numifaces)
		return SYSERR;
	if (oidi != bindl->sb_oid.len)
		return SYSERR;	/* oidi is not at end of objid */
	return OK;
}
#endif	/* SNMP */
