/* snmpvars.h */

/* System & Interface MIB */

extern char	SysDescr[], SysContact[], SysName[], SysLocation[];
extern unsigned
	SysUpTime, SysServices, IfNumber;

/* IP MIB */
extern unsigned
	IpForwarding, IpDefaultTTL, IpInReceives, IpInHdrErrors,
	IpInAddrErrors, IpForwDatagrams, IpInUnknownProtos, IpInDiscards,
	IpInDelivers, IpOutRequests, IpOutDiscards, IpOutNoRoutes,
	IpReasmTimeout, IpReasmReqds, IpReasmOKs, IpReasmFails, IpFragOKs,
	IpFragFails, IpFragCreates, IpRoutingDiscards;

/* ICMP MIB */
extern unsigned
	IcmpInMsgs, IcmpInErrors, IcmpInDestUnreachs, IcmpInTimeExcds,
	IcmpInParmProbs, IcmpInSrcQuenchs, IcmpInRedirects, IcmpInEchos,
	IcmpInEchoReps, IcmpInTimestamps, IcmpInTimestampReps,
	IcmpInAddrMasks, IcmpInAddrMaskReps, IcmpOutMsgs, IcmpOutErrors,
	IcmpOutDestUnreachs, IcmpOutTimeExcds, IcmpOutParmProbs,
	IcmpOutSrcQuenchs, IcmpOutRedirects, IcmpOutEchos,
	IcmpOutEchoReps, IcmpOutTimestamps, IcmpOutTimestampReps,
	IcmpOutAddrMasks, IcmpOutAddrMaskReps;

/* UDP MIB */
extern unsigned
	UdpInDatagrams, UdpNoPorts, UdpInErrors, UdpOutDatagrams;

/* TCP MIB */
extern unsigned
	TcpRtoAlgorithm, TcpRtoMin, TcpRtoMax, TcpMaxConn, TcpActiveOpens,
	TcpPassiveOpens, TcpAttemptFails, TcpEstabResets, TcpCurrEstab,
	TcpInSegs, TcpOutSegs, TcpRetransSegs, TcpInErrs, TcpOutRsts;

/* SNMP MIB */
extern unsigned
        snmpInPkts, snmpOutPkts, snmpInBadVersions,
        snmpInBadCommunityNames, snmpInBadCommunityUses,
        snmpInASNParseErrs, snmpInTooBigs, snmpInNoSuchNames,
        snmpInBadValues, snmpInReadOnlys, snmpInGenErrs,
        snmpInTotalReqVars, snmpInTotalSetVars, snmpInGetRequests,
        snmpInGetNexts, snmpInSetRequests, snmpInGetResponses,
        snmpInTraps, snmpOutTooBigs, snmpOutNoSuchNames,
        snmpOutBadValues, snmpOutGenErrs, snmpOutGetRequests,
        snmpOutGetNexts, snmpOutSetRequests, snmpOutGetResponses,
        snmpOutTraps, snmpEnableAuthenTraps;
