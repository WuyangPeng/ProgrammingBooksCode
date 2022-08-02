/* x_net.c - x_net */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <asn1.h>
#include <snmp.h>
#include <mib.h>
#include <io.h>
#include <sem.h>
#include <q.h>
#include <mark.h>
#include <ports.h>

/*#define PRINTSEMS*/

static	int	noarg(), iarg();
static int parg(int stdout, int stderr);
static char *tcpfnames(int flag);


/*------------------------------------------------------------------------
 *  x_net  -  (command netstat) print network status information
 *------------------------------------------------------------------------
 */
COMMAND x_net(stdin, stdout, stderr, nargs, args)
int	stdin, stdout, stderr, nargs;
char	*args[];
{

	if (nargs == 1)
		return noarg(stdout, stderr);
	if (nargs > 2 || *args[1] != '-') {
		write(stderr, "usage: netstat -[ip]\n", 21);
		return 1;
	}
	switch (args[1][1]) {
	case	'i':	return iarg(stdout, stderr);
	case	'p':	return parg(stdout, stderr);
	default:
		write(stderr, "usage: netstat -[ip]\n", 21);
		return 1;
	}
}

char	*tcpsnames[] = { "FREE", "CLOSED", "LISTEN", "SYNSENT", "SYNRCVD",
			"ESTABLISHED", "FINWAIT1", "FINWAIT2", "CLOSEWAIT",
			"LASTACK", "CLOSING", "TIMEWAIT" };

#define	NH1 \
"Proto   RQ     SQ   L. Port    Remote IP    R. Port    State    flags   dev\n"
#define NH2 \
"----- ------ ------ ------- --------------- ------- ----------- -----  -----\n"

static	int
noarg(stdout, stderr)
int	stdout, stderr;
{
	char	str[120];
	char	ipa[16];	/* "XXX.XXX.XXX.XXX\0" */
	int	i;

	write(stdout, NH1, strlen(NH1));
	write(stdout, NH2, strlen(NH2));
	for (i=0; i<Ntcp; ++i) {
		struct tcb	*ptcb = &tcbtab[i];

		if (ptcb->tcb_state == TCPS_FREE)
			continue;
		ip2dot(ipa, ptcb->tcb_rip);
#ifdef PRINTSEMS
		sprintf(str, " %3s  %6d %6d  %5d  %15s  %5d %11s %6s %5d %3d %3d %3d\n",
			"tcp", ptcb->tcb_rbcount, ptcb->tcb_sbcount,
			ptcb->tcb_lport, ipa, ptcb->tcb_rport,
			tcpsnames[ptcb->tcb_state],
			tcpfnames(ptcb->tcb_flags),
			ptcb->tcb_dvnum,
			ptcb->tcb_mutex,
			ptcb->tcb_ssema,
			ptcb->tcb_rsema);
#else
		sprintf(str, " %3s  %6d %6d  %5d  %15s  %5d %11s %6s %5d\n",
			"tcp", ptcb->tcb_rbcount, ptcb->tcb_sbcount,
			ptcb->tcb_lport, ipa, ptcb->tcb_rport,
			tcpsnames[ptcb->tcb_state], tcpfnames(ptcb->tcb_flags),
			ptcb->tcb_dvnum);
#endif
		write(stdout, str, strlen(str));
	}
	return(OK);
}

