/* stc_get.c - stc_get */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>

/*------------------------------------------------------------------------
 * stc_get - perform a get on a variable in the TCP connections table
 *------------------------------------------------------------------------
 */
int
stc_get(struct snbentry *bindl, int numifaces)
{
	int 	field, tcbn;



	if (stc_match(bindl, &field, &tcbn) == SYSERR)
		return SERR_NO_SUCH;

	switch (field) {
	case 1:		/* tcpConnState */
		SVTYPE(bindl) = ASN1_INT;
		SVINT(bindl) = tcbtab[tcbn].tcb_state; 
		break;
	case 2:		/* tcpConnLocalAddress */
		SVTYPE(bindl) = ASN1_IPADDR;
		SVIPADDR(bindl)=tcbtab[tcbn].tcb_lip;
		break;
	case 3:		/* tcpConnLocalPort */
		SVTYPE(bindl) = ASN1_INT;
		SVINT(bindl) = tcbtab[tcbn].tcb_lport; 
		break;
	case 4:		/* tcpConnRemAddress */
		SVTYPE(bindl) = ASN1_IPADDR;
		SVIPADDR(bindl)=tcbtab[tcbn].tcb_rip;
		break;
	case 5:		/* tcpConnRemPort */
		SVTYPE(bindl) = ASN1_INT;
		SVINT(bindl) = tcbtab[tcbn].tcb_rport;
		break;
	default:
		return SERR_NO_SUCH;
	}
	return SNMP_OK;
}
#endif	/* SNMP */
