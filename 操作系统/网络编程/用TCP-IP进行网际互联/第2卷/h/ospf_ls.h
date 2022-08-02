/* ospf_ls.h */

/* OSPF Link State Request Packet */

struct	ospf_lsr {
	unsigned long	lsr_type;	/* Link State Type		*/
	unsigned long	lsr_lsid;	/* Link State Identifier	*/
	unsigned long	lsr_rid;	/* Advertising Router		*/
};

#define	LSRLEN		12

/* OSPF Link State Summary */

struct	ospf_lss {
	unsigned short	lss_age;	/* Time (secs) Since Originated	*/
	unsigned char	lss_opts;	/* Options Supported		*/
	unsigned char	lss_type;	/* LST_* below			*/
	unsigned long	lss_lsid;	/* Link State Identifier	*/
	unsigned long	lss_rid;	/* Advertising Router Identifier*/
	unsigned long	lss_seq;	/* Link State Adv. Sequence #	*/
	unsigned short	lss_cksum;	/* Fletcher Checksum of LSA	*/
	unsigned short	lss_len;	/* Length of Advertisement	*/
};

#define	LSSHDRLEN	20

/* Link State Advertisement Types */

#define	LST_RLINK	1		/* Router Link			*/
#define	LST_NLINK	2		/* Network Link			*/
#define	LST_SLINK	3		/* IP Network Summary Link	*/
#define	LST_BRSLINK	4		/* AS Border Router Summary	*/
#define	LST_EXTERN	5		/* AS External Link		*/

/* Link State Advertisement (min) Lengths */

#define	LSA_RLEN	(LSSHDRLEN + 4)
#define	LSA_NLEN	(LSSHDRLEN + 4)

#define	LSA_ISEQ	0x80000001

/* LSS Type of Service Entry */
struct	tosent {
	unsigned char	tos_tos;	/* IP Type of Service		*/
	unsigned char	tos_mbz;	/* Must Be Zero			*/
	unsigned short	tos_metric;	/* Metric for This TOS		*/
};

/* OSPF Link State Advertisement */

#define	MAXLSDLEN	64	/* Max LS Data Len (configurable)	*/

struct ospf_lsa {
	struct ospf_lss	lsa_lss;	/* Link State Adv. Header	*/
	char		lsa_data[MAXLSDLEN]; /* Link-Type Dependent Data*/
};

/* Convenient Field Translations */

#define	lsa_age		lsa_lss.lss_age
#define	lsa_opts	lsa_lss.lss_opts
#define	lsa_type	lsa_lss.lss_type
#define	lsa_lsid	lsa_lss.lss_lsid
#define	lsa_rid		lsa_lss.lss_rid
#define	lsa_seq		lsa_lss.lss_seq
#define	lsa_cksum	lsa_lss.lss_cksum
#define	lsa_len		lsa_lss.lss_len

/* Router Links Advertisement */

struct	ospf_ra {
	unsigned char	ra_opts;	/* RAO_* Below			*/
	unsigned char	ra_mbz;		/* Must Be Zero			*/
	unsigned short	ra_nlinks;	/* # of Links This Advertisement*/
	unsigned char	ra_data[1];	/* nlinks rlink structs		*/
};

struct ospf_rl {
	unsigned long	rl_lid;		/* Link ID			*/
	unsigned long	rl_data;	/* Link Data			*/
	unsigned char	rl_type;	/* Link Type (RAT_* Below)	*/
	unsigned char	rl_ntos;	/* # of Types-of-Service Entries*/
	unsigned short	rl_metric;	/* TOS 0 Metric			*/
	unsigned long	rl_tosent[1];	/* TOS Entries ra_ntos Times	*/
};

#define	MINRLLEN	12

#define	RAO_ABR		0x01		/* Router is Area Border Router	*/
#define	RAO_EXTERN	0x02		/* Router is AS Boundary Router	*/

#define	RAT_PT2PT	1		/* Point-Point Connection	*/
#define	RAT_TRANSIT	2		/* Connection to Transit Network*/
#define	RAT_STUB	3		/* Connection to Stub Network	*/
#define	RAT_VIRTUAL	4		/* Virtual Link			*/

/* Network Links Advertisement */

struct	ospf_na {
	IPaddr		na_mask;	/* Network Mask			*/
	unsigned long	na_rid[1];	/* IDs of All Attached Routers	*/
};

/* Link State Update Packet Format */

struct	ospf_lsu {
	unsigned long	lsu_nads;	/* # Advertisments This Packet	*/
	char		lsu_data[1];	/* 1 or more struct ospf_lsa's	*/
};

#define	MINLSULEN	(MINHDRLEN + 4)	/* Base LSU Length		*/

void lss_build(struct ospf_if *, struct ospf_nb *, struct ep *);
int lsr_xmit(struct ospf_if *, struct ospf_nb *);
void lsa_add(struct ospf_if *, struct ep *, struct ospf_db *);
struct ep *ospflstmpl(struct ospf_if *);
struct ep *lsr_add(struct ospf_if *, struct ospf_lss *, struct ep *);
int lsr_queue(struct ospf_if *, struct ospf_nb *, struct ep *);
int lsa_send(struct ospf_if *, IPaddr, struct ep *);
int lsr_check(struct ospf_nb *);
