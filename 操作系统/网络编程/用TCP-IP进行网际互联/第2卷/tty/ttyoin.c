/* ttyoin.c - ttyoin */

#include <conf.h>
#include <kernel.h>
#include <tty.h>

/*------------------------------------------------------------------------
 * ttyoin - handle transmit interrupt on tty
 *------------------------------------------------------------------------
 */
void
ttyoin(struct devsw *pdev)
{
	kprintf("ttyoin\n");
}
