/* nogetc.c - nogetc */

#include <conf.h>
#include <kernel.h>

/*------------------------------------------------------------------------
 *  nogetc  -  return an error (used for "error" entries in devtab)
 *------------------------------------------------------------------------
 */
int
nogetc(struct devsw *pdev)
{
	return SYSERR;
}
