/* snfreebl.c - snfreebl */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <mem.h>

#ifdef	SNMP

#include <snmp.h>

/*------------------------------------------------------------------------
 * snfreebl - free memory used for ASN.1 strings and snbentry nodes
 *------------------------------------------------------------------------
 */
void
snfreebl(struct snbentry **bl)
{
	register struct snbentry	*pbl;
	register struct snbentry	*pbl_next;

	if (*bl == (void *)NULLPTR)
		return;
	for (pbl = *bl, pbl_next = pbl->sb_next; pbl_next;
	     pbl = pbl_next, pbl_next = pbl->sb_next) {
                if (pbl->sb_a1dynstr) {
		    freemem(pbl->sb_a1str, pbl->sb_a1slen);
		}
		freemem(pbl, sizeof(struct snbentry));
	}
	if (pbl->sb_a1dynstr) {
	    freemem(pbl->sb_a1str, pbl->sb_a1slen);
	}
	freemem(pbl, sizeof(struct snbentry));

        /* erase the list head */ 
        *bl = (struct snbentry *)NULLPTR; 
}
#endif	/* SNMP */
