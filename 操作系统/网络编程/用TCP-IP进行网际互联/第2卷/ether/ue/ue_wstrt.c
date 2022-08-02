/* ue_wstrt.c - ue_wstrt */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ue.h>

/*------------------------------------------------------------------------
 * ue_wstrt - start output on an SMC Ultra Ethernet device
 *------------------------------------------------------------------------
 */
int
ue_wstrt(pud)
struct utdev	*pud;
{
	STATWORD	ps;
	unsigned char	*xmbuf;		/* transmit buffer address	*/
	unsigned int	xmaddr;		/* transmit buf addr to card	*/
	unsigned int	csr;
	struct ep	*pep;
	int		len, isbcast;

	disable(ps);
	if (pud->ud_xpending) {
		restore(ps);
		return OK;
	}
	pud->ud_xpending++;
	pep = (struct ep *)deq(pud->ud_outq);
	if (pep == 0) {
		pud->ud_xpending--;
		restore(ps);
		return OK;
	}
	isbcast = !memcmp(pep->ep_dst, pud->ud_bcast, EP_ALEN);
	len = pep->ep_len;
	/* this version supports one packet per interrupt only */

	xmaddr = pud->ud_xmaddr;
	xmbuf = (unsigned char *) (pud->ud_iomem + xmaddr * UE_BUFSIZE);
	pud->ud_wretry = EP_RETRY;
	memcpy(xmbuf, &pep->ep_eh, pep->ep_len);
	csr = pud->ud_pdev->dvcsr;
	uewr(csr, W_TSTARTH, xmaddr);
	uewr(csr, W_TCNTH, (len >> 8) & 0xff);
	uewr(csr, W_TCNTL, len & 0xff);
	uewr(csr, CMD, uerd(csr, CMD) | CMD_TXP);
	restore(ps);
	freebuf(pep);
	if (isbcast)
		nif[pud->ud_ifnum].ni_onucast++;
	else
		nif[pud->ud_ifnum].ni_oucast++;
	nif[pud->ud_ifnum].ni_ooctets += len;
}
