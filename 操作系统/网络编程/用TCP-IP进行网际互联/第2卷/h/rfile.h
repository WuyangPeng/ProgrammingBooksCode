/* rfile.h */

#ifndef _RFILE_H_
#define _RFILE_H_

#include <file.h>

/* Remote file device control block and defined constants */

/* Constants for server device control functions */

#define	RFCLEAR		1		/* Clear incoming messages	*/

/* Constants for controlling retrys for server communication */

#define	RTIMOUT		5		/* Timeout for server response	*/
#define	RMAXTRY		2		/* Number of retrys per op.	*/

/* Constants for rf pseudo-device state variable */

#define	RFREE		-1		/* This pseudo-device is unused	*/
#define	RUSED		1		/* This pseudo-device is used	*/

/* Declaration of rf pseudo-device I/O control block */

struct	rfblk	{			/* Remote file control block	*/
	int	rf_dnum;		/* File's device num in devtab	*/
	char	rf_name[RNAMLEN];	/* Name of remote file		*/
	int	rf_state;		/* State of this pseudo device	*/
	int	rf_mode;		/* FLREAD, FLWRITE or both	*/
	int	rf_mutex;		/* exclusion for this file	*/
	long	rf_pos;			/* current byte offset in file	*/
};

#ifndef	Nrf
#define	Nrf	1
#endif
struct	rfinfo	{			/* all remote server info.	*/
	int	device;			/* device descriptor for server	*/
	int	rmutex;			/* mutual exclusion for server	*/
	struct	rfblk	rftab[Nrf];	/* remote file control blocks	*/
};

extern	struct	rfinfo	Rf;

int rfmkpac(int, char *, char *, unsigned char *, unsigned);
int rfio(struct devsw *, int, unsigned char *, unsigned);
int rfsend(struct fphdr *, int, int);
int rfalloc(void);
#endif /*_RFILE_H_*/
