/* sem.h - isbadsem */

#ifndef	_SEM_H_
#define _SEM_H_

#ifndef	NSEM
#define	NSEM		50	/* number of semaphores, if not defined	*/
#endif

#define	SFREE	'\01'		/* this semaphore is free		*/
#define	SUSED	'\02'		/* this semaphore is used		*/

struct	sentry	{		/* semaphore table entry		*/
	char	sstate;		/* the state SFREE or SUSED		*/
	int	semcnt;		/* count for this semaphore		*/
	int	sqhead;		/* q index of head of list		*/
	int	sqtail;		/* q index of tail of list		*/
};
extern	struct	sentry	semaph[];
extern	int	nextsem;

struct sema_stat {
	int	inuse;
	int	maxuse;
	int	failures;
};

#define	isbadsem(s)	(s<0 || s>=NSEM)

SYSCALL screate(unsigned), scount(int), wait(int), signal(int);
SYSCALL sdelete(int);

#endif /* _SEM_H_ */
