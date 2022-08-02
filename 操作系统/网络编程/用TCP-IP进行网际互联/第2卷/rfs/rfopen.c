/* rfopen.c - rfopen */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  rfopen  --  open a remote file
 *------------------------------------------------------------------------
 */
int
rfopen(struct devsw *pdev, void *name0, void *mode0)
{
	char	*name = (char *)name0;
	char	*mode = (char *)mode0;
	STATWORD ps;    
	struct	rfblk	*rfptr;
	int	i;
	int	mbits;
	int	devnum;

	disable(ps);
	if (strlen(name) > RNAMLEN) {
		restore(ps);
		return SYSERR;
	}
	mbits=ckmode(mode);
	if (mbits == SYSERR) {
		restore(ps);
		return SYSERR;
	}
	i=rfalloc();
	if (i == SYSERR) {
		restore(ps);
		return SYSERR;
	}
	rfptr = &Rf.rftab[i];
	devnum = rfptr->rf_dnum;
	strcpy(rfptr->rf_name, name);
	rfptr->rf_mode = mbits;
	rfptr->rf_pos = 0L;

	/* send remote file open request */

	if (rfio(&devtab[devnum], FS_OPEN, (u_char *)"", mbits) == SYSERR ) {
		rfptr->rf_state = RFREE;
		restore(ps);
		return SYSERR;
	}
	restore(ps);
	return devnum;
}
