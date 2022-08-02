/* sud_get.c - sud_get */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>

/*------------------------------------------------------------------------
 * sud_get - perform a get on a variable in the UDP listener table
 *------------------------------------------------------------------------
 */
int
sud_get(struct snbentry *bindl, int numifaces)
{
	int 	field, udpn;


	if (sud_match(bindl, &field, &udpn) == SYSERR)
		return SERR_NO_SUCH;
	switch (field) {
	case 1:		/* udpLocalAddress */
		{
	  	IPaddr ip_allzero = 0;
		SVTYPE(bindl) = ASN1_IPADDR;
		SVIPADDR(bindl)=ip_allzero;  /* accept any, rfc 1213 */
		}
		break;
	case 2:		/* udpLocalPort */
		SVTYPE(bindl) = ASN1_INT;
		SVINT(bindl) = upqs[udpn].up_port; 
		break;
	default:
		return SERR_NO_SUCH;
	}
	return SNMP_OK;
}
#endif	/* SNMP */
