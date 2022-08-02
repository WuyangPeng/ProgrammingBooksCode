/*------------------------------------------------------------------------
 *	panic  --  panic and abort XINU
 *------------------------------------------------------------------------
 */

#include <conf.h>
#include <kernel.h>    
#include <proc.h>
#include <tty.h>
#include <stdarg.h>

static unsigned long	esp, ebp;

void
panic(const char *msg, ...)
{
	va_list ap;
	STATWORD ps;    

	disable(ps);
	kprintf("currpid %d (%s)\n", currpid, proctab[currpid].pname);
	kprintf("Panic:");
	kprintf(msg, &ap);
	va_end(ap);
	control(CONSOLE, TTC_SYNC, 1);
	stacktrace(currpid, CONSOLE);
	_stop("(panic)\n");
	restore(ps);
}

