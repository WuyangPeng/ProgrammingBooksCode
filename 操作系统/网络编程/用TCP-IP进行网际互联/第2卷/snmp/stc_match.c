/* stc_match.c - stc_match */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>
#include <stdarg.h>

/*---------------------------------------------------------------------
 * stc_match - check if a variable exists in the TCP connections table
 *---------------------------------------------------------------------
 */
int
stc_match(struct snbentry *bindl,
	  ... /* int *field, int *tcbn */ )
{
	int 	oidi = STC_OIDLEN;
	IPaddr 	lip, rip;
	int 	lport, rport;
	va_list ap;
	int *field, *tcbn;

	va_start(ap,bindl);
	field = va_arg(ap,int *);
	tcbn = va_arg(ap,int *);
	va_end(ap);


	if ((*field = bindl->sb_oid.id[oidi++]) > SNUMF_TCTAB)
	 	return SYSERR;
	so2ipcpy((u_char *)&lip, &bindl->sb_oid.id[oidi]);
	oidi += IP_ALEN;
	lport = bindl->sb_oid.id[oidi++];
	so2ipcpy((u_char *)&rip, &bindl->sb_oid.id[oidi]);
	oidi += IP_ALEN;
	rport = bindl->sb_oid.id[oidi++];


	for (*tcbn = 0; *tcbn < Ntcp; ++(*tcbn)) {
		if (tcbtab[*tcbn].tcb_state == TCPS_FREE)
			continue;
		if (lport == tcbtab[*tcbn].tcb_lport &&
		    rport == tcbtab[*tcbn].tcb_rport &&
		    rip == tcbtab[*tcbn].tcb_rip &&
		    lip == tcbtab[*tcbn].tcb_lip)
			break;
	}
	if (*tcbn >= Ntcp || oidi != bindl->sb_oid.len)
	 	return SYSERR;
	return OK;
}
#endif	/* SNMP */
