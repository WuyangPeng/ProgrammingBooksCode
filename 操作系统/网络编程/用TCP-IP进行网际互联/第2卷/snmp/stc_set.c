/* stc_set.c - stc_set */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>
#include <io.h>

/*------------------------------------------------------------------------
 * stc_set - set TCP table entities
 *------------------------------------------------------------------------
 */
int
stc_set(struct snbentry *bindl, struct mib_info *mip, int numifaces)
{
	int tcbn, field;

	if (stc_match(bindl, &field, &tcbn) == SYSERR)
		return SERR_NO_SUCH;

	switch (field) {
	case 1:		/* tcpConnState */
		/* the only thing that you can legally change
		   this to is the integer deleteTCB(12) */
		if (SVTYPE(bindl) != ASN1_INT)
			return SERR_BAD_VALUE;
		if (SVINT(bindl) != 12)
			return SERR_BAD_VALUE;
		close(tcbtab[tcbn].tcb_dvnum);
		return SNMP_OK;
	default:
		return SERR_NO_SUCH;
	}
	return SNMP_OK;

}
#endif	/* SNMP */
