/* netmatch.c - netmatch */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  netmatch  -  Is "dst" on "net"?
 *------------------------------------------------------------------------
 */
Bool
netmatch(IPaddr dst, IPaddr net, IPaddr mask, Bool islocal)
{
	if ((dst & mask) != (net & mask))
		return FALSE;
	/*
	 * local srcs should only match unicast addresses (host routes)
	 */
	if (islocal)
		if (isbrc(dst) || IP_CLASSD(dst))
			return mask != ip_maskall;
	return TRUE;
}
