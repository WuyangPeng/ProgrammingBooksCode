/* nooint.c - nooint */

#include <conf.h>
#include <kernel.h>

/*------------------------------------------------------------------------
 *  nooint  -  return an error (used for "error" entries in devtab)
 *------------------------------------------------------------------------
 */
void
nooint(struct devsw *pdev)
{
	return;
}
