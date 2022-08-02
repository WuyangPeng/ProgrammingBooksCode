/* kprintf.c - kprintf */

#include <conf.h>
#include <kernel.h>
#include <tty.h>
#include <stdarg.h>

int	kputc(struct devsw *, unsigned char);

/*------------------------------------------------------------------------
 *  kprintf  --  kernel printf: formatted, unbuffered output to CONSOLE
 *------------------------------------------------------------------------
 */
void
kprintf(const char *fmt, ...)
{
	va_list		args;
	STATWORD	ps;
	unsigned int	saveof;

	disable(ps);
	saveof = control(CONSOLE, TTC_GOF);
	control(CONSOLE, TTC_SYNC, 1);
	va_start(args, fmt);
        _doprnt(fmt, args, kputc, CONSOLE);
	va_end(args);
	if ((saveof & TOF_SYNC) == 0)
		control(CONSOLE, TTC_SYNC, 0);
	restore(ps);
}
