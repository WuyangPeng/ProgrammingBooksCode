/* ee_init.c - ee_init */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <i386.h>
#include <ee.h>
#include <q.h>

static unsigned char	eeirq[] = {255, 9, 3, 4, 5, 10, 11, 255 };

unsigned char eecf[] = { 0x0c, 0x08, 0x00, 0x2e, 0x00, 0x60, 0x00, 0xf2,
	0x00, 0x00, 0x40, 0x00 };

/*------------------------------------------------------------------------
 * ee_init - startup initialization of Intel EtherExpress device
 *------------------------------------------------------------------------
 */
int
ee_init(pdev)
struct devsw	*pdev;
{
	struct etdev	*ped;
	unsigned short	eedat, wtmp, *pw;
	unsigned char	irq, tmp, memc, mempc, memdec;
	int		i, offset, ee_int();
	unsigned char	*pdbuf;
	unsigned short	rom[64];
	struct cbl	*pcbl;
	struct iscp	*piscp;
	struct scb	*pscb;
	struct rfd	*prfd;
	struct rbd	*prbd;
	struct tbd	*ptbd;

	pdev->dvioblk = (char *) ped = &ee[pdev->dvminor];
	ped->ed_pdev = pdev;
	ped->ed_outq = newq(ETOUTQSZ, QF_NOWAIT);
	ped->ed_ifnum = -1;
	ped->ed_descr = "Intel EtherExpress";
	ped->ed_mcc = 0;
	ped->ed_xpending = 0;

	/* read ROM data */

	for (i=0; i<EE_ROMSIZE; ++i)
		rom[i] = ee_romread(pdev->dvcsr, i);

	for (i=0; i<16; ++i)
		if ((inb(pdev->dvcsr + AID) & 0xf) != i)
			break;
	if (i < 16) {
		kprintf("ee_init: no EtherExpress at 0x%03x\n", pdev->dvcsr);
		return SYSERR;
	}
	/* set IRQ */

	irq = pdev->dvivec - IRQBASE;
	for (i=0; i<sizeof(eeirq); ++i)
		if (eeirq[i] == irq) {
			ped->ed_irq = i;
			break;
		}
	if (i == sizeof(eeirq)) {
		kprintf("ee%d: invalid IRQ (%d)\n", pdev->dvminor, irq);
		return SYSERR;
	} else {
		eedat = rom[EE_BOARD];
		eedat >>= 13;
		if (eeirq[eedat] != irq)
			kprintf("ee%d: WARNING ROM IRQ (%d) differs\n",
				pdev->dvminor, eeirq[eedat]);
		ped->ed_irq = eedat;
		irq = eeirq[eedat];
	}
	set_evec(pdev->dvivec, ee_int);

#ifdef notdef
/*XXX */
	/* test & set BUS timing */
	tmp = inb(pdev->dvcsr + CONFIG);
	outb(pdev->dvcsr + CONFIG, tmp | CONFIG_IOTE);

	/* do an I/O for the test */
	outb(pdev->dvcsr + RDPTR, 0);
	inw(pdev->dvcsr + DXREG);

	tmp = inb(pdev->dvcsr + CONFIG);
	if (tmp & CONFIG_TOGGLE) {
		if (tmp & CONFIG_ICLATE)
			tmp &= ~CONFIG_16EN;	/* force 8-bit mode */
		else
			tmp |= CONFIG_ICLATE;
	}
	tmp &= ~(CONFIG_IOTE|CONFIG_TOGGLE);
	outb(pdev->dvcsr + CONFIG, tmp);
#endif
	/* "warm up" DRAMS-- requires 16 bytes buf access */

	outb(pdev->dvcsr + RDPTR, 0);
	for (i=0; i<16; ++i)
		inw(pdev->dvcsr + DXREG);

	/* set up SCP */

	outw(pdev->dvcsr+WRPTR, SCP);
	outw(pdev->dvcsr+DXREG, SYSBUS_16);	/* 16-bit bus */
	outw(pdev->dvcsr+DXREG, 0);	/* skip unused words */
	outw(pdev->dvcsr+DXREG, 0);
	outw(pdev->dvcsr+DXREG, ISCP & 0xffff);
	outw(pdev->dvcsr+DXREG, ISCP >> 16);

	outb(pdev->dvcsr + EEC, EEC_586R);	/* reset 82586		*/
	outb(pdev->dvcsr + EEC, 0);		/* clear reset		*/

	/* set buffer memory map */

