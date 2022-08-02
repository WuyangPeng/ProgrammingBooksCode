/* getiaddr.c - getiaddr */

#include <conf.h>
#include <kernel.h>
#include <network.h>

int rarpsend(int);

/*------------------------------------------------------------------------
 *  getiaddr  -  obtain this interface's complete address (IP address)
 *------------------------------------------------------------------------
 */
IPaddr
getiaddr(int inum)
{
	struct netif	*pif;

	if (inum == NI_LOCAL || inum < 0 || inum >= Net.nif)
		return (IPaddr)SYSERR;
	pif = &nif[inum];
	wait (rarpsem);
	if (!pif->ni_ivalid && pif->ni_state == NIS_UP) {
		(void) rarpsend(inum);
	}
	signal(rarpsem);

	if (!pif->ni_ivalid)
		return (IPaddr)SYSERR;
	return pif->ni_ip;
}
