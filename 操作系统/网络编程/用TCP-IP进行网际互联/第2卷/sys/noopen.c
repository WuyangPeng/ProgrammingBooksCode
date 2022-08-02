/* noopen.c - noopen */

#include <conf.h>
#include <kernel.h>

/*------------------------------------------------------------------------
 *  noopen  -  return an error (used for "error" entries in devtab)
 *------------------------------------------------------------------------
 */
noopen(struct devsw *pdev, void *minor, void *junk)
{
	return SYSERR;
}
