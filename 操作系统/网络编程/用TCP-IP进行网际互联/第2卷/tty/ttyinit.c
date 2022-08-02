/* ttyinit.c - ttyinit */

#include <conf.h>
#include <kernel.h>
#include <tty.h>

/*------------------------------------------------------------------------
 * ttyinit - initialize tty structures
 *------------------------------------------------------------------------
 */
int
ttyinit(pdev)
struct devsw	*pdev;
{
	ttytab[pdev->dvminor].tty_state = TTYS_FREE;
}

struct tty	ttytab[Ntty];
