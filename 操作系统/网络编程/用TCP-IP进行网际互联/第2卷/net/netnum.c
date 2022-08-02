/* netnum.c - netnum */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  netnum  -  compute the network portion of a given IP address
 *------------------------------------------------------------------------
 */
IPaddr
netnum(IPaddr ipa)
{
	IPaddr	mask = ~0;

	if (IP_CLASSA(ipa)) mask = hl2net(0xff000000);
	if (IP_CLASSB(ipa)) mask = hl2net(0xffff0000);
	if (IP_CLASSC(ipa)) mask = hl2net(0xffffff00);
	return ipa & mask;
}
