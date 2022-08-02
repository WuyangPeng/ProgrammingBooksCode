/* snoip.c - sip2ocpy, so2ipcpy, soipequ */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>

/*---------------------------------------------------------------------
 * sip2ocpy - copy an IP address into the object id structure
 *---------------------------------------------------------------------
 */
void
sip2ocpy(u_short *oidp, IPaddr pip)
{
	int 	i;
	
	for (i = 0; i < IP_ALEN; i++) {
	    *oidp++ = ((u_short) ((char *)&pip)[i]) & 0xff;
	}

}

/*---------------------------------------------------------------------
 * so2ipcpy - copy 4 sub-object ids into an IP address array
 *---------------------------------------------------------------------
 */
void
so2ipcpy(u_char *pip, u_short *oidp)
{
	int 	i;
	
	for (i = 0; i < IP_ALEN; i++)
	    pip[i] = (u_char) oidp[i] & 0xff;
}

/*---------------------------------------------------------------------
 * soipequ - test equality between an object id and an IP address
 *---------------------------------------------------------------------
 */
int
soipequ(u_short *oidp, IPaddr ip, int len)
{
	int 	i;

	for (i = 0; i < len; i++) {
	    u_char *pip = (u_char *)&ip;
	    if ((u_short) pip[i] != (u_short) oidp[i])
		return(FALSE);
	}
	return(TRUE);
}
#endif	/* SNMP */
