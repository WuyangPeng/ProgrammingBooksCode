/* ue_init.c - ue_init */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ue.h>
#include <q.h>
#include <i386.h>

static int	ramsize[4] = { 8192, 16384, 32768, 65536 };

static	currpage;	/* current register page	*/

/*------------------------------------------------------------------------
 * ue_init - startup initialization of SMC Ultra Ethernet device
 *------------------------------------------------------------------------
 */
int
ue_init(pdev)
struct devsw	*pdev;
{
int mbase;
	struct utdev	*pud;
	unsigned char	tmp, rcon;
	unsigned short	*p;
	unsigned int	fn, i, ue_nrx, ue_int();

	pdev->dvioblk = (char *) pud = &ue[pdev->dvminor];
	pud->ud_pdev = pdev;
	pud->ud_outq = newq(ETOUTQSZ, QF_NOWAIT);
	pud->ud_ifnum = -1;
	pud->ud_descr = "SMC Ultra Ethernet";
	pud->ud_xpending = 0;

	for (i=0; i<6 ; ++i) {
		pud->ud_paddr[i] = inb(pdev->dvcsr + EADDR + i);
		pud->ud_bcast[i] = ~0;
	}

	tmp = inb(pdev->dvcsr + HWR);
	outb(pdev->dvcsr + HWR, tmp | HWR_SWH);
	pud->ud_iomem = inb(pdev->dvcsr + RAR);
	pud->ud_iosize = ramsize[(pud->ud_iomem >> 4) & 3];
	pud->ud_iomem = ((pud->ud_iomem & 0x40) << 17) |
		(pud->ud_iomem & 0x0f)<<13 | 0xC0000;
	uewr(pdev->dvcsr, GCR, uerd(pdev->dvcsr, GCR) | GCR_LIT);

	kprintf("ue%d: %02x:%02x:%02x:%02x:%02x:%02x, bid %x",
		pdev->dvminor,
		pud->ud_paddr[0] & 0xff,
		pud->ud_paddr[1] & 0xff,
		pud->ud_paddr[2] & 0xff,
		pud->ud_paddr[3] & 0xff,
		pud->ud_paddr[4] & 0xff,
		pud->ud_paddr[5] & 0xff,
		inb(pdev->dvcsr + BOARDID));
	kprintf(" irq %d iomem %X (%d K)\n", pdev->dvivec - IRQBASE,
		pud->ud_iomem, pud->ud_iosize/1024);

	/* disable ROM address mapping */
	uewr(pdev->dvcsr, BIO, 0x30);

	/* enable host access to interface memory */
	outb(pdev->dvcsr + CR, CR_MENB);


	currpage = 0;
	UEPAGE(pdev->dvcsr, currpage);	/* sync currpage w/ chip */
	for (i=0; i<EP_ALEN; ++i)
		uewr(pdev->dvcsr, STA0+i, pud->ud_paddr[i]);

	uewr(pdev->dvcsr, W_DCON, DCON_BUS16);

	/* clear interface memory */

	p = (unsigned short *)pud->ud_iomem;
	for (i=0; i<pud->ud_iosize / 2; ++i, ++p) {
		*p = 0;
		if (*p)
			kprintf("%X not zero but %x\n", p, *p);
	}
	/* set up receive ring */
	p=(unsigned short *)pud->ud_iomem;
	pud->ud_rmin = (int)p;
	ue_nrx = (pud->ud_iosize / 256) - 6;	/* io size - 1 xmit pack */
	pud->ud_xmaddr = ue_nrx;
	pud->ud_rmax = (int)p + (ue_nrx << 8);
	for (fn=1; fn < ue_nrx; ++fn) {
		*p = fn << 8;
		p += 128;	/* 128 shorts, 256 bytes */
	}

	mbase = 0;	/* start of receive buffers */
	uewr(pdev->dvcsr, W_RSTART, mbase);	/* RSTART = 0 */
	uewr(pdev->dvcsr, W_RSTOP, mbase + ue_nrx); /* RSTOP */

	uewr(pdev->dvcsr, BOUND, mbase + ue_nrx - 1);	/* BOUND = RSTOP-1 */
	uewr(pdev->dvcsr, CURR, mbase);
	pud->ud_nextbuf = mbase;

	uewr(pdev->dvcsr, NEXT, mbase);
	uewr(pdev->dvcsr, RADDH, mbase);
	uewr(pdev->dvcsr, RADDL, mbase);

	uewr(pdev->dvcsr, W_INTMASK, 0x7f);

	set_evec(pdev->dvivec, ue_int);

