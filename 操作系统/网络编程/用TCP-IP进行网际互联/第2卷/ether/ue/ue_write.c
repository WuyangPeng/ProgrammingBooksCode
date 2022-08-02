/* ue_write.c - ue_write */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 * ue_write - write a single packet to an SMC Ultra Ethernet
 *------------------------------------------------------------------------
 */
int
ue_write(struct devsw *pdev, unsigned char *pep0, unsigned len)
{
	struct ep	*pep = (struct ep *)pep0;
	struct utdev	*pud;

	pud = (struct utdev *)pdev->dvioblk;
	if (len > EP_MAXLEN) {
		nif[pud->ud_ifnum].ni_odiscard++;
		freebuf(pep);
		return SYSERR;
	}
	/* subtract the local header */
	len -= (int)&pep->ep_eh - (int)pep;
	if (len < EP_MINLEN)
		len = EP_MINLEN;
	memcpy(pep->ep_src, pud->ud_paddr, EP_ALEN);
	pep->ep_len = len;
	pep->ep_type = hs2net(pep->ep_type);
	pep->ep_order &= ~EPO_NET;
		
	if (enq(pud->ud_outq, pep, 0) < 0) {
		nif[pud->ud_ifnum].ni_odiscard++;
		freebuf(pep);
		ue_wstrt(pud);
		return SYSERR;
	}
	ue_wstrt(pud);
	return OK;
}
