/* route.h - RTFREE */

/* Routing Table Entries: */
struct route {
	IPaddr	rt_net;		/* network address for this route	*/
	IPaddr	rt_mask;	/* mask for this route			*/
	IPaddr	rt_gw;		/* next IP hop				*/
	u_short	rt_metric;	/* distance metric			*/
	u_short	rt_ifnum;	/* interface number			*/
	short	rt_key;		/* sort key				*/
	short	rt_ttl;		/* time to live	(seconds)		*/
	struct	route *rt_next;	/* next entry for this hash value	*/
/* stats */
	int	rt_refcnt;	/* current reference count		*/
	int	rt_usecnt;	/* total use count so far		*/
};

/* Routing Table Global Data: */
struct rtinfo {
	struct	route	*ri_default;
	int		ri_bpool;
	Bool		ri_valid;
	int		ri_mutex;
};

#define	RT_DEFAULT ip_anyaddr	/* the default net			*/
#define	RT_LOOPBACK ip_loopback	/* the loopback net			*/
#define	RT_TSIZE	512	/* these are pointers; it's cheap	*/
#define	RT_INF		999	/* no timeout for this route		*/

#define	RTM_INF		16	/* an infinite metric			*/

/* rtget()'s second argument... */

#define	RTF_REMOTE	0	/* traffic is from a remote host	*/
#define	RTF_LOCAL	1	/* traffic is locally generated		*/

#define	RT_BPSIZE	100	/* max number of routes			*/

/* RTFREE - remove a route reference (assumes ri_mutex HELD)		*/

#define	RTFREE(prt)					\
	if (--prt->rt_refcnt <= 0) {			\
		freebuf(prt);				\
	}

extern	struct	rtinfo	Route;
extern	struct	route	*rttable[];

int rtadd(IPaddr, IPaddr, IPaddr, unsigned, unsigned, unsigned);
int rtdel(IPaddr, IPaddr), rthash(IPaddr), rtfree(struct route *);
struct route *rtget(IPaddr, Bool);
void rtinit(void);
void ipredirect(struct ep *, unsigned, struct route *);
void ipdbc(unsigned, struct ep *, struct route *);
