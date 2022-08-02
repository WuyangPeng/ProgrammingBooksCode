/* stacktrace.c - stacktrace */

#include <conf.h>
#include <kernel.h>
#include <stdarg.h>
#include <proc.h>

static unsigned long	*esp;
static unsigned long	*ebp;

int kputc(struct devsw *, unsigned char);
static lcount;

#ifdef notdef
int
mprintf(int fd, char *fmt, ...)
{
	va_list	ap;
	char	c;
	int	i;

	va_start(ap, fmt);
	if ((lcount++ % 20) == 0) {
		kprintf("<<more>>\n");
		getc(CONSOLE); 
/*		for (i=0; i<500000; ++i) */
			;
	}
	_doprnt(fmt, ap, kputc, CONSOLE);
	va_end(ap);
	return 0;
}
#endif

/*------------------------------------------------------------------------
 * stacktrace - print a stack backtrace for a process
 *------------------------------------------------------------------------
 */
int
stacktrace(int pid, unsigned fd)
{
	struct pentry	*proc = &proctab[pid];
	unsigned long	*sp, *fp;
	int		dc;

	if (pid != 0 && isbadpid(pid))
		return SYSERR;
	if (pid == currpid) {
		asm("movl %esp,_esp");
		asm("movl %ebp,_ebp");
		sp = esp;
		fp = ebp;
	} else {
		sp = (unsigned long *)proc->pesp;
		fp = sp + 2; 		/* where ctxsw leaves it */
	}
	kprintf("currpid %d lastpid %d ", currpid, lastpid);
	kprintf("sp %X fp %X base %X\n", sp, fp, proc->pbase);

	dc = 0;
	for ( ; sp < proc->pbase; ++sp) {
		if ((dc++ % 7) % 0) {
			kprintf("\n%08X: ", sp);
		}
		kprintf("%08X ", *sp);
	}
	kprintf("\n");
	if (sp > proc->pbase) 
		kprintf("sp > procbase; no stack trace possible\n");
	while (sp < (unsigned long *)proc->pbase) {
		for (; sp < fp; sp++) {
			if (sp >= proc->pbase)
				break;
			kprintf("DATA (%08X) %08X (%d)\n", sp, *sp, *sp);
		}
		if (*sp == MAGIC)
			break;
		if (sp > proc->pbase)
			break;
		kprintf("\nFP   (%08X) %08X (%d)\n", sp, *sp, *sp);
		fp = (unsigned long *) *sp++;
		if (fp <= sp) {
			kprintf("bad stack, fp (%08X) <= sp (%08X)\n",
				fp, sp);
			return SYSERR;
		}
		if (fp > proc->pbase) {
			kprintf("bad fp (%08X) > pbase (%08X)\n",
				fp, proc->pbase);
			return SYSERR;
		}
		kprintf("RET  0x%X\n", *sp);
		sp++;
	}
	kprintf("MAGIC (should be %X): %X\n", MAGIC, *sp);
	if (sp != (unsigned long *)proc->pbase) {
		kprintf("unexpected short stack\n");
		return SYSERR;
	}
	return OK;
}

