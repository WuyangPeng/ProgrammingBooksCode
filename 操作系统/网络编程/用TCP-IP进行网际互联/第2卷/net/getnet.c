/* getnet.c - getnet, getinet */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  getnet  -  obtain the network portion of this system's IP address
 *------------------------------------------------------------------------
 */
IPaddr
getnet()
{
	return getiaddr(NI_PRIMARY);
}

/*------------------------------------------------------------------------
 *  getinet  -  obtain the network portion of this interface's IP address
 *------------------------------------------------------------------------
 */
IPaddr
getinet(int inum)
{
	struct netif	*pif;

	if (inum < 0 || inum >= Net.nif)
		return (IPaddr)SYSERR;
	pif = &nif[inum];
	if (!pif->ni_ivalid && getiaddr(inum) == (IPaddr)SYSERR)
		return (IPaddr)SYSERR;
	return pif->ni_net;
}
