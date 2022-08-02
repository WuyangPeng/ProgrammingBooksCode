/* ipproc.c - ipproc */

#include <conf.h>
#include <kernel.h>
#include <network.h>

struct	ep	*ipgetp(int *);
struct	route	*rtget(IPaddr, Bool);

/*------------------------------------------------------------------------
 *  ipproc  -  handle an IP datagram coming in from the network
 *------------------------------------------------------------------------
 */
PROCESS
ipproc(void)
{
	struct	ep	*pep;
	struct	ip	*pip;
	struct	route	*prt;
	Bool		nonlocal;
	int		ifnum;

	ippid = getpid();	/* so others can find us	*/

	signal(Net.sema);	/* signal initialization done	*/

	while (TRUE) {
		pep = ipgetp(&ifnum);
		pip = (struct ip *)pep->ep_data;

		if ((pip->ip_verlen>>4) != IP_VERSION) {
			IpInHdrErrors++;
			freebuf(pep);
			continue;
		}
		if (IP_CLASSE(pip->ip_dst)) {
			IpInAddrErrors++;
			freebuf(pep);
			continue;
		}
		if (ifnum != NI_LOCAL) {
			if (cksum((WORD *)pip, IP_HLEN(pip))) {
				IpInHdrErrors++;
				freebuf(pep);
				continue;
			}
			ipnet2h(pip);
			pep->ep_order |= EPO_IP;
		}
		prt = rtget(pip->ip_dst, (ifnum == NI_LOCAL));

		if (prt == NULL) {
			if (gateway) {
				iph2net(pip);
				pep->ep_order &= ~EPO_IP;
				icmp(ICT_DESTUR, ICC_NETUR,
						pip->ip_src, pep, 0);
			} else {
				IpOutNoRoutes++;
				freebuf(pep);
			}
			continue;
		}
		nonlocal = ifnum != NI_LOCAL && prt->rt_ifnum != NI_LOCAL;
		if (!gateway && nonlocal) {
			IpInAddrErrors++;
			freebuf(pep);
			rtfree(prt);
			continue;
		}
		if (nonlocal)
			IpForwDatagrams++;
		/* fill in src IP, if we're the sender */

		if (ifnum == NI_LOCAL) {
			if (pip->ip_src == ip_anyaddr)
				if (prt->rt_ifnum == NI_LOCAL)
					pip->ip_src = pip->ip_dst;
				else
					pip->ip_src =
						nif[prt->rt_ifnum].ni_ip;
		} else if (--(pip->ip_ttl) == 0 &&
				prt->rt_ifnum != NI_LOCAL) {
			IpInHdrErrors++;
			iph2net(pip);
			pep->ep_order &= ~EPO_IP;
			icmp(ICT_TIMEX, ICC_TIMEX, pip->ip_src, pep, 0);
			rtfree(prt);
			continue;
		}
		ipdbc(ifnum, pep, prt);	/* handle directed broadcasts	*/
		ipredirect(pep, ifnum, prt); /* do redirect, if needed	*/
		if (prt->rt_metric != 0)
			ipputp(prt->rt_ifnum, prt->rt_gw, pep);
		else
			ipputp(prt->rt_ifnum, pip->ip_dst, pep);
		rtfree(prt);
	}
}

int	ippid, gateway, bsdbrc;
