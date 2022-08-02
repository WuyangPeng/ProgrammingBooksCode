/* ospf.h  */

/* OSPF process info */
extern	PROCESS		ospf();
#define	OSPFSTK		4096		/* stack size for OSPF input	*/
#define	OSPFPRI		  90		/* OSPF priority		*/
#define	OSPFNAM		"ospfinp"	/* name of OSPF input process	*/
#define	OSPFARGC	   0		/* count of args to ospfinp 	*/

extern	PROCESS		ospfhello();
#define	OSPFHSTK	4096		/* stack size for OSPF hello	*/
#define	OSPFHPRI	  90		/* OSPF priority		*/
#define	OSPFHNAM	"ospfhello"	/* name of OSPF hello process	*/
#define	OSPFHARGC	   0		/* count of args to ospfhello 	*/

#define	OSPFQLEN	20		/* OSPF input port queue length	*/
#define	MAXNBR		32		/* Max # active neighbors	*/

/* Manifest OSPF Configuration Parameters */

#define	OSPF_VERSION	2		/* protocol version number	*/
#ifdef notdef
#define	HELLOINTV	10		/* Hello Interval (seconds)	*/
#endif
#define	HELLOINTV	30		/* Hello Interval (seconds)	*/
#define	DEADINTV	4*HELLOINTV	/* Router Dead Interval (secs)	*/
#ifdef notdef
#define	RXMTINTV	5		/* Retransmit Interval (secs)	*/
#endif
#define	RXMTINTV	15		/* Retransmit Interval (secs)	*/

#define	AUTHLEN		8		/* 64-bit Password		*/

typedef	int	timer_t;		/* OSPF count-down timers (secs)*/

/* Area Information */

struct ospf_ar {
	unsigned long	  ar_id;	/* Area Identifier		*/
	unsigned char	  ar_authtype;	/* Authentication Type		*/
	unsigned char	  ar_auth[AUTHLEN]; /* Password, if ARA_PASSWD	*/
	int		  ar_dbmutex;	/* Mutex for Top. Database	*/
	int		  ar_hmod;	/* Hash Table Modulus		*/
	struct ospf_db	**ar_htable;	/* LSA Hash Table		*/
	struct ospf_db	 *ar_dblhead;	/* Head of Top. Database	*/
	struct ospf_if	 *ar_if;	/* List of Interfaces This Area	*/
};

#define	ARA_NONE	0		/* No Authentication for Area	*/
#define	ARA_PASSWD	1		/* Simple-password Auth.	*/

/* Neighbor Information */

struct	ospf_nb {
	unsigned char	nb_state;	/* neighbor conversation state	*/
	unsigned long	nb_seq;		/* DD packet sequence number	*/
	unsigned long	nb_rid;		/* neighbor's router ID		*/
	unsigned char	nb_prio;	/* neighbor's router priority	*/
	IPaddr		nb_ipa;		/* neighbor's IP address	*/
	unsigned char	nb_opts;	/* options			*/
	unsigned long	nb_drid;	/* neighbor's designated router	*/
	unsigned long	nb_brid;	/* backup designated router	*/
	Bool		nb_master;	/* nonzero if we are master	*/
	timer_t		nb_lastheard;	/* seconds since last HELLO	*/
	timer_t		nb_trexmt;	/* Retransmit Timer (secs)	*/
	timer_t		nb_tlastdd;	/* Slave Last DD pkt. Timer	*/
	timer_t		nb_tlsr;	/* LSR Retransmit Timer		*/
	int		nb_lsal;	/* Link Status Adv. List	*/
	int		nb_dsl;		/* Database Summary List	*/
	int		nb_lsrl;	/* Link Status Req. List	*/
};

/* Neighbor States */

#define	NBS_DOWN	0
#define	NBS_ATTEMPT	1
#define	NBS_INIT	2
#define NBS_2WAY	3
#define	NBS_EXSTART	4
#define	NBS_EXCHNG	5
#define	NBS_LOADING	6
#define	NBS_FULL	7

/* Neighbor Options */

#define	NBO_T		0x01		/* Router Does Supports IP TOS	*/
#define	NBO_E		0x02		/* Can Use External Routes	*/

#define	NBMAXLIST	10		/* Max Retrans. Queue Lengths	*/

#include "ospf_ls.h"
#include "ospf_pkt.h"
#include "ospf_if.h"
#include "ospf_db.h"

extern struct ospf_ar	ospf_ar[];
extern struct ospf_if	ospf_if[];
extern int		ospf_iport;
extern int		ospf_lspool;
extern IPaddr		AllSPFRouters, AllDRouters;

void ospfinit(void), if_elect(unsigned);
int ospfcheck(struct ep *);
int nb_rexmt(struct ospf_if *, struct ospf_nb *);
int nb_aok(struct ospf_if *, struct ospf_nb *);
int nb_makel(struct ospf_nb *), nb_clearl(struct ospf_nb *);
int nb_mismatch(struct ospf_if *, struct ospf_nb *);
struct ospf_nb *nb_add(struct ospf_if *, struct ospf *);
struct ospf *ospfnet2h(struct ospf *);
void ospf_hin(struct ep *), ospf_ddin(struct ep *), lsr_in(struct ep *);
void lsu_in(struct ep *), lsack_in(struct ep *);
int lsr_xmt(struct ospf_if *, struct ospf_nb *);
void dd_queue(struct ospf_if *, struct ospf_nb *);
void dd_xmit(struct ospf_if *, struct ospf_nb *);
struct ep *ospfddtmpl(struct ospf_if *);
void ddi_exstart(struct ospf_if *, struct ospf_nb *, struct ep *);
int ddi_exchng(struct ospf_if *, struct ospf_nb *, struct ep *);
int ddi_full(struct ospf_if *, struct ospf_nb *, struct ep *);
