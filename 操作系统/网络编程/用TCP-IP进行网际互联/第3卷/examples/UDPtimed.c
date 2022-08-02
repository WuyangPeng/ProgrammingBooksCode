/* UDPtimed.c - main */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>

int	passiveUDP(const char *service);
int	errexit(const char *format, ...);

#define	UNIXEPOCH	2208988800UL	/* UNIX epoch, in UCT secs	*/

/*------------------------------------------------------------------------
 * main - Iterative UDP server for TIME service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
	struct sockaddr_in fsin;	/* the from address of a client	*/
	char	*service = "time";	/* service name or port number	*/
	char	buf[1];			/* "input" buffer; any size > 0	*/
	int	sock;			/* server socket		*/
	time_t	now;			/* current time			*/
	unsigned int	alen;		/* from-address length		*/

	switch (argc) {
	case	1:
		break;
	case	2:
		service = argv[1];
		break;
	default:
		errexit("usage: UDPtimed [port]\n");
	}

	sock = passiveUDP(service);

	while (1) {
		alen = sizeof(fsin);
		if (recvfrom(sock, buf, sizeof(buf), 0,
				(struct sockaddr *)&fsin, &alen) < 0)
			errexit("recvfrom: %s\n", strerror(errno));
		(void) time(&now);
		now = htonl((unsigned long)(now + UNIXEPOCH));
		(void) sendto(sock, (char *)&now, sizeof(now), 0,
			(struct sockaddr *)&fsin, sizeof(fsin));
	}
}
