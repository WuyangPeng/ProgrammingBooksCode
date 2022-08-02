/* nowrite.c - nowrite */

#include <conf.h>
#include <kernel.h>

/*------------------------------------------------------------------------
 *  nowrite  -  return an error (used for "error" entries in devtab)
 *------------------------------------------------------------------------
 */
int
nowrite(struct devsw *pdev, unsigned char *buf, unsigned len)
{
	return SYSERR;
}
