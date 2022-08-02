/* tty.h */

#define	IBLEN		256		/* input buffer size		*/
#define	OBLEN		256		/* output buffer size		*/


/* terminal special characters */
struct tchars {
	unsigned char	tc_erase;
	unsigned char	tc_intr;
	unsigned char	tc_kill;
	unsigned char	tc_lnext;
	unsigned char	tc_reprint;
	unsigned char	tc_eof;
	unsigned char	tc_stop;
	unsigned char	tc_start;
	unsigned char	tc_susp;
	unsigned char	tc_werase;
	unsigned char	tc_eol;
	unsigned char	tc_status;
};

struct tty {
	unsigned char	 tty_state;	/* TTYS_* below			*/
	struct devsw	*tty_pdev;	/* tty dev structure		*/
	struct devsw	*tty_phw;	/* hardware dev structure	*/
	struct tchars	 tty_tchars;	/* line editing characters	*/
	int		 tty_cpid;	/* controlling process		*/

	/* TTY input fields */
	int		 tty_isema;	/* 1/0 semaphore for tty input	*/
	unsigned char	 tty_iflags;	/* TIF_* below			*/
	unsigned short	 tty_istart;	/* index of first character	*/
	unsigned short	 tty_icount;	/* # characters in input buffer	*/
	unsigned char	 tty_in[IBLEN];

	/* TTY output fields */
	int		 tty_osema;	/* output buffer space semaphore*/
	unsigned char	 tty_oflags;	/* TOF_* below			*/
	unsigned short	 tty_ostart;	/* index of first character	*/
	unsigned short	 tty_ocount;	/* # characters in output buffer*/
	unsigned char	 tty_out[OBLEN];
	int		 tty_rows;
	int		 tty_cols;

	/* login information */
	int		 tty_uid;	/* user identifier		*/
	unsigned long	 tty_ltime;	/* login time			*/
	unsigned long	 tty_ctime;	/* last command time		*/
};

/* TTY states */

#define	TTYS_FREE	0
#define	TTYS_ALLOC	1

/* TTY input flags */

#define	TIF_NOBLOCK	0x0001		/* don't block on input		*/
#define	TIF_NOECHO	0x0002		/* echo input			*/
#define	TIF_RAW		0x0004
#define	TIF_CBREAK	0x0008
#define	TIF_EXCLUSIVE	0x0010
#define	TIF_EOF		0x0020		/* have seen EOF		*/

/* TTY output flags */

#define	TOF_NOBLOCK	0x0001		/* don't block on output	*/
#define	TOF_SYNC	0x0002		/* do synchronous output	*/
#define	TOF_RAW		0x0004		/* do raw output		*/

/* control() functions */

#define TTC_CPID	0x0001		/* set controlling PID		*/
#define	TTC_SYNC	0x0002		/* do synchronous output	*/
#define	TTC_GIF		0x0003		/* get input flags		*/
#define	TTC_GOF		0x0004		/* get output flags		*/
#define	TTC_NEXTC	0x0005		/* peek at next character	*/
#define	TTC_SUSER	0x0006		/* set uid for a tty		*/
#define	TTC_CUSER	0x0007		/* clear uid for a tty		*/

#define	TTC_MODER	0x0011		/* set raw input mode		*/
#define	TTC_MODEC	0x0012		/* set cooked input mode	*/
#define	TTC_MODEK	0x0013		/* set cbreak input mode	*/

#define	NOCHAR		256

extern struct tty	ttytab[];
