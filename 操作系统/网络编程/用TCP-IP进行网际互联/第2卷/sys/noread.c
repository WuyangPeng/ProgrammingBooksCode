/* noread.c - noread */

#include <conf.h>
#include <kernel.h>

/*------------------------------------------------------------------------
 *  noread  -  return an error (used for "error" entries in devtab)
 *------------------------------------------------------------------------
 */
int
noread(struct devsw *pdev, char *buf, unsigned len)
{
	return SYSERR;
}
