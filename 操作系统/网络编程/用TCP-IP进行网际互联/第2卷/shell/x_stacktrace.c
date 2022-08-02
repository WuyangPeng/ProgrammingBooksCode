/* x_stacktrace.c - x_stacktrace */

#include <conf.h>
#include <kernel.h>
#include <proc.h>

/*------------------------------------------------------------------------
 *  x_stacktrace  -  (command stacktrace) print stacktrace for a PID
 *------------------------------------------------------------------------
 */
COMMAND	x_stacktrace(stdin, stdout, stderr, nargs, args)
int	stdin, stdout, stderr, nargs;
char	*args[];
{
	int	pid;

	if (nargs == 1)
		return stacktrace(currpid, stdout);
	else if (nargs != 2) {
		fprintf(stderr, "usage: stacktrace <pid>\n");
		return SYSERR;
	}
	pid = atoi(args[1]);
	if (pid != 0 && isbadpid(pid)) {
		fprintf(stderr, "no such process (%d)\n", pid);
		return SYSERR;
	}
	return stacktrace(pid, stdout);
}
