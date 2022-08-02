/* rfcntl.c - rfcntl */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  rfcntl  --  control the remote file server access system
 *------------------------------------------------------------------------
 */
int
rfcntl(struct devsw *pdev, int func, void *addr, void *addr2)
{
	char	junk;
	int	len;

	junk = 0L;
	switch (func) {

	case RFCLEAR:
		/* clear port associated with rfserver */
		control(Rf.device, DG_CLEAR);
		return(OK);

	/* Universal file manipulation functions */

	case FLACCESS:
		return rfmkpac(FS_ACCESS, (char *)addr, &junk,
			(u_char *)&junk, (unsigned)addr2);

	case FLREMOVE:
		return rfmkpac(FS_UNLINK, (char *)addr, &junk,
			(u_char *)"", 0);

	case FLRENAME:
		len = strlen((char *)addr2) + 1;
		return rfmkpac(FS_RENAME, (char *)addr, &junk,
			(u_char *)addr2, len);

	default:
		return SYSERR;
	}	
}
