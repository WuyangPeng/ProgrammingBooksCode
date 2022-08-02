/* kbd.h */

#define	KB_DAT	((void *)0x60)		/* keyboard data register	*/
#define	KB_CSR	((void *)0x64)		/* control/status register	*/

#define	KBS_HASDAT	0x01		/* valid data in data register	*/
#define	KBS_NRDY	0x02		/* not ready for more input	*/

#define	HACKER_KB

#define	BREAK	0x80		/* break bit	*/

#define	LSHIFT	0x2a
#define	RSHIFT	0x36
#define	LMETA	0x38

/* swap caps-lock and control key placement on brain-dead keyboards */
#ifdef	HACKER_KB
#define	LCTL	0x3a
#define	CAPSL	0x1d
#else
#define	LCTL	0x1d
#define	CAPSL	0x3a
#endif

extern unsigned char	kbcode[], kbshift[], kbctl[];

/* scan state flags */
#define	INCTL		0x01	/* control key is down		*/
#define INSHIFT		0x02	/* shift key is down		*/
#define	CAPSLOCK	0x04	/* caps lock mode		*/
#define	INMETA		0x08	/* meta (alt) key is down	*/
#define	EXTENDED	0x10	/* in extended character mode	*/

#define	EXTESC		0xe0	/* extended character escape	*/

