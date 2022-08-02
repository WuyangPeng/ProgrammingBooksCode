/* netmask.c - netmask */

#include <conf.h>
#include <kernel.h>
#include <network.h>

IPaddr netnum(IPaddr);

/*------------------------------------------------------------------------
 *  netmask  -  set the default mask for the given net
 *------------------------------------------------------------------------
 */
IPaddr
netmask(IPaddr net)
{
	IPaddr	netpart;
	int	i;

	if (net == 0)
		return net;
	/* check for net match (for subnets) */

	netpart = netnum(net);
	for (i=0; i<Net.nif; ++i)
		if (nif[i].ni_svalid && nif[i].ni_ivalid &&
		    nif[i].ni_net == netpart)
			return nif[i].ni_mask;
	if (IP_CLASSA(net)) return hl2net(0xff000000);
	if (IP_CLASSB(net)) return hl2net(0xffff0000);
	if (IP_CLASSC(net)) return hl2net(0xffffff00);
	return ~0;
}
