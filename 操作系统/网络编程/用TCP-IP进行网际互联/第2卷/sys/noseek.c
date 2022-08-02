/* noseek.c - noseek */

#include <conf.h>
#include <kernel.h>

/*------------------------------------------------------------------------
 *  noseek  -  return an error (used for "error" entries in devtab)
 *------------------------------------------------------------------------
 */
noseek(struct devsw *pdev, long off)
{
	return SYSERR;
}
