/* arp.h - SHA, SPA, THA, TPA */

/* Internet Address Resolution Protocol  (see RFCs 826, 920)		*/

#define	AR_HARDWARE	1	/* Ethernet hardware type code		*/

/* Definitions of codes used in operation field of ARP packet */
	
#define	AR_REQUEST	1	/* ARP request to resolve address	*/
#define	AR_REPLY	2	/* reply to a resolve request		*/

#define	RA_REQUEST	3	/* reverse ARP request (RARP packets)	*/
#define	RA_REPLY	4	/* reply to a reverse request (RARP ")	*/

struct	arp	{
	u_short	ar_hwtype;	/* hardware type			*/
	u_short	ar_prtype;	/* protocol type			*/
	u_char	ar_hwlen;	/* hardware address length		*/
	u_char	ar_prlen;	/* protocol address length		*/
	u_short	ar_op;		/* ARP operation (see list above)	*/
	u_char	ar_addrs[1];	/* sender and target hw & proto addrs	*/
/*	char	ar_sha[???];	 - sender's physical hardware address	*/
/*	char	ar_spa[???];	 - sender's protocol address (IP addr.)	*/
/*	char	ar_tha[???];	 - target's physical hardware address	*/
/*	char	ar_tpa[???];	 - target's protocol address (IP)	*/
};

#define	SHA(p)	(&p->ar_addrs[0])
#define	SPA(p)	(&p->ar_addrs[p->ar_hwlen])
#define	THA(p)	(&p->ar_addrs[p->ar_hwlen + p->ar_prlen])
#define	TPA(p)	(&p->ar_addrs[(p->ar_hwlen*2) + p->ar_prlen])


#define	MAXHWALEN	EP_ALEN	/* Ethernet				*/
#define	MAXPRALEN	IP_ALEN	/* IP					*/

#define ARP_HLEN	8	/* ARP header length			*/

#define	ARP_TSIZE	50	/* ARP cache size			*/
#define	ARP_QSIZE	10	/* ARP port queue size			*/

/* cache timeouts */

#define ARP_TIMEOUT	600		/* 10 minutes			*/
#define	ARP_INF		0x7fffffff	/* "infinite" timeout value	*/
#define	ARP_RESEND	1	/* resend if no reply in 1 sec		*/
#define	ARP_MAXRETRY	4	/* give up after ~30 seconds		*/

struct	arpentry {		/* format of entry in ARP cache		*/
	short	ae_state;	/* state of this entry (see below)	*/
	short	ae_hwtype;	/* hardware type			*/
	short	ae_prtype;	/* protocol type			*/
	char	ae_hwlen;	/* hardware address length		*/
	char	ae_prlen;	/* protocol address length		*/
	struct netif *ae_pni;	/* pointer to interface structure	*/
	int	ae_queue;	/* queue of packets for this address	*/
	int	ae_attempts;	/* number of retries so far		*/
	int	ae_ttl;		/* time to live				*/
	u_char	ae_hwa[MAXHWALEN];	/* Hardware address 		*/
	u_char	ae_pra[MAXPRALEN];	/* Protocol address 		*/
};

#define	AS_FREE		0	/* Entry is unused (initial value)	*/
#define	AS_PENDING	1	/* Entry is used but incomplete		*/
#define	AS_RESOLVED	2	/* Entry has been resolved		*/

/* RARP variables */

extern int	rarppid;	/* id of process waiting for RARP reply	*/
extern int	rarpsem;	/* semaphore for access to RARP service	*/

/* ARP variables */

extern struct	arpentry	arptable[ARP_TSIZE];

/* ARP function declarations */

int		 arp_in(struct netif *, struct ep *);
struct arpentry *arpfind(u_char *, u_short, struct netif *);
struct arpentry *arpadd(struct netif *, struct arp *);
