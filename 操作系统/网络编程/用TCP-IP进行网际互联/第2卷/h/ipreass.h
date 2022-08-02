/* ipreass.h */

/* Internet Protocol (IP)  reassembly support */

#define IP_FQSIZE	10	/* max number of frag queues		*/
#define IP_MAXNF	10	/* max number of frags/datagram		*/
#define	IP_FTTL		60	/* time to live (secs)			*/

/* ipf_state flags */

#define	IPFF_VALID	1	/* contents are valid			*/
#define	IPFF_BOGUS	2	/* drop frags that match		*/
#define	IPFF_FREE	3	/* this queue is free to be allocated	*/

struct	ipfq	{
	char	ipf_state;		/* VALID, FREE or BOGUS		*/
	IPaddr	ipf_src;		/* IP address of the source	*/
	short	ipf_id;			/* datagram id			*/
	int	ipf_ttl;		/* countdown to disposal	*/
	int	ipf_q;			/* the queue of fragments	*/
};

extern	int	ipfmutex;		/* mutex for ipfqt[]		*/
extern	struct	ipfq	ipfqt[];	/* IP frag queue table		*/

int ipfsend(struct netif *, IPaddr, struct ep *, unsigned, unsigned,
	unsigned);
int ipfhcopy(struct ep *, struct ep *, unsigned);
