/* noputc.c - noputc */

#include <conf.h>
#include <kernel.h>

/*------------------------------------------------------------------------
 *  noputc  -  return an error (used for "error" entries in devtab)
 *------------------------------------------------------------------------
 */
int
noputc(struct devsw *pdev, unsigned char c)
{
	return SYSERR;
}
