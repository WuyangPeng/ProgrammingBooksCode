/* ee_cntl.c - ee_cntl */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 * ee_cntl - handle Intel EtherExpress16 control() functions
 *------------------------------------------------------------------------
 */
int
ee_cntl(pdev, func, arg)
struct devsw	*pdev;
int		func;
char		*arg;
{
	struct etdev	*ped = &ee[pdev->dvminor];
	int		rv;

	switch (func) {
	case EPC_PROMON:
	case EPC_PROMOFF:
		rv = SYSERR;	/* not supported yet */
	case EPC_MADD:
		rv = ee_mcadd(ped, arg);
		break;
	case EPC_MDEL:
		rv = ee_mcdel(ped, arg);
		break;
	default:
		rv = SYSERR;
	}
	return rv;
}
