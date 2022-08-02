/* telnet.c - telnet */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/signal.h>
#include <sys/errno.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "local.h"

void	rcvurg(int);

#define	BUFSIZE		2048	/* read buffer size	*/

struct termios	oldtty;

int	connectTCP(const char *host, const char *service);
int	ttysetup(void);

/*------------------------------------------------------------------------
 * telnet - do the TELNET protocol to the given host and port
 *------------------------------------------------------------------------
 */
int
telnet(const char *host, const char *service)
{
	unsigned char	buf[BUFSIZE];
	int	s, nfds;	/* socket and # file descriptors */
	int	cc;
	int	on = 1;
	fd_set	arfds, awfds, rfds, wfds;
	FILE	*sfp;

	s = connectTCP(host, service);

	ttysetup();

	fsmbuild();	/* set up FSM's */

	(void) signal(SIGURG, rcvurg);
	(void) setsockopt(s, SOL_SOCKET, SO_OOBINLINE, (char *)&on,
			sizeof(on));

	nfds = getdtablesize();
	FD_ZERO(&arfds);
	FD_ZERO(&awfds);
	FD_SET(s, &arfds);	/* the socket			*/
	FD_SET(0, &arfds);	/* standard input		*/

	sfp = fdopen(s, "w");	/* to get buffered output	*/

	while (1) {
		memcpy(&rfds, &arfds, sizeof(rfds));
		memcpy(&wfds, &awfds, sizeof(rfds));

		if (select(nfds, &rfds, &wfds, (fd_set *)0,
				(struct timeval *)0) < 0) {
			if (errno == EINTR)
				continue;	/* just a signal	*/
			cerrexit("select: %s\n", strerror(errno));
		}
		if (FD_ISSET(s, &rfds)) {
			cc = read(s, (char *)buf, sizeof(buf));
			if (cc < 0)
				cerrexit("socket read: %s\n",
						strerror(errno));
			else if (cc == 0) {
				printf("\nconnection closed.\n");
				if (tcsetattr(0, TCSADRAIN, &oldtty) < 0)
					errexit("tcsetattr: %s\n",
						strerror(errno));
				exit(0);
			} else
				ttwrite(sfp, stdout, buf, cc);
		}
		if (FD_ISSET(0, &rfds)) {
			cc = read(0, (char *)buf, sizeof(buf));
			if (cc < 0)
				cerrexit("tty read: %s\n",
						strerror(errno));
			else if (cc == 0) {
				FD_CLR(0, &arfds);
				(void) shutdown(s, 1);
			} else
				sowrite(sfp, stdout, buf, cc);
		}
		(void) fflush(sfp);
		(void) fflush(stdout);
	}
}
