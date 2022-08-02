/* rip.h */

#if !defined(_RIP_H_) && defined(RIP)
#define _RIP_H_

#define	RIPHSIZE	4	/* size of the header in octets		*/
#define	RIP_VERSION	1	/* RIP version number			*/
#define	AF_INET		2	/* Address Family for IP		*/

/* RIP commands codes: */

#define	RIP_REQUEST	1	/* message requests routes		*/
#define	RIP_RESPONSE	2	/* message contains route advertisement	*/

/* one RIP route entry */

struct	riprt {
	short	rr_family;	/* 4BSD Address Family			*/
	short	rr_mbz;		/* must be zero				*/
	u_long	rr_ipa;		/* the part we use for IP		*/
	char	rr_pad[8];	/* remaining address for non-IP		*/
	int	rr_metric;	/* distance (hop count) metric		*/
};

#define	MAXRIPROUTES	25	/* MAX routes per packet		*/
#define	RIP_INFINITY	16	/* dest is unreachable			*/

#define RIPINT		300	/* interval to send (1/10 secs)		*/
#define	RIPDELTA	 50	/* stray RIPINT +/- this (1/10 secs)	*/
#define	RIPOUTMIN	 50	/* min interval between updates (1/10 s)*/

#define RIPRTTL		180	/* route ttl (secs)			*/
#define	RIPZTIME	120	/* zombie route lifetime (secs)		*/

/* RIP packet structure */
struct	rip {
	char	rip_cmd;	/* RIP command				*/
	char	rip_vers;	/* RIP_VERSION, above			*/
	short	rip_mbz;	/* must be zero				*/
	struct	riprt	rip_rts[MAXRIPROUTES];
};

/* RIP process definitions */

extern	PROCESS		rip(), ripout();/* processes to implement RIP	*/
#define	RIPISTK		49152		/* RIP process stack size	*/
#define	RIPOSTK		4096		/* RIP process stack size	*/
#define	RIPPRI		50		/* RIP process priority		*/
#define	RIPNAM		"rip"		/* RIP main process name	*/
#define	RIPONAM		"ripout"	/* RIP output process name	*/
#define	RIPARGC		0		/* Num. args for main RIP proc.	*/
#define	RIPOARGC	0		/* Num. args for RIP out. proc.	*/

#define	MAXNRIP		5		/* max # of packets per update	*/

/* Per-interface RIP send data */
struct	rq {
	Bool		rq_active;	/* TRUE => this data is active	*/
	IPaddr		rq_ip;		/* destination IP address	*/
	unsigned short	rq_port;	/* destination port number	*/
/* what we've built already:		*/
	struct	ep	*rq_pep[MAXNRIP];	/* packets to send	*/
	int		rq_len[MAXNRIP];	/* length of each	*/
/* in-progress packet information	*/
	int		rq_cur;		/* current working packet	*/
	int		rq_nrts;	/* # routes this packet		*/
	struct	rip	*rq_prip;	/* current rip data		*/
};

extern	int	riplock;		/* ripin/ripout synchronization	*/
extern	int	rippid;			/* PID for ripout() process	*/
extern	Bool	dorip;			/* TRUE => do active RIP	*/

int ripmetric(struct route *, unsigned);
int ripstart(struct rq *);
int ripcheck(struct rip *, unsigned);
int riprecv(struct rip *, unsigned, IPaddr);
int riprepl(struct rip *, unsigned, IPaddr, unsigned short);
int ripsend(IPaddr, unsigned short);
Bool ripok(struct riprt *);
int ripifset(struct rq rqinfo[], IPaddr, unsigned short);
int ripadd(struct rq rqinfo[], struct route *);
#endif /* !defined(_RIP_H_ && defined(RIP) */
