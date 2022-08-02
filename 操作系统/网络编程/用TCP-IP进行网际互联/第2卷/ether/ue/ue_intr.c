/* ue_intr.c - ue_intr */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ue.h>

/*------------------------------------------------------------------------
 * ue_intr - handle an SMC Ultra Ethernet device interrupt
 *------------------------------------------------------------------------
 */
void
ue_intr(struct devsw *pdev)
{
	struct utdev	*pud;
	static int	next;
	struct ep	*pep;
	int		i;
	void		*csr;
	unsigned int	intstat;

	pud = 0;
	for (i=0; i<Neth; ++i, ++next) {
		if (next >= Neth)
			next = 0;
		if (intstat = ue_hasintr(&ue[next])) {
			pud = &ue[next];
			break;
		}
	}
	if (pud == 0)
		return;
	csr = pud->ud_pdev->dvcsr;
	uewr(csr, W_INTMASK, 0);
	uewr(csr, INTSTAT, intstat);	/* clear the interrupt */
	if (intstat & INTSTAT_PTX)
		ue_xintr(pud, intstat & INTSTAT_TXE);
	if (intstat & INTSTAT_RXE)
		kprintf("receive error, rstat %x\n", uerd(csr, RSTAT));
	if (intstat & INTSTAT_TXE)
		kprintf("receive error, rstat %x\n", uerd(csr, TSTAT));
	uewr(csr, W_INTMASK, 0x7f);
	if (intstat & INTSTAT_PRX)
		ue_demux(pud);
}

/*------------------------------------------------------------------------
 * ue_hasintr - return true if this ue device has a pending interrupt
 *------------------------------------------------------------------------
 */
int
ue_hasintr(pud)
struct utdev	*pud;
{
	return uerd(pud->ud_pdev->dvcsr, INTSTAT);
}

/*------------------------------------------------------------------------
 * ue_xintr - handle a transmit interrupt on an SMC Ultra Ethernet
 *------------------------------------------------------------------------
 */
int
ue_xintr(struct utdev *pud, int err)
{
	if (err)
		kprintf("transmit error\n");
	pud->ud_xpending--;
	if (lenq(pud->ud_outq))
		ue_wstrt(pud);
}
