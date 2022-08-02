/* util.h - tv2lin */

#include <common.h>
#define tv2lin(t, clkrt) ((t.tv_sec * clkrt) + ((int) ((double)	 \
                          t.tv_usec * .000001 * (double) clkrt)))

struct	bufpool {
	char	*bp_next;		/* pointer to next free buffer	*/
	sem_t	bp_sem;			/* counting semaphore		*/
	pthread_mutex_t bp_mutex;	/* lock for list manipulation	*/
};

void            bpinit(void);
char           *bpget(void);
void            bpfree(void *);

extern struct bufpool	bp;
