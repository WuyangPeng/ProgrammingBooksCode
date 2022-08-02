/* x_ifstat.c - x_ifstat */

#include <conf.h>
#include <kernel.h>
#include <network.h>

static	char *sn[] = { "DOWN", "UP", "UNUSED" };

/*------------------------------------------------------------------------
 *  x_ifstat  -  print interface status information
 *------------------------------------------------------------------------
 */
COMMAND	x_ifstat(stdin, stdout, stderr, nargs, args)
int	stdin, stdout, stderr, nargs;
char	*args[];
{
	char	host[32], mask[32];
	char	str[80];
	char	*dn;
	struct	netif	*pni;
	int	iface;

	if (nargs != 2) {
		sprintf(str, "usage: ifstat <intf>\n");
		write(stderr, str, strlen(str));
		return OK;
	}
	iface = atoi(args[1]);
	if (iface < 0 || iface >= Net.nif) {
		sprintf(str, "ifstat: illegal interface (0-%d)\n", Net.nif-1);
		write(stderr, str, strlen(str));
		return OK;
	}
	if (iface == NI_LOCAL) {
		sprintf(str, "Local interface state: %s\n",
			sn[nif[NI_LOCAL].ni_state]);
		write(stdout, str, strlen(str));
		return OK;
	}
	pni = &nif[iface];
	switch(pni->ni_dev) {
	case ETHER:	dn = "le0";
			break;
#if	Noth > 0
	case OTHER1:	dn = "on0";
			break;
	case OTHER2:	dn = "on1";
			break;
#endif	/* Noth > 0 */
	default:
		dn = "??";
	}
	sprintf(str,"%s: state=%x<%s>\n",dn,pni->ni_state,sn[pni->ni_state]);
	write(stdout, str, strlen(str));
	if (pni->ni_ivalid)
		sprintf(str, "IP %s NAME ", ip2dot(host, pni->ni_ip));
	else
		sprintf(str, "IP <invalid> NAME ");
	write(stdout, str, strlen(str));
	if (pni->ni_nvalid)
		sprintf(str, "\"%s\"\n", pni->ni_name);
	else
		sprintf(str, "<invalid>\n");
	write(stdout, str, strlen(str));
	if (pni->ni_svalid)
		sprintf(str, "MASK %s BROADCAST %s\n",
			ip2dot(mask, pni->ni_mask),
			ip2dot(host, pni->ni_brc));
	else
		sprintf(str, "MASK <invalid> BROADCAST <invalid>\n");
	write(stdout, str, strlen(str));
	sprintf(str,"MTU %d paddr %02x:%02x:%02x:%02x:%02x:%02x",
		pni->ni_mtu, pni->ni_hwa.ha_addr[0]&0xff,
		pni->ni_hwa.ha_addr[1]&0xff, pni->ni_hwa.ha_addr[2]&0xff,
		pni->ni_hwa.ha_addr[3]&0xff, pni->ni_hwa.ha_addr[4]&0xff,
		pni->ni_hwa.ha_addr[5]&0xff);
	write(stdout, str, strlen(str));
	sprintf(str, " bcast %02x:%02x:%02x:%02x:%02x:%02x\n",
		pni->ni_hwb.ha_addr[0]&0xff, pni->ni_hwb.ha_addr[1]&0xff,
		pni->ni_hwb.ha_addr[2]&0xff, pni->ni_hwb.ha_addr[3]&0xff,
		pni->ni_hwb.ha_addr[4]&0xff, pni->ni_hwb.ha_addr[5]&0xff);
	write(stdout, str, strlen(str));
	sprintf(str, "inq %d\n", pni->ni_ipinq);
	write(stdout, str, strlen(str));
	return(OK);
}
