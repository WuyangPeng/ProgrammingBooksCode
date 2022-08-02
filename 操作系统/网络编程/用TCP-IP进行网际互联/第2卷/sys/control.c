/* control.c - control */

#include <conf.h>
#include <kernel.h>
#include <io.h>
#include <stdarg.h>

/*------------------------------------------------------------------------
 *  control  -  control a device (e.g., set the mode)
 *------------------------------------------------------------------------
 */
SYSCALL
control(int descrp, int func, ...)
{
	va_list		ap;
	struct	devsw	*pdev;
	void		*arg1, *arg2;
	int		rv;

	va_start(ap, func);
	if (isbaddev(descrp) )
		return SYSERR;
	pdev = &devtab[descrp];
	arg1 = va_arg(ap, void *);
	arg2 = va_arg(ap, void *);
	rv = (*pdev->dvcntl)(pdev, func, arg1, arg2);
	va_end(ap);
	return rv;
}
