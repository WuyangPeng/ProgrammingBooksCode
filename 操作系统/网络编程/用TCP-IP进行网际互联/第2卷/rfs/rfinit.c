/* rfinit.c - rfinit */

#include <conf.h>
#include <kernel.h>
#include <fserver.h>
#include <rfile.h>
#include <sem.h>

/*------------------------------------------------------------------------
 *  rfinit  --  initialize remote file pseudo devices
 *------------------------------------------------------------------------
 */
rfinit(struct devsw *pdev)
{
	struct	rfblk	*rfptr;

	pdev->dvioblk = (char *) (rfptr = &Rf.rftab[pdev->dvminor]);
	rfptr->rf_dnum = pdev->dvnum;
	rfptr->rf_name[0] = NULLCH;
	rfptr->rf_state = RFREE;
	rfptr->rf_mutex = screate(1);
	rfptr->rf_pos = 0L;
	if (pdev->dvminor == 0) {	/* done just once */
		Rf.device = RCLOSED;
		Rf.rmutex = screate(1);
	}
}

struct	rfinfo	Rf;
