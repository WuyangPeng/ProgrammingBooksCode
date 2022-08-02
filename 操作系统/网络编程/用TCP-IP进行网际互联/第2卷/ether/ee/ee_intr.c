/* ee_intr.c - ee_intr */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ee.h>

/*------------------------------------------------------------------------
 * ee_intr - handle an Intel EtherExpress16 device interrupt
 *------------------------------------------------------------------------
 */
int
ee_intr()
{
	static int	next;
	struct etdev	*ped;
	int		i, csr, status;

	ped = 0;
	for (i=0; i<Neth; ++i, ++next) {
		if (next >= Neth)
			next = 0;
		ped = &ee[next];
		if ((status = ee_hasintr(ped)) & 0xf000)
			break;
	}
	if (i == Neth)
		return;
	csr = ped->ed_pdev->dvcsr;

	ee_ack(ped, status);

	if (status & (STAT_CX|STAT_CNA))
		ee_xintr(ped);

	/*
	 * ee_demux can cause a context switch, so must re-enable board
	 * interrupt latch before calling it.
	 */
	outb(csr+SIRQ, ped->ed_irq);
	outb(csr+SIRQ, ped->ed_irq | SIRQ_IEN);

	if (status & STAT_FR)
		ee_demux(ped);
}

/*------------------------------------------------------------------------
 * ee_hasintr - return true if this ee device has a pending interrupt
 *------------------------------------------------------------------------
 */
int
ee_hasintr(ped)
struct etdev	*ped;
{
	struct scb	*pscb = ped->ed_scb;

	ee_wait(ped);
	return pscb->scb_status & 0xf000;
}

/*------------------------------------------------------------------------
 * ee_xintr - handle a transmit interrupt on an Intel EtherExpress
 *------------------------------------------------------------------------
 */
int
ee_xintr(ped)
struct etdev	*ped;
{
	struct cbl	*pcbl = ped->ed_cbl;

	if (pcbl->cbl_status & TSTAT_C) {
		if (!(pcbl->cbl_status & TSTAT_OK)) {
			kprintf("ee%d: tranmission error, status %x\n",
				ped->ed_pdev->dvminor, pcbl->cbl_status);
			nif[ped->ed_ifnum].ni_oerrors++;
		}
		if (!ped->ed_xpending)
			kprintf("stray transmit interrupt\n");
		else
			ped->ed_xpending--;
		pcbl->cbl_status = 0;
	}
	if (lenq(ped->ed_outq))
		ee_wstrt(ped);
}
