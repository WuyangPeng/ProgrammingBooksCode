/* ospf_if.h */

/* OSPF Interface Information */

struct ospf_if {
	unsigned int	 if_type;	/* one of IFT_* below		*/
	unsigned char	 if_state;	/* one of IFS_* below		*/
	unsigned char	 if_event;	/* one of IFE_* below		*/
	unsigned int	 if_hintv;	/* Hello Packet Interval	*/
	unsigned int	 if_rdintv;	/* Router Dead Interval		*/
	unsigned int	 if_rintv;	/* Retransmit Interval		*/
	timer_t		 if_twait;	/* Wait Timer for WAITING state	*/
	unsigned int	 if_xdelay;	/* Estimated Transmission Delay	*/
	IPaddr		 if_dipa;	/* IP Address of desig. router	*/
	IPaddr		 if_bipa;	/* IP address of backup router	*/
	unsigned int	 if_metric;	/* Cost to use this Interface	*/
	unsigned char	 if_auth[AUTHLEN]; /* Authentication Key	*/
	int		 if_nbmutex;	/* Mut. Excl. Semaphor for nbtab*/
	struct ospf_ar	*if_area;	/* Area Structure Back-pointer	*/
	struct ospf_if	*if_next;	/* Next Interface for Area	*/
	struct ospf_nb	 if_nbtab[MAXNBR+1]; /* Neighbor list this net	*/
};

#define	if_rid		if_nbtab[0].nb_rid
#define	if_prio		if_nbtab[0].nb_prio
#define	if_drid		if_nbtab[0].nb_drid
#define	if_brid		if_nbtab[0].nb_brid
#define	if_opts		if_nbtab[0].nb_opts

/* Interface Types */

#define	IFT_BROADCAST	0		/* Interface Supports Broadcast	*/
#define	IFT_MULTI	1		/* Interface Supports Multicast	*/
#define	IFT_PT2PT	2		/* Interface is Point-to-point	*/
#define	IFT_VIRTUAL	3		/* Interface is a Virtual Link	*/

/* Interface States */

#define	IFS_DOWN	0		/* Interface non-functional	*/
#define	IFS_LOOPBACK	1		/* Interface in loopback mode	*/
#define	IFS_WAITING	2		/* Electing Backup Desig. Rtr.	*/
#define	IFS_PT2PT	3		/* Interface is Point-to-Point	*/
#define	IFS_DROTHER	4		/* not Designated Router	*/
#define	IFS_BACKUP	5		/* Is Backup Designated Router	*/
#define	IFS_DR		6		/* Is Designated Router		*/

/* Scheduled Interface Events */

#define	IFE_BSEEN	0x01		/* Have Seen Backup DR Claim	*/
#define	IFE_NCHNG	0x02		/* A Neighbor State Changed	*/