static	int
iarg(stdout, stderr)
int	stdout, stderr;
{
	struct	upq	*pup;
	char	str[80];
	int	i;

	sprintf(str,
		"netpool=%d, lrgpool=%d\n", Net.netpool, Net.lrgpool);
	write(stdout, str, strlen(str));
	sprintf(str, "Number of interfaces configured: %d\n", Net.nif);
	for (i=1; i<Net.nif; ++i) {
		struct	netif	*pni = &nif[i];

		if (pni->ni_state == NIS_DOWN &&
		    pni->ni_admstate == NIS_DOWN)
				continue;
		sprintf(str,
			"\nif%d\nIn:  %ld packets (%ld broadcast), %ld bytes\n", i,
			pni->ni_iucast+pni->ni_inucast, pni->ni_inucast,
			pni->ni_ioctets);
		write(stdout, str, strlen(str));
		sprintf(str,
			"Out: %ld packets (%ld broadcast), %ld bytes\n",
			pni->ni_oucast+pni->ni_onucast, pni->ni_onucast,
			pni->ni_ooctets);
		write(stdout, str, strlen(str));
		sprintf(str,
		"Errors: %ld input, %ld output\tDiscards %ld input, %ld output\n",
			pni->ni_ierrors, pni->ni_oerrors,
			pni->ni_idiscard, pni->ni_odiscard);
		write(stdout, str, strlen(str));
		sprintf(str, "%ld input packets with unknown protocols\n",
			pni->ni_iunkproto);
		write(stdout, str, strlen(str));
	}
	str[0] = '\n';
	write(stdout, str, 1);
	for (i=0; i<UPPS; i++) {
		pup = &upqs[i];
		if (!pup->up_valid)
		  continue;
		sprintf(str,
			"%2d. port=%4d, pid=%3d, xport=%2d, size=%2d\n",
			i, pup->up_port, pup->up_pid, pup->up_xport,
			pcount(pup->up_xport) );
		write(stdout, str, strlen(str));
	}

	sprintf(str, "\nfragment queues:\n");
	write(stdout, str, strlen(str));
	wait(ipfmutex);
	for (i=0; i<IP_FQSIZE; ++i) {
		char *state;
		struct ep *p;

		if (ipfqt[i].ipf_state == IPFF_FREE)
			continue;
		state = (ipfqt[i].ipf_state == IPFF_VALID) ? "VALID" : "ORPHAN";
		sprintf(str, "%d.\tstate %s src %X id %x ttl %d\toffsets: ",
			i, state,
			IP2I(ipfqt[i].ipf_src),
			ipfqt[i].ipf_id,
			ipfqt[i].ipf_ttl);
		write(stdout, str, strlen(str));
		while ((p = (struct ep *) seeq(ipfqt[i].ipf_q)) != (struct ep *) NULL) {
			struct ip *pip;

			pip = (struct ip *)p->ep_data;
			sprintf(str, " %d", pip->ip_fragoff & IP_FRAGOFF);
			write(stdout, str, strlen(str));
		}
		str[0] = '\n';
		write(stdout, str, 1);
	}
	signal(ipfmutex);
	return(OK);
}

#define	addflag(f, name) \
	if (flag & f) { \
		*p++ = name; \
		*p = '\0'; \
	}

static
char *
tcpfnames(int flag)
{
	static char string[5];
	char	*p;

	p = &string[0];
	*p = '\0';

	addflag(TCBF_RDONE, 'R');
	addflag(TCBF_SDONE, 'S');
	addflag(TCBF_DELACK, 'D');
	addflag(TCBF_BUFFER, 'B');
	return string;
}


struct {
	char		*name;
	unsigned	*value;
} tcpstuff[] =  {
	{ "MaxConn",		&TcpMaxConn },
	{ "ActiveOpens",	&TcpActiveOpens },
	{ "PassiveOpens",	&TcpPassiveOpens },
	{ "AttemptFails",	&TcpAttemptFails },
	{ "EstabResets",	&TcpEstabResets },
	{ "CurrEstab",		&TcpCurrEstab },
	{ "InSegs",		&TcpInSegs },
	{ "OutSegs",		&TcpOutSegs },
	{ "RetransSegs",	&TcpRetransSegs },
	{ 0, 0}
};