	rcon = RCON_BROAD | RCON_RCA;
#ifdef	MULTICAST
	rcon |= RCON_GROUP;
#endif	/* MULTICAST */
#ifdef	NETMON
/*	rcon |= RCON_PROM; */
#endif	/* NETMON */
	uewr(pdev->dvcsr, W_RCON, rcon);

	/* enable the device */

	uewr(pdev->dvcsr, ICR, ICR_EIL);
	tmp = uerd(pdev->dvcsr, CMD);
	tmp |= CMD_STA;
	tmp &= ~CMD_STP;
	uewr(pdev->dvcsr, CMD, tmp);
}


uewr(csr, reg, value)
unsigned int	csr, reg;
unsigned char	value;
{
	int	newpage;

	newpage = reg >> 8;
	if (newpage != currpage)
		UEPAGE(csr, newpage);
	outb(csr + (reg & 0x1f), value);
}

int
uerd(csr, reg)
unsigned int	csr, reg;
{
	int	newpage;

	newpage = reg >> 8; 
	if (newpage != currpage)
		UEPAGE(csr, newpage);
	return inb(csr + (reg & 0x1f));
}

ue_dump(csr)
unsigned int	csr;
{
	unsigned char ocmd, ohwr;
	int		i;

	ohwr = inb(csr + HWR);
	ocmd = inb(csr + CMD);
	for (i=0; i< 8; ++i)
		kprintf("%02x ", inb(csr + i));
	outb(csr + HWR, ohwr & ~HWR_SWH);
	kprintf("\nswh = 0: ");
	for (i=8; i < 16; ++i)
		kprintf("%02x ", inb(csr + i));
	outb(csr + HWR, ohwr | HWR_SWH);
	kprintf("\nswh = 1: ");
	for (i=8; i < 16; ++i)
		kprintf("%02x ", inb(csr + i));
	outb(csr + CMD, ocmd & 0x3f);
	kprintf("\npage 0: ");
	for (i=16; i<32; ++i)
		kprintf("%02x ", inb(csr + i));
	outb(csr + CMD, (ocmd & 0x3f) | 0x40);
	kprintf("\npage 1: ");
	for (i=16; i<32; ++i)
		kprintf("%02x ", inb(csr + i));
	outb(csr + CMD, (ocmd & 0x3f) | 0x80);
	kprintf("\npage 2: ");
	for (i=16; i<32; ++i)
		kprintf("%02x ", inb(csr + i));
	outb(csr + CMD, (ocmd & 0x3f) | 0xC0);
	kprintf("\npage 3: ");
	for (i=16; i<32; ++i)
		kprintf("%02x ", inb(csr + i));
	kprintf("\n");
	outb(csr + HWR, ohwr);
	outb(csr + CMD, ocmd);

{
	int	i;
	unsigned short *p = (unsigned short *)0xcc000;

	kprintf("mem: ");
	for (i=0; i<8; ++i, ++p) {
		kprintf("%02x ", *p & 0xff);
		kprintf("%02x ", (*p >> 8) & 0xff);
	}
	kprintf("\nmem: ");
	for (i=8; i<16; ++i, ++p) {
		kprintf("%02x ", *p & 0xff);
		kprintf("%02x ", (*p >> 8) & 0xff);
	}
	kprintf("\nmem: ");
	for (i=16; i<24; ++i, ++p) {
		kprintf("%02x ", *p & 0xff);
		kprintf("%02x ", (*p >> 8) & 0xff);
	}
	kprintf("\n");
}
}

ue_dbuf(pud)
struct utdev	*pud;
{
	int nb = pud->ud_iosize / 256;
	int	i, j;

	for (i=0; i<nb; ++i) {
		struct urb	*prb = (struct urb *)(pud->ud_iomem + i * 256);
		kprintf("bn %x rstat %x next %x len %u dat: ", i,
			prb->urb_rstat, prb->urb_next, prb->urb_len);
		for (j=0; j<64; ++j)
			kprintf("%02x ", prb->urb_data[j]);
		kprintf("\n");
	}
}

ue_check(pud)
struct utdev	*pud;
{
	int	ue_nrx = pud->ud_iosize / 256 - 6;
	struct urb	*prb;
	int	i;

	for (i=0; i<ue_nrx; ++i) {
		prb = (struct urb *)(pud->ud_iomem + i*256);
		if (prb->urb_len > 1520)
			return 0;
		if (prb->urb_rstat == 0 || prb->urb_rstat == 0x21 ||
			prb->urb_rstat == 0x1)
				continue;
		return 0;
	}
	return 1;
}

struct utdev	ue[Neth];	/* should be "Nue" */
