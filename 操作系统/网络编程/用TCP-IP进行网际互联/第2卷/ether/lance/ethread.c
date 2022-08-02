/* ethread.c - ethread */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lereg.h>
#include <network.h>
#include <q.h>

/*#define DEBUG*/

/*------------------------------------------------------------------------
 *  ethread - read a single packet from the ethernet
 *------------------------------------------------------------------------
 */
ethread(devptr, ppep, len)
     struct	devsw	*devptr;
     struct	ep	**ppep;
     int	len;
{
    struct	ep	*pep;
    struct	etblk	*pet;

#ifdef DEBUG
    kprintf("ethread(): called\n");
#endif
    
    pet = (struct etblk *) devptr->dvioblk;
    
    /* wait for exclusive read access */
    wait(pet->etrsem);
    
    pet->etrpid = currpid;
    
    while ((pep = (struct ep *) deq(pet->etinq)) == (struct ep *) 0) {
	suspend(currpid);
    }
    
    pet->etrpid = BADPID;
    
    if (pep->ep_len > len) {
	len = SYSERR;
	*ppep = (struct ep *) NULL;
    } else {
	len = pep->ep_len;
	*ppep = pep;
    }
    
    signal(pet->etrsem);
    return(len);
}
