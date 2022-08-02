/* syslog.c - syslog */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <io.h>
#include <stdarg.h>
#include <syslog.h>

#ifdef	LOGHOST
char	*loghost = LOGHOST;
#else
char	*loghost = 0;
#endif

static int	logdev = BADDEV;
static char	logbuf[LOG_MAXLEN+10]; /* mesg. + room for <#.> & null	*/

extern int	currpid;

/*------------------------------------------------------------------------
 * syslog - log messages to a remote UNIX syslogd or the console
 *------------------------------------------------------------------------
 */
int
syslog(int where, char *pname, char *fmt, ...)
{
	va_list	args;
	int	len;

	va_start(args, fmt);
	if (loghost == 0) {
		kprintf(fmt, args);
		return OK;
	}
	if (logdev == BADDEV) {
		logdev = open(UDP, LOGHOST, ANYLPORT);
		if (logdev == SYSERR)
			return SYSERR;
		control(logdev, DG_SETMODE, DG_DMODE);
	}
	sprintf(logbuf, "<%d>", where);
	len = strlen(logbuf);
	sprintf(&logbuf[len], "%s[%u]: ", pname, currpid);
	len = strlen(logbuf);
	vsprintf(&logbuf[len], fmt, args);
	len = strlen(logbuf);
	logbuf[len++] = '\n';
	logbuf[len] = '\0';
	va_end(args);
	return write(logdev, logbuf, len);
}
