/* upalloc.c - upalloc */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <network.h>
#include <ports.h>

/*------------------------------------------------------------------------
 *  upalloc  -  allocate a UDP port demultiplexing queue
 *------------------------------------------------------------------------
 */
int
upalloc(void)
{
	struct	upq	*pup;
	int		i;

	wait(udpmutex);
	for (i=0 ; i<UPPS ; i++) {
		pup = &upqs[i];
		if (!pup->up_valid) {
			pup->up_valid = TRUE;
			pup->up_port = 0;
			pup->up_pid = BADPID;
			pup->up_xport = pcreate(UPPLEN);
			signal(udpmutex);
			return i;
		}
	}
	signal(udpmutex);
	return SYSERR;
}

struct	upq	upqs[UPPS];
