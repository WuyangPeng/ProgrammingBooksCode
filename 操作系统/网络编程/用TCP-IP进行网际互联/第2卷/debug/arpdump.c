/* arpdump.c - arpdump */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 * arpdump - pretty-print an ARP packet to the console
 *------------------------------------------------------------------------
 */
int arpdump(parp, order)
struct arp *parp;
int	order;
{
	short	hwtype, prtype, op;
	int	i;

	if (order & EPO_ARP) {
		hwtype = parp->ar_hwtype;
		prtype = parp->ar_prtype;
		op = parp->ar_op;
	} else {
		hwtype = net2hs(parp->ar_hwtype);
		prtype = net2hs(parp->ar_prtype);
		op = net2hs(parp->ar_op);
	}
	kprintf("ARP:\thw %x prot %x ", hwtype, prtype);
	kprintf("hwlen %d prlen %d op %d\nARP:\tSHA ", parp->ar_hwlen,
		parp->ar_prlen, op);
	for (i=0; i<parp->ar_hwlen-1; ++i)
		kprintf("%02x:", SHA(parp)[i] & 0xff);
	kprintf("%02x\tSPA ", SHA(parp)[i] & 0xff);
	for (i=0; i<parp->ar_prlen-1; ++i)
		kprintf("%u.", SPA(parp)[i] & 0xff);
	kprintf("%u\nARP:\tTHA ", SPA(parp)[i] & 0xff);
	for (i=0; i<parp->ar_hwlen-1; ++i)
		kprintf("%02x:", THA(parp)[i] & 0xff);
	kprintf("%02x\tTPA ", THA(parp)[i] & 0xff);
	for (i=0; i<parp->ar_prlen-1; ++i)
		kprintf("%u.", TPA(parp)[i] & 0xff);
	kprintf("%u\n\n", TPA(parp)[i] & 0xff);
}
