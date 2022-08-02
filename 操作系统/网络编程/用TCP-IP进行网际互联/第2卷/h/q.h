/* q.h - firstid, firstkey, isempty, lastkey, nonempty */

#ifndef _Q_H_
#define _Q_H_

/* q structure declarations, constants, and inline procedures		*/

#ifndef	NQENT
#define	NQENT		NPROC + NSEM + NSEM + 4	/* for ready & sleep	*/
#endif

struct	qent	{		/* one for each process plus two for	*/
				/* each list				*/
	int	qkey;		/* key on which the queue is ordered	*/
	int	qnext;		/* pointer to next process or tail	*/
	int	qprev;		/* pointer to previous process or head	*/
	};

extern	struct	qent q[];
extern	int	nextqueue;

/* inline list manipulation procedures */

#define	isempty(list)	(q[(list)].qnext >= NPROC)
#define	nonempty(list)	(q[(list)].qnext < NPROC)
#define	firstkey(list)	(q[q[(list)].qnext].qkey)
#define lastkey(tail)	(q[q[(tail)].qprev].qkey)
#define firstid(list)	(q[(list)].qnext)

/* gpq constants */

#define	QF_WAIT		0	/* use semaphores to mutex		*/
#define	QF_NOWAIT	1	/* use disable/restore to mutex		*/

int newq(unsigned, unsigned);
int enq(int, void *, int);
void *deq(int), *headq(int);
void *seeq(int);
int freeq(int);
int lenq(int);

#endif /* _Q_H_ */