static int
parg(int stdout, int stderr)
{
	kprintf("IfNumber:  %d\n", IfNumber);
	kprintf("SysDescr:  %d\n", SysDescr);
	kprintf("SysUpTime: %d\n", SysUpTime);

        kprintf("\nICMP MIB:\n");
        kprintf("  IcmpInAddrMaskReps:   %d\n", IcmpInAddrMaskReps);
        kprintf("  IcmpInAddrMasks:      %d\n", IcmpInAddrMasks);
        kprintf("  IcmpInDestUnreachs:   %d\n", IcmpInDestUnreachs);
        kprintf("  IcmpInEchoReps:       %d\n", IcmpInEchoReps);
        kprintf("  IcmpInEchos:          %d\n", IcmpInEchos);
        kprintf("  IcmpInErrors:         %d\n", IcmpInErrors);
        kprintf("  IcmpInMsgs:           %d\n", IcmpInMsgs);
        kprintf("  IcmpInParmProbs:      %d\n", IcmpInParmProbs);
        kprintf("  IcmpInRedirects:      %d\n", IcmpInRedirects);
        kprintf("  IcmpInSrcQuenchs:     %d\n", IcmpInSrcQuenchs);
        kprintf("  IcmpInTimeExcds:      %d\n", IcmpInTimeExcds);
        kprintf("  IcmpInTimestampReps:  %d\n", IcmpInTimestampReps);
        kprintf("  IcmpInTimestamps:     %d\n", IcmpInTimestamps);
        kprintf("  IcmpOutAddrMaskReps:  %d\n", IcmpOutAddrMaskReps);
        kprintf("  IcmpOutAddrMasks:     %d\n", IcmpOutAddrMasks);
        kprintf("  IcmpOutDestUnreachs:  %d\n", IcmpOutDestUnreachs);
        kprintf("  IcmpOutEchoReps:      %d\n", IcmpOutEchoReps);
        kprintf("  IcmpOutEchos:         %d\n", IcmpOutEchos);
        kprintf("  IcmpOutErrors:        %d\n", IcmpOutErrors);
        kprintf("  IcmpOutMsgs:          %d\n", IcmpOutMsgs);
        kprintf("  IcmpOutParmProbs:     %d\n", IcmpOutParmProbs);
        kprintf("  IcmpOutRedirects:     %d\n", IcmpOutRedirects);
        kprintf("  IcmpOutSrcQuenchs:    %d\n", IcmpOutSrcQuenchs);
        kprintf("  IcmpOutTimeExcds:     %d\n", IcmpOutTimeExcds);
        kprintf("  IcmpOutTimestampReps: %d\n", IcmpOutTimestampReps);
        kprintf("  IcmpOutTimestamps:    %d\n", IcmpOutTimestamps);

        kprintf("\nIP MIB:\n");
        kprintf("  IpDefaultTTL:      %d\n", IpDefaultTTL);
        kprintf("  IpForwDatagrams:   %d\n", IpForwDatagrams);
        kprintf("  IpFragCreates:     %d\n", IpFragCreates);
        kprintf("  IpFragFails:       %d\n", IpFragFails);
        kprintf("  IpFragOKs:         %d\n", IpFragOKs);
        kprintf("  IpInAddrErrors:    %d\n", IpInAddrErrors);
        kprintf("  IpInDelivers:      %d\n", IpInDelivers);
        kprintf("  IpInDiscards:      %d\n", IpInDiscards);
        kprintf("  IpInHdrErrors:     %d\n", IpInHdrErrors);
        kprintf("  IpInReceives:      %d\n", IpInReceives);
        kprintf("  IpInUnknownProtos: %d\n", IpInUnknownProtos);
        kprintf("  IpOutDiscards:     %d\n", IpOutDiscards);
        kprintf("  IpOutNoRoutes:     %d\n", IpOutNoRoutes);
        kprintf("  IpOutRequests:     %d\n", IpOutRequests);
        kprintf("  IpReasmFails:      %d\n", IpReasmFails);
        kprintf("  IpReasmOKs:        %d\n", IpReasmOKs);
        kprintf("  IpReasmReqds:      %d\n", IpReasmReqds);
        kprintf("  IpReasmTimeout:    %d\n", IpReasmTimeout);
        
        kprintf("\nTCP MIB:\n");
        kprintf("  TcpActiveOpens:  %d\n", TcpActiveOpens);
        kprintf("  TcpAttemptFails: %d\n", TcpAttemptFails);
        kprintf("  TcpCurrEstab:    %d\n", TcpCurrEstab);
        kprintf("  TcpEstabResets:  %d\n", TcpEstabResets);
        kprintf("  TcpInSegs:       %d\n", TcpInSegs);
        kprintf("  TcpInErrs:       %d\n", TcpInErrs);
        kprintf("  TcpMaxConn:      %d\n", TcpMaxConn);
        kprintf("  TcpOutSegs:      %d\n", TcpOutSegs);
        kprintf("  TcpOutRsts:      %d\n", TcpOutRsts);
        kprintf("  TcpPassiveOpens: %d\n", TcpPassiveOpens);
        kprintf("  TcpRetransSegs:  %d\n", TcpRetransSegs);
        kprintf("  TcpRtoAlgorithm: %d\n", TcpRtoAlgorithm);
        kprintf("  TcpRtoMax:       %d\n", TcpRtoMax);
        kprintf("  TcpRtoMin:       %d\n", TcpRtoMin);

        kprintf("\nUDP MIB:\n");
        kprintf("  UdpInDatagrams:  %d\n", UdpInDatagrams);
        kprintf("  UdpInErrors:     %d\n", UdpInErrors);
        kprintf("  UdpNoPorts:      %d\n", UdpNoPorts);
        kprintf("  UdpOutDatagrams: %d\n", UdpOutDatagrams);

        kprintf("\nSNMP MIB:\n");
	kprintf("  snmpInPkts:              %d\n", snmpInPkts);
	kprintf("  snmpOutPkts              %d\n", snmpOutPkts);
	kprintf("  snmpInBadVersions:       %d\n", snmpInBadVersions);
	kprintf("  snmpInBadCommunityNames: %d\n", snmpInBadCommunityNames);
	kprintf("  snmpInBadCommunityUses:  %d\n", snmpInBadCommunityUses);
	kprintf("  snmpInASNParseErrs:      %d\n", snmpInASNParseErrs);
	kprintf("  snmpInTooBigs:           %d\n", snmpInTooBigs);
	kprintf("  snmpInNoSuchNames:       %d\n", snmpInNoSuchNames);
	kprintf("  snmpInBadValues:         %d\n", snmpInBadValues);
	kprintf("  snmpInReadOnlys:         %d\n", snmpInReadOnlys);
	kprintf("  snmpInGenErrs:           %d\n", snmpInGenErrs);
	kprintf("  snmpInTotalReqVars:      %d\n", snmpInTotalReqVars);
	kprintf("  snmpInTotalSetVars:      %d\n", snmpInTotalSetVars);
	kprintf("  snmpInGetRequests:       %d\n", snmpInGetRequests);
	kprintf("  snmpInGetNexts:          %d\n", snmpInGetNexts);
	kprintf("  snmpInSetRequests:       %d\n", snmpInSetRequests);
	kprintf("  snmpInGetResponses:      %d\n", snmpInGetResponses);
	kprintf("  snmpInTraps              %d\n", snmpInTraps);
	kprintf("  snmpOutTooBigs:          %d\n", snmpOutTooBigs);
	kprintf("  snmpOutNoSuchNames:      %d\n", snmpOutNoSuchNames);
	kprintf("  snmpOutBadValues:        %d\n", snmpOutBadValues);
	kprintf("  snmpOutGenErrs:          %d\n", snmpOutGenErrs);
	kprintf("  snmpOutGetRequests:      %d\n", snmpOutGetRequests);
	kprintf("  snmpOutGetNexts:         %d\n", snmpOutGetNexts);
	kprintf("  snmpOutSetRequests:      %d\n", snmpOutSetRequests);
	kprintf("  snmpOutGetResponses      %d\n", snmpOutGetResponses);
	kprintf("  snmpOutTraps:            %d\n", snmpOutTraps);
	kprintf("  snmpEnableAuthenTraps:   %d\n", snmpEnableAuthenTraps);

	return(OK);
}
