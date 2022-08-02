/* noclose.c - noclose */

#include <conf.h>
#include <kernel.h>

/*------------------------------------------------------------------------
 *  noclose  -  return an error (used for "error" entries in devtab)
 *------------------------------------------------------------------------
 */
int
noclose(struct devsw *pdev)
{
	return SYSERR;
}