	eedat = rom[EE_MEM1];
	memc = eedat & 0xff;
	mempc = eedat >> 8;
	memdec = rom[EE_MEM2];
	mempc = ~memdec;
	tmp = 0x80;
	for (i=7; i>=0; --i, tmp >>= 1)
		if (memdec & tmp) {
			ped->ed_iomem = 0xc0000 + i * 0x4000;
			break;
		}
	if (i < 0) {
		ped->ed_iomem = 0xcc000;
		kprintf("invalid ROM configuration, setting to iomem %X\n", 
			ped->ed_iomem);
		memdec = 0x8;
		memc = 0x1c;
	}
#ifdef notdef
	/* test and set mempc */

	pw = (unsigned short *)0xc0000;
	mempc = 0;
	for (i=0; i<8; ++i) {
		mempc >>= 1;
		outb(pdev->dvcsr + CONFIG, CONFIG_MCS16);
		wtmp = *pw;	/* reference it */
		mempc |= inb(pdev->dvcsr + CONFIG) & 0x80;
		pw += 8192;
	}
	outb(pdev->dvcsr + CONFIG, CONFIG_MCS16);
	wtmp = *(unsigned short *)0xf0000;
	if (inb(pdev->dvcsr + CONFIG) & 0x80)
		memc |= MEMC_MCS16;
	else
		memc &= ~MEMC_MCS16;
#endif

	outb(pdev->dvcsr + MEMDEC, memdec);
	outb(pdev->dvcsr + MEMC, memc);
	outb(pdev->dvcsr + MEMPC, mempc);

	for (i=0; i<EP_ALEN/2 ; ++i) {
		eedat = rom[EE_EADDR + i];

		ped->ed_paddr[EP_ALEN - 2*i -1] = eedat & 0xff;
		ped->ed_paddr[EP_ALEN - 2*i -2] = eedat >> 8;
		ped->ed_bcast[2*i] = ~0;
		ped->ed_bcast[2*i+1] = ~0;
	}
	kprintf("ee%d: etheraddr %02x:%02x:%02x:%02x:%02x:%02x ",
		pdev->dvminor,
		ped->ed_paddr[0] & 0xff,
		ped->ed_paddr[1] & 0xff,
		ped->ed_paddr[2] & 0xff,
		ped->ed_paddr[3] & 0xff,
		ped->ed_paddr[4] & 0xff,
		ped->ed_paddr[5] & 0xff);
	kprintf("irq %d iomem %X\n", irq, ped->ed_iomem);

	piscp = (struct iscp *) (ped->ed_iomem + ISCP);
	piscp->iscp_busy = 1;
	piscp->iscp_scboff = SCB;
	piscp->iscp_scbbase = 0;

	pscb = (struct scb *)(ped->ed_iomem + SCB);
	ped->ed_scb = pscb;
	bzero(pscb, sizeof(struct scb));
	offset = (unsigned int)pscb + sizeof(struct scb);

	/* allocate space for a command block */

	pcbl = (struct cbl *)offset;
	ped->ed_cbl = pcbl;
	pcbl->cbl_next = 0xffff;
	offset += sizeof(struct cbl);

	/* allocate transmit buffer */

	ptbd = ped->ed_tbd = (struct tbd *)offset;
	ptbd->tbd_count = 0;
	ptbd->tbd_eof = 1;
	ptbd->tbd_next = H2IO(ped, ptbd);
	offset += sizeof(struct tbd);
	ped->ed_xmbuf = (unsigned char *)offset;
	ptbd->tbd_buf = H2IO(ped, ped->ed_xmbuf);
	offset += EDLEN;

	/* initialize receive buffers */

	ped->ed_rfd = (struct rfd *)offset;
	offset += EE_NRX * sizeof(struct rfd);
	ped->ed_rbd = (struct rbd *)offset;
	offset += EE_NRX * sizeof(struct rbd);
	pdbuf = (unsigned char *)offset;
	prfd = ped->ed_rfd;
	prbd = ped->ed_rbd;
	for (i=0; i<EE_NRX; ++i) {
		prfd->rfd_status = 0;
		prfd->rfd_cmd = 0;
		prfd->rfd_next = H2IO(ped, prfd + 1);
		prfd->rfd_rbd = H2IO(ped, prbd);

		prbd->rbd_count = 0;
		prbd->rbd_valid = 0;
		prbd->rbd_eof = 0;
		prbd->rbd_next = H2IO(ped, prbd + 1);
		prbd->rbd_buf = H2IO(ped, pdbuf);
		prbd->rbd_size = EDLEN;
		prbd->rbd_el = 0;

		prfd++;
		prbd++;
		pdbuf += EDLEN;
	}
	prfd--; prbd--;	/* go back to last one */

