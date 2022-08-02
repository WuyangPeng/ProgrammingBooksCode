/* dgram.h */

/* datagram pseudo-device control block */

struct	dgblk	{			/* datagram device control block*/
	int	dg_dnum;		/* device number of this device	*/
	int	dg_state;		/* whether this device allocated*/
	IPaddr	df_lip;			/* local IP address		*/
	u_short	dg_lport;		/* local datagram port number	*/
	IPaddr	dg_fip;			/* foreign machine IP address	*/
	u_short	dg_fport;		/* foreign datagram port number	*/
	int	dg_xport;		/* incoming packet queue	*/
	int	dg_upq;			/* index of our upq entry	*/
	int	dg_mode;		/* mode of this interface	*/
};

/* datagram psuedo-device state constants */

#define	DGS_FREE	0		/* this device is available	*/
#define	DGS_INUSE	1		/* this device is in use	*/

#define	DG_TIME		30		/* read timeout (tenths of sec)	*/

/* constants for dg pseudo-device control functions */

#define	DG_SETMODE	1		/* set mode of device		*/
#define	DG_CLEAR	2		/* clear all waiting datagrams	*/

/* constants for dg pseudo-device mode bits */

#define	DG_NMODE	001		/* normal (datagram) mode	*/
#define	DG_DMODE	002		/* data-only mode		*/
#define	DG_TMODE	004		/* timeout all reads		*/
#define	DG_CMODE	010		/* generate checksums (default)	*/

/* structure of xinugram as dg interface delivers it to user */

struct	xgram	{			/* Xinu datagram (not UDP)	*/
	IPaddr	xg_fip;			/* foreign host IP address	*/
	unsigned short	xg_fport;	/* foreign UDP port number	*/
	unsigned short	xg_lport;	/* local UDP port number	*/
	u_char	xg_data[U_MAXLEN];	/* maximum data to/from UDP	*/
};

#define	XGHLEN	8	/* error in ( (sizeof(struct xgram)) - U_MAXLEN)*/

/* constants for port specifications on UDP open call */

#define	ANYFPORT	0		/* accept any foreign UDP port	*/
#define	ANYLPORT	0		/* assign a fresh local port num*/

extern	struct	dgblk	dgtab[Ndg];
extern	int	dgmutex;

int	dgalloc(void);
