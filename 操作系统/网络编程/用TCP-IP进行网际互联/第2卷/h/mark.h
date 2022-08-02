/* mark.h - unmarked */

#ifndef _MARK_H_
#define	_MARK_H_

#ifndef	MAXMARK
#define	MAXMARK	20		/* maximum number of marked locations	*/
#endif
#ifdef	MEMMARK
extern	int	*(marks[]);
extern	int	nmarks;
extern	int	mkmutex;
typedef	int	MARKER[1];	/* by declaring it to be an array, the	*/
				/* name provides an address so forgotten*/
				/* &'s don't become a problem		*/

#define	unmarked(L)		(L[0]<0 || L[0]>=nmarks || marks[L[0]]!=L)
#define marked(L)               !unmarked(L)

SYSCALL mark(int *);

#endif
#endif /* _MARK_H_ */