	prfd->rfd_cmd = EECMD_EL;	/* mark end of receive FD list	*/
	prfd->rfd_next = H2IO(ped, ped->ed_rfd);
	ped->ed_rfdend = prfd;

	prbd->rbd_el = 1;
	prbd->rbd_next = H2IO(ped, ped->ed_rbd);
	ped->ed_rbdend = prbd;

	pscb->scb_rfaoff = H2IO(ped, ped->ed_rfd);

	outb(pdev->dvcsr + CAC, 0);		/* start the 82586	*/

	for (i=0; i<200; ++i) {
		if (!piscp->iscp_busy)
			break;
		delay(1);
	}
	if (i == 200) {
		kprintf("ee%d: failed initialization\n", pdev->dvminor);
		return SYSERR;
	}
	for (i=0; i<200; ++i) {
		if (pscb->scb_status == STAT_CX|STAT_CNA)
			break;
		delay(1);
	}
	if (i == 200) {
		kprintf("ee%d: failed status check (status %x)\n",
			pdev->dvminor, pscb->scb_status);
		return SYSERR;
	}

	/* configure */

	ee_cmd(ped, EECMD_CONFIG, eecf);
	ee_ack(ped, pscb->scb_status);

	/* set station address */

	ee_cmd(ped, EECMD_IASET, ped->ed_paddr);
	ee_ack(ped, pscb->scb_status);

	/* start frame reception */
	ee_wait(ped);
	pscb->scb_cmd = (pscb->scb_status & 0xf000) | SCBCMD_RUS;
	pscb->scb_status = 0;

	outb(pdev->dvcsr + CAC, 0);	/* start the 82586	*/

	outb(pdev->dvcsr+SIRQ, ped->ed_irq | SIRQ_IEN);	/* enable interrupts */
	return OK;
}

int
eedump(ped)
struct etdev *ped;
{
	struct iscp	*piscp = (struct iscp *)ped->ed_iomem;
	struct scb	*pscb = ped->ed_scb;
	struct cbl	*pcbl = ped->ed_cbl;
	struct rfd	*prfd = ped->ed_rfd;
	struct rbd	*prbd = ped->ed_rbd;
	struct tbd	*ptbd = ped->ed_tbd;
	int		i;

	kprintf("\n\nprfd %X prfdend %X prbd %X prbdend %X ptbd %X\n",
		ped->ed_rfd, ped->ed_rfdend, ped->ed_rbd, ped->ed_rbdend,
		ped->ed_tbd);
	kprintf("ISCP: host %X IO %X busy %x scboff %X scbbase %X\n",
		piscp, H2IO(ped, piscp), piscp->iscp_busy, piscp->iscp_scboff,
		piscp->iscp_scbbase);
	kprintf("SCB: host %X IO %X status %x cmd %x cbloff %x rfaoff %x\n",
		pscb, H2IO(ped, pscb),
		pscb->scb_status, pscb->scb_cmd, pscb->scb_cbloff,
		pscb->scb_rfaoff);
	kprintf("SCB: errors: crc %d align %d resource %d over %d\n",
		pscb->scb_ecrc, pscb->scb_ealign, pscb->scb_eresource,
		pscb->scb_eover);
	kprintf("CBL: status %x cmd %x next %x size %d\n", pcbl->cbl_status,
		pcbl->cbl_cmd, pcbl->cbl_next, sizeof(struct cbl));
	kprintf("TBD: count %d eof %d next %X buf %X\n", ptbd->tbd_count,
		ptbd->tbd_eof, ptbd->tbd_next, ptbd->tbd_buf);
	for (i=0; i<EE_NRX; ++i) {
		kprintf("RFD%d: host %X IO %X status %x cmd %x next %x ",
			i, prfd, H2IO(ped, prfd), prfd->rfd_status,
			prfd->rfd_cmd, prfd->rfd_next);
		kprintf("rbd %x\n", prfd->rfd_rbd);
		prfd = (struct rfd *)IO2H(ped, prfd->rfd_next);
	}
	for (i=0; i<EE_NRX; ++i) {
		kprintf("RBD%d: host %X IO %X count %d valid %d eof %d ",
			i, prbd, H2IO(ped, prbd), prbd->rbd_count,
			prbd->rbd_valid, prbd->rbd_eof);
		kprintf("next %x buf %X bsize %d el %d\n",
			prbd->rbd_next, prbd->rbd_buf, prbd->rbd_size,
			prbd->rbd_el);
		prbd = (struct rbd *)IO2H(ped, prbd->rbd_next);
	}
	kprintf("\n\n");
}
