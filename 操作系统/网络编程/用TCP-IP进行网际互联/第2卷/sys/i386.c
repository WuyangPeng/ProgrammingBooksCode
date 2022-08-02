/* i386.c - setsegs */

#include <icu.h>
#include <i386.h>
#include <kernel.h>


#define	KCODE	1
#define	KSTACK	2
#define	KDATA	3

struct sd gdt_copy[NGD] = {
		/* 0th entry NULL */
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
		/* 1st, Kernel Code Segment */
	{ 0xffff, 0, 0, 6, 1, 1, 0, 1, 0xf, 0, 0, 1, 1, 0 },
		/* 2nd, Kernel Data Segment */
	{ 0xffff, 0, 0, 2, 0, 1, 0, 1, 0xf, 0, 0, 1, 1, 0 },
		/* 3rd, Kernel Stack Segment */
	{ 0xffff, 0, 0, 2, 0, 1, 0, 1, 0xf, 0, 0, 1, 1, 0 },
};

extern struct sd gdt[];
extern struct segtr gdtr;

#define	HOLESIZE	((1024-640)/4)

long	initsp;		/* initial SP for nulluser() */

extern	char	*maxaddr;

/*------------------------------------------------------------------------
 * setsegs - initialize the 386 processor
 *------------------------------------------------------------------------
 */
setsegs()
{
	extern int	start, etext;
	struct sd	*psd;
	unsigned int	np, npages;

	npages = sizmem();
	maxaddr = (char *)(npages * NBPG - 1);

	psd = &gdt_copy[1];	/* kernel code segment */
	np = ((int)&etext + NBPG-1) / NBPG;	/* # code pages */
	psd->sd_lolimit = np;
	psd->sd_hilimit = np >> 16;

	psd = &gdt_copy[2];	/* kernel data segment */
	psd->sd_lolimit = npages;
	psd->sd_hilimit = npages >> 16;

	psd = &gdt_copy[3];	/* kernel stack segment */
	psd->sd_lolimit = npages;
	psd->sd_hilimit = npages >> 16;

	memcpy(gdt, gdt_copy, sizeof(gdt_copy));
	initsp = npages*NBPG  - 4;
}

/*------------------------------------------------------------------------
 * init8259 - initialize the 8259A interrupt controllers
 *------------------------------------------------------------------------
 */
init8259()
{
	STATWORD	PS;

	/* Master device */
	outb(ICU1, 0x11);	/* ICW1: icw4 needed		*/
	outb(ICU1+1, 0x20);	/* ICW2: base ivec 32		*/
	outb(ICU1+1, 0x4);	/* ICW3: cascade on irq2	*/
	outb(ICU1+1, 0x1);	/* ICW4: buf. master, 808x mode */
	outb(ICU1, 0xb);	/* OCW3: set ISR on read	*/

	/* Slave device */
	outb(ICU2, 0x11);	/* ICW1: icw4 needed		*/
	outb(ICU2+1, 0x28);	/* ICW2: base ivec 40		*/
	outb(ICU2+1, 0x2);	/* ICW3: slave on irq2		*/
	outb(ICU2+1, 0xb);	/* ICW4: buf. slave, 808x mode	*/
	outb(ICU2, 0xb);	/* OCW3: set ISR on read	*/

	disable(PS);
}

pseg(psd)
struct sd	*psd;
{
	int		i;
	unsigned char	*pb = (unsigned char *)psd;
	unsigned int	base;
	unsigned int	limit;

	kprintf("pseg (%X)\n", pb);
	kprintf("hex:   %02x", (unsigned int)*pb++);
	for(i=1; i<8; ++i) {
		kprintf(" (%X)", pb);
		kprintf(" %02x", (unsigned int)*pb++);
	}
	limit = ((int)psd->sd_hilimit) << 16;
	limit |= psd->sd_lolimit;
	base = ((int)psd->sd_hibase) << 24;
	base |= ((int)psd->sd_midbase)<< 16;
	base |= psd->sd_lobase;
	
	kprintf("\nby field: base %X limit %d perm %d\n", base, limit,
		psd->sd_perm);
	kprintf("iscode %d isapp %d dpl %d present %d avl %d\n",
		psd->sd_iscode, psd->sd_isapp, psd->sd_dpl, psd->sd_present,
		psd->sd_avl);
	kprintf("mbz %d 32b %d gran %d\n", psd->sd_mbz, psd->sd_32b,
		psd->sd_gran);
}
