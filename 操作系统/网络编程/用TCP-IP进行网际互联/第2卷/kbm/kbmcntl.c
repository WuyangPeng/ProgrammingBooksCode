/* kbmcntl.c - kbmcntl */

#include <conf.h>
#include <kernel.h>

/*------------------------------------------------------------------------
 *  kbmcntl  -  control a  keyboard/monitor device
 *------------------------------------------------------------------------
 */
kbmcntl(struct devsw *pdev, int func, void *arg1, void *arg2)
{
	return SYSERR;
}
