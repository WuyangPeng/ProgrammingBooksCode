/* udpnxtp.c - udpnxtp */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  udpnxtp  -  return the next available UDP local "port" number
 *	N.B.: assumes udpmutex HELD
 *------------------------------------------------------------------------
 */
unsigned short udpnxtp()
{
	static	unsigned short	lastport = ULPORT;
	Bool			inuse = TRUE;
	struct	upq		*pup;
	int			i;

	while (inuse) {
		lastport++;
		if (lastport == 0)
			lastport = ULPORT;
		inuse = FALSE;
		for (i=0; !inuse && i<UPPS ; i++) {
			pup = &upqs[i];
			inuse = pup->up_valid && pup->up_port == lastport;
		}
	}
	return lastport;
}
