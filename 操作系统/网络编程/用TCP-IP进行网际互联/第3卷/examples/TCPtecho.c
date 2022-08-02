/* TCPtecho.c - main, TCPtecho, reader, writer, mstime */

#include <sys/types.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/socket.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int	TCPtecho(fd_set *pafds, int nfds, int ccount, int hcount);
int	reader(int fd, fd_set *pfdset);
int	writer(int fd, fd_set *pfdset);
int	errexit(const char *format, ...);
int	connectTCP(const char *host, const char *service);
long	mstime(unsigned long *);

#define	BUFSIZE		4096		/* write buffer size		*/
#define	CCOUNT		64*1024		/* default character count	*/

#define	USAGE	"usage: TCPtecho [ -c count ] host1 host2...\n"

char	*hname[NOFILE];			/* fd to host name mapping	*/
int	rc[NOFILE], wc[NOFILE];		/* read/write character counts	*/
char	buf[BUFSIZE];			/* read/write data buffer	*/


/*------------------------------------------------------------------------
 * main - concurrent TCP client for ECHO service timing
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
	int	ccount = CCOUNT;
	int	i, hcount, maxfd, fd;
	int	one = 1;
	fd_set	afds;

	hcount = 0;
	maxfd = -1;
	for (i=1; i<argc; ++i) {
		if (strcmp(argv[i], "-c") == 0) {
			if (++i < argc && (ccount = atoi(argv[i])))
				continue;
			errexit(USAGE);
		}
		/* else, a host */

		fd = connectTCP(argv[i], "echo");
		if (ioctl(fd, FIONBIO, (char *)&one))
			errexit("can't mark socket nonblocking: %s\n",
				strerror(errno));
		if (fd > maxfd)
			maxfd = fd;
		hname[fd] = argv[i];
		++hcount;
		FD_SET(fd, &afds);
	}
	TCPtecho(&afds, maxfd+1, ccount, hcount);
	exit(0);
}

/*------------------------------------------------------------------------
 * TCPtecho - time TCP ECHO requests to multiple servers
 *------------------------------------------------------------------------
 */
int
TCPtecho(fd_set *pafds, int nfds, int ccount, int hcount)
{
	fd_set	rfds, wfds;		/* read/write fd sets		*/
	fd_set	rcfds, wcfds;		/* read/write fd sets (copy)	*/
	int	fd, i;

	for (i=0; i<BUFSIZE; ++i)	/* echo data	*/
		buf[i] = 'D';
	memcpy(&rcfds, pafds, sizeof(rcfds));
	memcpy(&wcfds, pafds, sizeof(wcfds));
	for (fd=0; fd<nfds; ++fd)
		rc[fd] = wc[fd] = ccount;

	(void) mstime((unsigned long *)0);	/* set the epoch */

	while (hcount) {
		memcpy(&rfds, &rcfds, sizeof(rfds));
		memcpy(&wfds, &wcfds, sizeof(wfds));

		if (select(nfds, &rfds, &wfds, (fd_set *)0,
				(struct timeval *)0) < 0)
			errexit("select failed: %s\n", strerror(errno));
		for (fd=0; fd<nfds; ++fd) {
			if (FD_ISSET(fd, &rfds))
				if (reader(fd, &rcfds) == 0)
					hcount--;
			if (FD_ISSET(fd, &wfds))
				writer(fd, &wcfds);
		}
	}
}

/*------------------------------------------------------------------------
 * reader - handle ECHO reads
 *------------------------------------------------------------------------
 */
int
reader(int fd, fd_set *pfdset)
{
	unsigned long	now;
	int		cc;

	cc = read(fd, buf, sizeof(buf));
	if (cc < 0)
		errexit("read: %s\n", strerror(errno));
	if (cc == 0)
		errexit("read: premature end of file\n");
	rc[fd] -= cc;
	if (rc[fd])
		return 1;
	(void) mstime(&now);
	printf("%s: %lu ms\n", hname[fd], now);
	(void) close(fd);
	FD_CLR(fd, pfdset);
	return 0;
}

/*------------------------------------------------------------------------
 * writer - handle ECHO writes
 *------------------------------------------------------------------------
 */
int
writer(int fd, fd_set *pfdset)
{
	int	cc;

	cc = write(fd, buf, MIN((int)sizeof(buf), wc[fd]));
	if (cc < 0)
		errexit("read: %s\n", strerror(errno));
	wc[fd] -= cc;
	if (wc[fd] == 0) {
		(void) shutdown(fd, 1);
		FD_CLR(fd, pfdset);
	}
}

/*------------------------------------------------------------------------
 * mstime - report the number of milliseconds elapsed
 *------------------------------------------------------------------------
 */
long
mstime(unsigned long *pms)
{
	static struct timeval	epoch;
	struct timeval		now;

	if (gettimeofday(&now, (struct timezone *)0))
		errexit("gettimeofday: %s\n", strerror(errno));
	if (!pms) {
		epoch = now;
		return 0;
	}
	*pms = (now.tv_sec - epoch.tv_sec) * 1000;
	*pms += (now.tv_usec - epoch.tv_usec + 500)/ 1000;
	return *pms;
}
