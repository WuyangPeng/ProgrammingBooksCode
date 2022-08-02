/* isbrc.c - isbrc */

#include <conf.h>
#include <kernel.h>
#include <sleep.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  isbrc  -  Is "dest" a broadcast address?
 *------------------------------------------------------------------------
 */
Bool
isbrc(IPaddr dest)
{
	int	inum;

	/* all 0's and all 1's are broadcast */

	if (dest == ip_anyaddr || dest == ip_maskall)
		return TRUE;

	/* check real broadcast address and BSD-style for net & subnet 	*/

	for (inum=0; inum < Net.nif; ++inum)
		if (dest == nif[inum].ni_brc ||
		    dest == nif[inum].ni_nbrc ||
		    dest == nif[inum].ni_subnet ||
		    dest == nif[inum].ni_net)
			return TRUE;

	return FALSE;
}
