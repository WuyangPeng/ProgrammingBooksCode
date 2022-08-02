/* x_sema.c - x_sema */

#include <conf.h>
#include <kernel.h>
#include <mark.h>
#include <sem.h>

extern struct sema_stat sema_stat;

/*------------------------------------------------------------------------
 *  x_sema  -  (command sema) format and print semaphore information
 *------------------------------------------------------------------------
 */
COMMAND	x_sema(stdin, stdout, stderr, nargs, args)
int	stdin, stdout, stderr, nargs;
char	*args[];
{
	char	str[80];

	sprintf(str, "failures %d maxused %4d (of %d)  inuse=%4d (%3d%%)\n",
		sema_stat.failures, sema_stat.maxuse, NSEM, sema_stat.inuse,
		(sema_stat.inuse * 100)/NSEM);
	write(stdout, str, strlen(str));
	return OK;
}
