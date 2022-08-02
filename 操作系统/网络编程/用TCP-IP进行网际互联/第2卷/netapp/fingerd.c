/* fingerd.c - fingerd */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <network.h>
#include <syslog.h>

int lfing(char *, int);

#define	FINGERLOG	CONSOLE
/*------------------------------------------------------------------------
 *  fingerd  -  the finger server
 *------------------------------------------------------------------------
 */
PROCESS
fingerd(void)
{
	int	fd;

	fd = open(TCP, ANYFPORT, (void *)79);
	control(fd, TCPC_LISTENQ, 5);	/* set the queue length		*/

	while (TRUE) {
		struct	tcpstat tcpstat;
		char	host[64], dot[32], user[32];
		IPaddr	from;
		int	cfd, cc, rv;

		cc = 0;
		/* cfd is a CONNECTED TCP stream when control() returns */
		cfd = control(fd, TCPC_ACCEPT);
		if (cfd == SYSERR)
			break;

		/* just handle it directly */

		memset(user, 0, sizeof(user));
		rv = read(cfd, &user[cc], sizeof(user) - cc);
		for (cc = rv; rv > 0; cc += rv) {
			if (index(user, '\n'))
				break;
			rv = read(cfd, &user[cc], sizeof(user) - cc);
		}
		if (cc < 2) {
			close(cfd);
			continue;
		}
		user[cc-2] = '\0';	/* format is "[user]\r\n"	*/

		(void) control(cfd, TCPC_STATUS, &tcpstat);
		lfing(user, cfd);
		close(cfd);
		from = tcpstat.ts_faddr;
		ip2name(from, host);
		ip2dot(dot, from);
		syslog(LOG_DAEMON|LOG_INFO, "fingerd",
			"%s (%s) -> \"%.32s\"\n", host, dot, user);
	}
}
