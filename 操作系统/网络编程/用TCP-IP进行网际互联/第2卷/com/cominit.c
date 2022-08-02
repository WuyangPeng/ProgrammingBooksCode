/* cominit.c -- cominit */

#include <conf.h>
#include <kernel.h>
#include <tty.h>
#include <com.h>
#include <sem.h>

unsigned char	inb(void *);
void		outb(void *, unsigned char);
int		set_evec(unsigned, void (handler)());


/*------------------------------------------------------------------------
 *  cominit -- initialize a com device (NS16{4/5}50)
 *------------------------------------------------------------------------
 */
int
cominit(struct devsw *pdev)
{
	struct comsoft	*pcom;
	void		*csr = pdev->dvcsr;
	void		comint();

	pcom = &comtab[pdev->dvminor];
	pcom->com_pdev = pdev;
	set_evec(pdev->dvivec, comint);

	outb(csr+LCR, LCR_DLAB);
	outb(csr+DLL, 12);	/* 9600 baud */
	outb(csr+DLM, 0);	/* 9600 baud */
	outb(csr+LCR, LCR_W8); /* 8N1 */
	/* raise DTR and RTS & enable interrupts */
	outb(csr+MCR, MCR_DTR | MCR_RTS | MCR_OUT2);

	pcom->com_osema = screate(COMBUFSZ);
	outb(csr+IER, 0x0f); /* enable interrupts */
	(void) inb(csr+IIR);
	return OK;
}

struct comsoft	comtab[Nserial];

int
comdump(void *csr)
{
	int		i;
	unsigned char	lcr;

	kprintf("comdump: DLAB=0\n");
	lcr = inb(csr + LCR);
	outb(csr + LCR, lcr & ~LCR_DLAB);
	for (i=0; i<8; ++i)
		kprintf("%02x ", inb(csr + i));
	kprintf("\nDLAB=1\n");
	outb(csr + LCR, lcr | LCR_DLAB);
	kprintf("%02x %02x\n", inb(csr), inb(csr + 1));
	outb(csr + LCR, lcr);
	return OK;
}
