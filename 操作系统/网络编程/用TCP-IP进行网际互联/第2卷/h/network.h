/* network.h */

#include <systypes.h>
#include <string.h>
#include <sem.h>
#include <mark.h>
#include <bufpool.h>
#include <q.h>
#include <io.h>

/* All includes needed for the network */

#include <lereg.h>    
#include <ether.h>
#include <ip.h>
#include <netif.h>
#include <ipreass.h>
#include <icmp.h>
#include <udp.h>
#include <tcp.h>
#include <tcpfsm.h>
#include <tcb.h>
#include <tcpstat.h>
#include <tcptimer.h>
#include <net.h>
#include <dgram.h>
#include <arp.h>
#include <fserver.h>
#include <rfile.h>
#include <domain.h>
#include <dma.h>
#include <route.h>
#ifdef	RIP
#include <rip.h>
#endif	/* RIP */
#include <daemon.h>
#include <snmpvars.h>

/* Declarations data conversion and checksum routines */

extern	unsigned short 	cksum();    /* 1s comp of 16-bit 1s comp sum*/

#if	BYTE_ORDER == LITTLE_ENDIAN
#define hs2net(x) (unsigned) ((((x)>>8) &0xff) | (((x) & 0xff)<<8))
#define	net2hs(x) hs2net(x)

#define hl2net(x)	(((((x)& 0xff)<<24) | ((x)>>24) & 0xff) | \
	(((x) & 0xff0000)>>8) | (((x) & 0xff00)<<8))
#define net2hl(x) hl2net(x)
#endif

#if	BYTE_ORDER == BIG_ENDIAN
#define hs2net(x) (x)
#define net2hs(x) (x)
#define hl2net(x) (x)
#define net2hl(x) (x)
#endif

/* network macros */
#define hi8(x)   (unsigned char)  (((long) (x) >> 16) & 0x00ff)
#define low16(x) (unsigned short) ((long) (x) & 0xffff)

#define	BYTE(x, y)	((x)[(y)]&0xff)	/* get byte "y" from ptr "x" */
