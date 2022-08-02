/* ethint.c - AMD 7990 Lance Ethernet chip interrupt handle  */

#include <conf.h>
#include <kernel.h>
#include <network.h>


/*------------------------------------------------------------------------
 *  ethint  --  handle ethernet interrupt
 *		We assume 1 lance ethernet chip. Consequently we
 *		don't do the demux'ing a real drive would do
 *------------------------------------------------------------------------
 */
INTPROC	ethint()
{
    STATWORD ps;
    struct	etblk	*ethblk;
    
    disable(ps);
    ethinter( &(eth[0]) );		/* assume eth[0] - kinda bogus */
    restore(ps);			/* restore status register	*/
}
