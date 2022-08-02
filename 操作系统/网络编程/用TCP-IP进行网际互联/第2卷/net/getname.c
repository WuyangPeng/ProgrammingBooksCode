/* getname.c - getname, getiname */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  getname  -  get name of this host and place it where specified
 *------------------------------------------------------------------------
 */
SYSCALL
getname(char *nam)
{
	return getiname(NI_PRIMARY, nam);
}

/*------------------------------------------------------------------------
 *  getiname  -  get name of this host and place it where specified
 *------------------------------------------------------------------------
 */
int
getiname(int ifn, char *nam)
{
	struct	netif *intf;
	IPaddr	myaddr;
	char	*p;

	if (ifn < 0 || ifn >= Net.nif)
		return SYSERR;
	intf = &nif[ifn];
	*nam = NULLCH;
	if (!intf->ni_nvalid) {
		myaddr = getiaddr(ifn);
		if (ip2name(myaddr, intf->ni_name) == (char *)SYSERR)
			return SYSERR;
		intf->ni_nvalid = TRUE;
	}
	for (p=intf->ni_name ; p && *p != NULLCH; )
		*nam++ = *p++;
	*nam = NULLCH;
	return OK;
}
