/* icsetsrc.c - icsetsrc */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  icsetsrc -  set the source address on an ICMP packet
 *------------------------------------------------------------------------
 */
void
icsetsrc(struct ip *pip)
{
	int	i;

	for (i=0; i<Net.nif; ++i) {
		if (i == NI_LOCAL)
			continue;
		if (netmatch(pip->ip_dst,nif[i].ni_ip,nif[i].ni_mask,0))
			break;
	}
	if (i == Net.nif)
		pip->ip_src = ip_anyaddr;
	else
		pip->ip_src = nif[i].ni_ip;
}
