/* ospf_pkt.h */

/* OSPF packet format */

struct ospf {
	unsigned char	ospf_version;	/* Version Number		*/
	unsigned char	ospf_type;	/* Packet Type			*/
	unsigned short	ospf_len;	/* Packet Length		*/
	unsigned long	ospf_rid;	/* Router Identifier		*/
	unsigned long	ospf_aid;	/* Area Identifier		*/
	unsigned short	ospf_cksum;	/* Check Sum			*/
	unsigned short	ospf_authtype;	/* Authentication Type		*/
	unsigned char	ospf_auth[AUTHLEN]; /* Authentication Field	*/
	unsigned char	ospf_data[1];
};

#define	MINHDRLEN	24		/* OSPF base header length	*/

/* OSPF Packet Types */

#define	T_HELLO		1		/* Hello packet			*/
#define	T_DATADESC	2		/* Database Description		*/
#define	T_LSREQ		3		/* Link State Request		*/
#define	T_LSUPDATE	4		/* Link State Update		*/
#define	T_LSACK		5		/* Link State Acknowledgement	*/

/* OSPF Authentication Types */

#define	AU_NONE		0		/* No Authentication		*/
#define	AU_PASSWD	1		/* Simple Password		*/

/* OSPF Hello Packet */

struct	ospf_hello {
	unsigned long	oh_netmask;	/* Network Mask			*/
	unsigned short	oh_hintv;	/* Hello Interval (seconds)	*/
	unsigned char	oh_opts;	/* Options			*/
	unsigned char	oh_prio;	/* Sender's Router Priority	*/
	unsigned long	oh_rdintv;	/* Seconds Before Declare Dead	*/
	unsigned long	oh_drid;	/* Designated Router ID		*/
	unsigned long	oh_brid;	/* Backup Designated Router ID	*/
	unsigned long	oh_neighbor[1];	/* Living Neighbors		*/
};

#define	MINHELLOLEN	(MINHDRLEN + 20)

/* OSPF Database Description Packet */

struct	ospf_dd {
	unsigned short	dd_mbz;		/* Must Be Zero			*/
	unsigned char	dd_opts;	/* Options			*/
	unsigned char	dd_control;	/* Control Bits	(DDC_* below)	*/
	unsigned long	dd_seq;		/* Sequence Number		*/
	struct ospf_lss	dd_lss[1];	/* Link State Advertisements	*/
};

#define	MINDDLEN	(MINHDRLEN + 8)

#define	DDC_INIT	0x04		/* Initial Sequence		*/
#define	DDC_MORE	0x02		/* More to follow		*/
#define	DDC_MSTR	0x01		/* This Router is Master	*/
