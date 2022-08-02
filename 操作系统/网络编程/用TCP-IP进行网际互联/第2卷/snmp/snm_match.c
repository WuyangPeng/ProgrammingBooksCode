/* snm_match.c - snm_match */
    
#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <stdarg.h>

/*------------------------------------------------------------------------
 * snm_match - check if a variable exists in the IP NetToMedia Table
 *------------------------------------------------------------------------
 */
int
snm_match(struct snbentry *bindl,
	  ... /* int *iface, int *entry, int *field, int numifaces */ )
{
	int 	oidi;
	struct	arpentry *pae;
	va_list ap;
	int *iface, *entry, *field, numifaces;

	va_start(ap,bindl);
	iface = va_arg(ap,int *);
	entry = va_arg(ap,int *);
	field = va_arg(ap,int *);
	numifaces = va_arg(ap,int);
	va_end(ap);

	oidi = SNM_OIDLEN;
	if ((*field = bindl->sb_oid.id[oidi++]) > SNUMF_NMTAB)
		return SYSERR;
	if ((*iface = bindl->sb_oid.id[oidi++]) > numifaces)
		return SYSERR;
	oidi++;		/* skip over the 1 */
	/*
	 * oidi now points to IPaddr.  Read it and match it against
	 * the correct arp cache entry to get entry number
	 */
	for (*entry = 0; *entry < ARP_TSIZE; (*entry)++) {
		pae = &arptable[*entry];
		if (pae->ae_state != AS_FREE &&
		    pae->ae_pni == &nif[*iface] &&
		    soipequ(&bindl->sb_oid.id[oidi],
			    *((IPaddr *)pae->ae_pra),IP_ALEN))
			break;
	}
	if (*entry >= ARP_TSIZE)
		return SYSERR;
	if (oidi + IP_ALEN != bindl->sb_oid.len)
		return SYSERR;	/*  oidi is not at end of objid */
	return OK;
}
#endif	/* SNMP */
