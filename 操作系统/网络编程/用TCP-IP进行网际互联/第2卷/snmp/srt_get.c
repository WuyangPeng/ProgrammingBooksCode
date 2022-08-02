/* srt_get.c - srt_get */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <asn1.h>

/*------------------------------------------------------------------------
 * srt_get - perform a get on a variable in the Routing Table
 *------------------------------------------------------------------------
 */
int
srt_get(struct snbentry *bindl, int numifaces)
{
	struct	route *rtp;
	int	rtl, field;

	if (srt_match(bindl, &rtp, &rtl, &field) == SYSERR)
		return SERR_NO_SUCH;
	switch(field) {
	case 1:		/* ipRouteDest */
		SVTYPE(bindl) = ASN1_IPADDR;
		SVIPADDR(bindl)=rtp->rt_net;
		return SNMP_OK;
	case 2:		/* ipRouteIfIndex */
		SVTYPE(bindl) = ASN1_INT;
		SVINT(bindl) = rtp->rt_ifnum;
		return SNMP_OK;
	case 3:		/* ipRouteMetric1 */
		SVTYPE(bindl) = ASN1_INT;
		SVINT(bindl) = rtp->rt_metric;
		return SNMP_OK;
	case 4:		/* ipRouteMetric2 */
	case 5:		/* ipRouteMetric3 */
	case 6:		/* ipRouteMetric4 */
		SVTYPE(bindl) = ASN1_INT;
		SVINT(bindl) = -1;
		return SNMP_OK;
	case 7:		/* ipRouteNextHop */
		SVTYPE(bindl) = ASN1_IPADDR;
		SVIPADDR(bindl)=rtp->rt_gw;
		return SNMP_OK;
	case 8:		/* ipRouteType */
		SVTYPE(bindl) = ASN1_INT;
		if (rtp->rt_metric)
		    SVINT(bindl) = 4;	/* remote */
		else
		    SVINT(bindl) = 3;	/* direct */
		return SNMP_OK;
	case 9:		/* ipRouteProto */
		SVTYPE(bindl) = ASN1_INT;
		SVINT(bindl) = 1;		/* other */
		return SNMP_OK;
	case 10:		/* ipRouteAge */
		SVTYPE(bindl) = ASN1_INT;
		SVINT(bindl) = rtp->rt_ttl;
		return SNMP_OK;
	case 11:		/* ipRouteMask */
		SVTYPE(bindl) = ASN1_IPADDR;
		SVIPADDR(bindl)=rtp->rt_mask;
		return SNMP_OK;
	case 12:		/* ipRouteMetric5 */
		SVTYPE(bindl) = ASN1_INT;
		SVINT(bindl) = -1;
		return SNMP_OK;
	case 13:		/* ipRouteInfo */
		{
			struct oid RouteInfo = { {0,0}, 2};
			SVTYPE(bindl) = ASN1_OBJID;
			/* set to 0.0, per rfc 1213 */
			SVOIDLEN(bindl) = RouteInfo.len;
			memcpy(SVOID(bindl), RouteInfo.id, RouteInfo.len * 2);
		}
		return SNMP_OK;
	default:
		break;
	}
	return SERR_NO_SUCH;
}
#endif	/* SNMP */
