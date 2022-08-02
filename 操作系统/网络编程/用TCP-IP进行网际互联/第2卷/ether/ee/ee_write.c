/* ee_write.c - ee_write */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 * ee_write - write a single packet to an Intel EtherExpress
 *------------------------------------------------------------------------
 */
int
ee_write(pdev, pep, len)
struct devsw	*pdev;
struct ep	*pep;
int		len;
{
	struct etdev	*ped;

	ped = (struct etdev *)pdev->dvioblk;
	if (len > EP_MAXLEN) {
		nif[ped->ed_ifnum].ni_odiscard++;
		freebuf(pep);
		return SYSERR;
	}
	/* subtract the local header */
	len -= (int)&pep->ep_eh - (int)pep;
	if (len < EP_MINLEN)
		len = EP_MINLEN;
	memcpy(pep->ep_src, ped->ed_paddr, EP_ALEN);
	pep->ep_len = len;
	pep->ep_type = hs2net(pep->ep_type);
	pep->ep_order &= ~EPO_NET;
		
	if (enq(ped->ed_outq, pep, 0) < 0) {
		nif[ped->ed_ifnum].ni_odiscard++;
		freebuf(pep);
		ee_wstrt(ped);
		return SYSERR;
	}
	ee_wstrt(ped);
	return OK;
}
