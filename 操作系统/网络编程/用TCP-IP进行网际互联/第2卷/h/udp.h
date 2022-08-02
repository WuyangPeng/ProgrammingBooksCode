/* udp.h */

/* User Datagram Protocol (UDP) constants and formats */

#define	U_HLEN	8		/* UDP header length in bytes		*/

/* maximum data in UDP packet	*/
#define	U_MAXLEN	(IP_MAXLEN-(IP_MINHLEN<<2)-U_HLEN)

struct	udp {				/* message format of DARPA UDP	*/
	unsigned short	u_src;		/* source UDP port number	*/
	unsigned short	u_dst;		/* destination UDP port number	*/
	unsigned short	u_len;		/* length of UDP data		*/
	unsigned short	u_cksum;	/* UDP checksum (0 => none)	*/
	char	u_data[U_MAXLEN];	/* data in UDP message		*/
};

/* UDP constants */

#define	ULPORT		2050	/* initial UDP local "port" number	*/

/* assigned UDP port numbers */

#define	UP_ECHO		7	/* echo server				*/
#define	UP_DISCARD	9	/* discard packet			*/
#define	UP_USERS	11	/* users server				*/
#define	UP_DAYTIME	13	/* day and time server			*/
#define	UP_QOTD		17	/* quote of the day server		*/
#define	UP_CHARGEN	19	/* character generator			*/
#define	UP_TIME		37	/* time server				*/
#define	UP_WHOIS	43	/* who is server (user information)	*/
#define	UP_DNAME	53	/* domain name server			*/
#define	UP_TFTP		69	/* trivial file transfer protocol server*/
#define	UP_RWHO		513	/* remote who server (ruptime)		*/
#define	UP_RIP		520	/* route information exchange (RIP)	*/

#ifndef	Ndg
#define	UPPS		1	/* number of xinu ports used to		*/
#else				/*  demultiplex udp datagrams		*/
#define	UPPS		Ndg
#endif
#define	UPPLEN		50	/* size of a demux queue		*/

/* mapping of external network UDP "port" to internal Xinu port */

struct	upq	{			/* UDP demultiplexing info	*/
	Bool		up_valid;	/* is this entry in use?	*/
	unsigned short	up_port;	/* local UDP port number	*/
	int		up_pid;		/* port for waiting reader	*/
	int		up_xport;	/* corresponding Xinu port on	*/
};					/*  which incoming pac. queued	*/

extern	struct	upq	upqs[];
extern	int	udpmutex;	/* for UDP port searching mutex		*/

int udpsend(IPaddr, u_short, u_short, struct ep *, unsigned, Bool);
unsigned short udpcksum(struct ep *, int);
void udpnet2h(struct udp *), udph2net(struct udp *);
