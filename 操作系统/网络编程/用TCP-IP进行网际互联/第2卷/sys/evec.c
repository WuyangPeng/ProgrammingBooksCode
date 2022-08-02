/* evec.c -- initevec, doevec */

#include <conf.h>
#include <i386.h>    
#include <kernel.h>
#include <proc.h>
#include <sem.h>
#include <mem.h>
#include <tty.h>
#include <q.h>
#include <io.h>

/*
 * The girmask is used as a mask for interrupts that don't have a
 * handler set. disable() & restore() are OR-ed with it to get the
 * mask actually used.
 */
unsigned short	girmask;

extern struct idt idt[NID];
extern struct segtr idtr;

extern short	defevec[];
extern int	userret();

initevec()
{
	int		i;
	STATWORD	ps;

	for (i=0; i<NID; ++i)
		set_evec(i, (int)defevec[i]);
	/*
	 * "girmask" masks all (bus) interrupts with the default handler.
	 * initially, all, then cleared as handlers are set via set_evec()
	 */
	girmask = 0xfffb;	/* leave bit 2 enabled for IC cascade */

	lidt();
	init8259();
}

/*------------------------------------------------------------------------
 * set_evec - set exception vector to point to an exception handler
 *------------------------------------------------------------------------
 */
int
set_evec(unsigned xnum, void *(handler)())
{
	struct	idt	*pidt;

	pidt = &idt[xnum];
	pidt->igd_loffset = (unsigned)handler;
	pidt->igd_segsel = 0x8;		/* kernel code segment */
	pidt->igd_mbz = 0;
	pidt->igd_type = IGDT_TRAPG;
	pidt->igd_dpl = 0;
	pidt->igd_present = 1;
	pidt->igd_hoffset = (unsigned)handler >> 16;
	if (xnum > 31 && xnum < 48) {
		/* enable the interrupt in the global IR mask */
		xnum -= 32;
		girmask &= ~(1<<xnum);
	}
}

char *inames[17] = {
	"divide by zero",
	"debug exception",
	"NMI interrupt",
	"breakpoint",
	"overflow",
	"bounds check failed",
	"invalid opcode",
	"coprocessor not available",
	"double fault",
	"coprocessor segment overrun",
	"invalid TSS",
	"segment not present",
	"stack fault",
	"general protection violation",
	"page fault",
	"coprocessor error",
};

static long *fp;

static int intrap;

trap(inum)
int	inum;
{
	long		*sp, *fp;
	STATWORD 	PS;

	disable(PS);
	if (intrap) {
		_stop("double trap\n");
	}
	intrap = TRUE;

	asm("movl	%ebp,_fp");
	sp = fp + 15;	/* eflags/CS/eip/ebp/regs/trap#/Xtrap/ebp */
	kprintf("Xinu trap!\n");
	if (inum < 16)
		kprintf("exception %d (%s) currpid %d (%s)\n", inum,
			inames[inum], currpid, proctab[currpid].pname);
	else
		kprintf("exception %d currpid\n", inum);
	kprintf("eflags %X ", *sp--);
	sp--;	/* skip OLD CS */
	kprintf("eip %X ", *sp);
	sp--;
	if (inum == 8 || (inum >= 10 && inum <= 14)) {
		kprintf("error code %08x (%u)\n", *sp, *sp);
		sp--;
	}
	sp--;	/* skip FP for Xint call */
	kprintf("register dump:\n");
	kprintf("eax %08X (%10u)\t", *sp, *sp);
	sp--;
	kprintf("ecx %08X (%10u)\n", *sp, *sp);
	sp--;
	kprintf("edx %08X (%10u)\t", *sp, *sp);
	sp--;
	kprintf("ebx %08X (%10u)\n", *sp, *sp);
	sp--;
	kprintf("esp %08X (%10u)\t", *sp, *sp);
	sp--;
	kprintf("ebp %08X (%10u)\n", *sp, *sp);
	fp = sp;
	sp--;
	kprintf("esi %08X (%10u)\t", *sp, *sp);
	sp--;
	kprintf("edi %08X (%10u)\n", *sp, *sp);
	sp--;
#ifdef notyet
	control(CONSOLE, TTC_SYNC, 1);
	stacktrace(currpid, CONSOLE);
#endif
{int i, j;
	kprintf("stack backtrace:\n");
	for (i=0; i<8; ++i) {
		kprintf("%X)  ", sp);
		for (j=0; j<6; ++j)
			kprintf("%08X ", *sp++);
		kprintf("\n");
	}
}
	_stop("");
}


doevec(arg)
     int arg;
{
    unsigned short sr;
    unsigned long pc;
    unsigned short vector;
    int evnum;
    char *parg;

    parg = (char *) &arg;

    sr = *((short *) parg);
    pc = *((long  *) (parg+2));
    vector = (*((short *) (parg+6))) & 0x0fff;    /* only low 12 bits */
    
    kprintf("\nXinu Trap!  ");
    kprintf("sr: 0x%x  ", sr);
    kprintf("exception: 0x%x  ", vector);
    kprintf("pc: 0x%lx\n",pc);
    kprintf("Trap definition: ");

    evnum = vector/4;
    if (evnum<32)
	switch(evnum) {
	    case  0: kprintf("RESET0, SHOULDN'T SEE THIS\n"); break;
	    case  1: kprintf("RESET1, SHOULDN'T SEE THIS\n"); break;
	    case  2: kprintf("Bus Error\n"); break;
	    case  3: kprintf("Address Error\n"); break;
	    case  4: kprintf("Illegal instruction\n"); break;
	    case  5: kprintf("Divide by 0\n"); break;
	    case  6: kprintf("CHK,CHK2 software trap\n"); break;
	    case  7: kprintf("cpTRAPcc, TRAPcc, TRAPV software trap\n"); break;
	    case  8: kprintf("Privilege Violation\n"); break;
	    case  9: kprintf("Trace\n"); break;
	    case 10: kprintf("Line 1010 Emulator, illegal instruction\n"); break;
	    case 11: kprintf("Line 1111 Emulator, illegal instruction\n"); break;

	    case 13: kprintf("Coprocessor protocol violation\n"); break;
	    case 14: kprintf("Format Error\n"); break;
	    case 15: kprintf("Uninitialized Interrupt\n"); break;

	    case 24: kprintf("Spurrious Interrupt\n"); break;
	    case 25: kprintf("Level 1 Auto Vector\n"); break;
	    case 26: kprintf("Level 2 Auto Vector\n"); break;
	    case 27: kprintf("Level 3 Auto Vector\n"); break;
	    case 28: kprintf("Level 4 Auto Vector\n"); break;
	    case 29: kprintf("Level 5 Auto Vector (clock)\n"); break;
	    case 30: kprintf("Level 6 Auto Vector (serial line)\n"); break;
	    case 31: kprintf("Level 7 Auto Vector (monitor clock)\n"); break;
	    default: kprintf("Unassigned (reserved)\n"); break;
	  }
    else if (evnum<48)
	kprintf("Trap #%d instruction trap\n",(evnum-32));
    else if (evnum<54)
	kprintf("FPCP trap\n");
    else if (evnum<59)
	kprintf("PMMU trap\n");
    else if (evnum<64)
	kprintf("Unassigned, reserved\n");
    else
	kprintf("User defined vector\n");

    kprintf("\n");
    _stop("bogus doevec call\n");
}
