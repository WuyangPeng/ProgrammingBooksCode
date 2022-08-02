/* comcntl.c - comcntl */

#include <conf.h>
#include <kernel.h>

/*------------------------------------------------------------------------
 *  comcntl  -  control a serial line device by setting modes
 *------------------------------------------------------------------------
 */
int
comcntl(struct devsw *pdev, int func, void *arg1, void *arg2)
{
	return SYSERR;
}

int brtab[] = { 50, 75, 110, 134, 150, 300, 600, 1200, 1800, 2000, 2400,
	3600, 4800, 7200, 9600, 19200, 38400, 56000, -1 };

/* assuming a 1.18432 Mhz clock */
int lstab[] = {2304, 1536, 1047, 857, 768, 384, 192, 96, 64, 58, 48, 32,
	24, 16, 12, 6, 3, 2, -1 };
