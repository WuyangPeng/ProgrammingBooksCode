/* sninit.c - sninit */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <ctype.h>
#include <snmp.h>
#include <mib.h>
#include <snmpvars.h>

extern char vers[];

struct oid SysObjectID = { {0}, 1};
#endif	/* SNMP */

/* System & Interface MIB */
char 	 SysDescr[256], SysContact[256], SysName[256], SysLocation[256];
unsigned SysUpTime, SysServices, IfNumber;

/* IP MIB */
unsigned IpForwarding, IpDefaultTTL, IpInReceives, IpInHdrErrors,
	IpInAddrErrors, IpForwDatagrams, IpInUnknownProtos, IpInDiscards,
	IpInDelivers, IpOutRequests, IpOutDiscards, IpOutNoRoutes,
	IpReasmTimeout, IpReasmReqds, IpReasmOKs, IpReasmFails, IpFragOKs,
	IpFragFails, IpFragCreates, IpRoutingDiscards;

/* ICMP MIB */
unsigned IcmpInMsgs, IcmpInErrors, IcmpInDestUnreachs, IcmpInTimeExcds,
	IcmpInParmProbs, IcmpInSrcQuenchs, IcmpInRedirects, IcmpInEchos,
	IcmpInEchoReps, IcmpInTimestamps, IcmpInTimestampReps,
	IcmpInAddrMasks, IcmpInAddrMaskReps, IcmpOutMsgs, IcmpOutErrors,
	IcmpOutDestUnreachs, IcmpOutTimeExcds, IcmpOutParmProbs,
	IcmpOutSrcQuenchs, IcmpOutRedirects, IcmpOutEchos,
	IcmpOutEchoReps, IcmpOutTimestamps, IcmpOutTimestampReps,
	IcmpOutAddrMasks, IcmpOutAddrMaskReps;

/* UDP MIB */
unsigned UdpInDatagrams, UdpNoPorts, UdpInErrors, UdpOutDatagrams;

/* TCP MIB */
unsigned TcpRtoAlgorithm, TcpRtoMin, TcpRtoMax, TcpMaxConn,
	TcpActiveOpens, TcpPassiveOpens, TcpAttemptFails, TcpEstabResets,
	TcpCurrEstab, TcpInSegs, TcpOutSegs, TcpRetransSegs,
        TcpInErrs, TcpOutRsts;

/* SNMP MIB */
unsigned snmpInPkts, snmpOutPkts, snmpInBadVersions,
	snmpInBadCommunityNames, snmpInBadCommunityUses,
	snmpInASNParseErrs, snmpInTooBigs, snmpInNoSuchNames,
	snmpInBadValues, snmpInReadOnlys, snmpInGenErrs,
	snmpInTotalReqVars, snmpInTotalSetVars, snmpInGetRequests,
	snmpInGetNexts, snmpInSetRequests, snmpInGetResponses,
	snmpInTraps, snmpOutTooBigs, snmpOutNoSuchNames,
	snmpOutBadValues, snmpOutGenErrs, snmpOutGetRequests,
	snmpOutGetNexts, snmpOutSetRequests, snmpOutGetResponses,
	snmpOutTraps, snmpEnableAuthenTraps;


#ifdef	SNMP
int snmpinitialized = FALSE;

/*------------------------------------------------------------------------
 * sninit - initialize the data structures for the SNMP server and client
 *------------------------------------------------------------------------
 */
void
sninit(void)
{
	if (snmpinitialized)
		return;	/* if SNMP data structures already initialized */
	snmpinitialized = TRUE;
	hashinit();

	/* initialize most SNMP variables */
	strcpy(SysDescr, vers);		strcpy(SysContact,  CONTACT);
	strcpy(SysLocation, LOCATION);	getname(SysName);

	IfNumber = Net.nif - 1;
	
	/* non-zero int/counter initializations */
	IpDefaultTTL = IP_TTL;
	IpReasmTimeout = IP_FTTL;
	TcpRtoAlgorithm = 4;
	TcpRtoMin = TCP_MINRXT*10;
	TcpRtoMax = TCP_MAXRXT*10;
	TcpMaxConn = Ntcp;
}
#endif	/* SNMP */
