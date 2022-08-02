/* nocntl.c - nocntl */

#include <conf.h>
#include <kernel.h>

/*------------------------------------------------------------------------
 *  nocntl  -  return an error (used for "error" entries in devtab)
 *------------------------------------------------------------------------
 */
int
nocntl(struct devsw *pdev, int cmd, void *arg1, void *arg2)
{
	return SYSERR;
}
