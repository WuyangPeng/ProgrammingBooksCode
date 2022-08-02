/* icmp.h */

/* Internet Control Message Protocol Constants and Packet Format */

/* ic_type field */
#define	ICT_ECHORP	0	/* Echo reply				*/
#define	ICT_DESTUR	3	/* Destination unreachable		*/
#define	ICT_SRCQ	4	/* Source quench			*/
#define	ICT_REDIRECT	5	/* Redirect message type		*/
#define	ICT_ECHORQ	8	/* Echo request				*/
#define	ICT_TIMEX	11	/* Time exceeded			*/
#define	ICT_PARAMP	12	/* Parameter Problem			*/
#define	ICT_TIMERQ	13	/* Timestamp request			*/
#define	ICT_TIMERP	14	/* Timestamp reply			*/
#define	ICT_INFORQ	15	/* Information request			*/
#define	ICT_INFORP	16	/* Information reply			*/
#define	ICT_MASKRQ	17	/* Mask request				*/
#define	ICT_MASKRP	18	/* Mask reply				*/

/* ic_code field */
#define	ICC_NETUR	0	/* dest unreachable, net unreachable	*/
#define	ICC_HOSTUR	1	/* dest unreachable, host unreachable	*/
#define	ICC_PROTOUR	2	/* dest unreachable, proto unreachable	*/
#define	ICC_PORTUR	3	/* dest unreachable, port unreachable	*/
#define	ICC_FNADF	4	/* dest unr, frag needed & don't frag	*/
#define	ICC_SRCRT	5	/* dest unreachable, src route failed	*/

#define	ICC_NETRD	0	/* redirect: net			*/
#define	ICC_HOSTRD	1	/* redirect: host			*/
#define	IC_TOSNRD	2	/* redirect: type of service, net	*/
#define	IC_TOSHRD	3	/* redirect: type of service, host	*/

#define	ICC_TIMEX	0	/* time exceeded, ttl			*/
#define	ICC_FTIMEX	1	/* time exceeded, frag			*/

#define	IC_HLEN		8	/* octets				*/
#define	IC_PADLEN	3	/* pad length (octets)			*/

#define	IC_RDTTL	300	/* ttl for redirect routes		*/

/* ICMP packet format (following the IP header)				*/

struct	icmp	{			/* ICMP packet			*/
	char	ic_type;		/* type of message (ICT_* above)*/
	char	ic_code;		/* code (ICC_* above)		*/
	short	ic_cksum;		/* checksum of ICMP header+data	*/

	union	{
		struct {
			int	ic1_id:16; /* echo type, a message id	*/
			int	ic1_seq:16;/* echo type, a seq. number	*/
		} ic1;
		IPaddr	ic2_gw;		/* for redirect, gateway	*/
		struct {
			char	ic3_ptr;/* pointer, for ICT_PARAMP	*/
			char	ic3_pad[IC_PADLEN];
		} ic3;
		int	ic4_mbz;	/* must be zero			*/
	} icu;
	char	ic_data[1];		/* data area of ICMP message	*/
};

/* format 1 */
#define	ic_id	icu.ic1.ic1_id
#define	ic_seq	icu.ic1.ic1_seq

/* format 2 */
#define	ic_gw	icu.ic2_gw

/* format 3 */
#define	ic_ptr	icu.ic3.ic3_ptr
#define	ic_pad	icu.ic3.ic3_pad

/* format 4 */
#define	ic_mbz	icu.ic4_mbz

int icmp(u_short, u_short, IPaddr, void *, void *);
