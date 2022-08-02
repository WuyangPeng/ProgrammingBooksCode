/* netdump.c - netdump */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  netdump  -  dump the contents of Net struct and  udp demux queues
 *------------------------------------------------------------------------
 */
netdump()
{
#ifdef	notdef
	int	i;
	struct	netq	*pnq;

	kprintf("Network: buffer pool=%d, mutex=%d, next udp #=%d,",
		Net.netpool, Net.nmutex, Net.nxtprt);
	kprintf(" addr is %svalid\n", Net.mavalid?"":"in");
	kprintf("Packets: recvd=%d, tossed=%d (%d for queue overflow)\n",
		Net.npacket, Net.ndrop, Net.nover);
	for (i=0; i<NETQS; i++) {
		pnq = &Net.netqs[i];
		if (pnq->nq_valid)
		  kprintf("%2d. port=%4d, pid=%3d, xprt=%2d, size=%2d\n",
			i, pnq->nq_port, pnq->nq_pid, pnq->nq_xport,
			pcount(pnq->nq_xport) );
	}
#endif	notdef
	return(OK);
}
