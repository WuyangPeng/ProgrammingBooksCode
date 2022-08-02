/* noiint.c - noiint */

#include <conf.h>
#include <kernel.h>

/*------------------------------------------------------------------------
 *  noiint  -  return an error (used for "error" entries in devtab)
 *------------------------------------------------------------------------
 */
void
noiint(struct devsw *pdev, unsigned char ch)
{
	return;
}
