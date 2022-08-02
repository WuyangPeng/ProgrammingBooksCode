/* netstart.c - netstart */

#include <conf.h>
#include <kernel.h>
#include <sleep.h>
#include <network.h>
#include <snmp.h>
#include <tcptimer.h>
#include <proc.h>
#include <date.h>

#ifdef OSPF
#include <ospf.h>
#endif /* OSPF */

extern	int	bsdbrc;

void arpinit(void), ipfinit(void), initgate(void), inithost(void);
void hginit(void);
int udpecho(), rwho();

/*------------------------------------------------------------------------
 *  netstart - initialize net
 *------------------------------------------------------------------------
 */
int
netstart(int userpid)
{
	char str[128];
	char *str1 = "sleeping 30 secs to get routes...";
	char *str2 = "\ndone.\n";
	unsigned long	now;
	int		i;

	if (clkruns == FALSE)
		panic("net: no clock");

	/* initialize ports */

	for (i=0 ; i<UPPS ; i++)
		upqs[i].up_valid = FALSE;
	udpmutex = screate(1);

	arpinit();
	ipfinit();	/* init the IP frag queue */

	/* these need a command to set/clear them. FIX ME!!! */
	gateway = 1;
	IpForwarding = 1;	/* == 2 if not a gateway */
	IfNumber = Net.nif - 1;

	/* bsdbrc = 1; */ /* uncomment to use 0's broadcast */

	if (gateway) {
		IPaddr	gw;
		initgate();
		gw = dot2ip(DEFRTR);
		rtadd(RT_DEFAULT, RT_DEFAULT, gw, RTM_INF-1, 1, RT_INF);
	} else
		inithost();
	rtadd(RT_LOOPBACK, ip_maskall, RT_LOOPBACK, 0, NI_LOCAL, RT_INF);

	for (i=0; i<Net.nif; ++i) {
		nif[i].ni_ipinq = newq(NI_INQSZ, QF_NOWAIT);
		nif[i].ni_hwtype = AR_HARDWARE;		/* for ARP */
		/* no OTHER's for now */
		if (i < 2)
			nif[i].ni_state = NIS_UP;
	}

	/*
	 * wait()'s synchronize to insure initialization is done
	 * before proceeding.
	 */

	resume(create(slowtimer, STSTK, STPRI, STNAM, STARGC));
	wait(Net.sema);
	resume(create(ipproc, IPSTK, IPPRI, IPNAM, IPARGC));
	wait(Net.sema);
	resume(create(tcptimer, TMSTK, TMPRI, TMNAM, TMARGC));
	wait(Net.sema);
	resume(create(tcpinp, TCPISTK, TCPIPRI, TCPINAM, TCPIARGC));
	wait(Net.sema);
	resume(create(tcpout, TCPOSTK, TCPOPRI, TCPONAM, TCPOARGC));
	wait(Net.sema);


	if (!gateway) {
		write(CONSOLE, str1, strlen(str1));
		sleep(30);
		write(CONSOLE, str2, strlen(str2));
	}

	/* get addrs & names */
	for (i=0; i<Net.nif; ++i) {
		IPaddr junk;
		char junk2[64];

		if (i == NI_LOCAL)
			continue;
		if (nif[i].ni_state != NIS_UP)
			continue;
		junk = getiaddr(i);
		sprintf(str,
		"if%d IP %s ha %02x:%02x:%02x:%02x:%02x:%02x ",
			i,
			ip2dot(junk2, nif[i].ni_ip),
			nif[i].ni_hwa.ha_addr[0]&0xff,
			nif[i].ni_hwa.ha_addr[1]&0xff,
			nif[i].ni_hwa.ha_addr[2]&0xff,
			nif[i].ni_hwa.ha_addr[3]&0xff,
			nif[i].ni_hwa.ha_addr[4]&0xff,
			nif[i].ni_hwa.ha_addr[5]&0xff);
		write(CONSOLE, str, strlen(str));
		sprintf(str, "br %02x:%02x:%02x:%02x:%02x:%02x\n",
			nif[i].ni_hwb.ha_addr[0]&0xff,
			nif[i].ni_hwb.ha_addr[1]&0xff,
			nif[i].ni_hwb.ha_addr[2]&0xff,
			nif[i].ni_hwb.ha_addr[3]&0xff,
			nif[i].ni_hwb.ha_addr[4]&0xff,
			nif[i].ni_hwb.ha_addr[5]&0xff);
		write(CONSOLE, str, strlen(str));

		icmp(ICT_MASKRQ, 0, nif[i].ni_brc, 0, 0);
		recvtim(30);	/* wait for an answer */
		getiname(i, junk2);
	}
	getutim(&now);

#ifdef	MULTICAST
	hginit();
#endif	/* MULTICAST */
#ifdef RIP
	resume(create(rip, RIPISTK, RIPPRI, RIPNAM, RIPARGC));
#endif	/* RIP */
#ifdef	OSPF
	resume(create(ospf, OSPFSTK, OSPFPRI, OSPFNAM, 0));
#endif /* OSPF */
#ifdef	SNMP
	resume(create(snmpd, SNMPSTK, SNMPPRI, SNMPDNAM, 0));
#endif	/* SNMP */

	rwho();
	resume(create(FINGERD, FNGDSTK, FNGDPRI, FNGDNAM, FNGDARGC));
	resume(create(ECHOD, ECHOSTK, ECHOPRI, ECHODNAM, 0));
	resume(create(udpecho, 1000, 50, "udpecho", 0));

	resume(userpid);
}

struct	netif		nif[NIF];
struct	netinfo		Net;
