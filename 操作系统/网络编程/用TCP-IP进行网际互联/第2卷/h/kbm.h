/* con.h */

#define	KB_DAT	0x60		/* keyboard data port		*/
#define	KB_CSR	0x64		/* keyboard CSR port		*/

/* keyboard status bits */

#define	KBS_HASDAT	0x01	/* output buffer has data		*/
#define	KBS_NRDY	0x02	/* not ready for input			*/
#define	KBS_SYSTEM	0x04	/* 0 at power-on, 1 after		*/
#define	KBS_INHIBIT	0x10	/* state of keyboard inhibit switch	*/
#define	KBS_TTO		0x20	/* transmit time-out			*/
#define	KBS_RTO		0x40	/* receive time-out			*/
#define	KBS_PARITY	0x80	/* parity error				*/

