/* echod.c - echod */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <network.h>


/*------------------------------------------------------------------------
 *  echod  -  the TCP echo server
 *------------------------------------------------------------------------
 */
PROCESS
echod(void)
{
	int	fd;

	fd = open(TCP, ANYFPORT, (void *)7);
	control(fd, TCPC_LISTENQ, 10);	/* set the queue length */

	while (TRUE) {
		int	cfd;

		/* cfd is a CONNECTED TCP stream when control() returns */
		cfd = control(fd, TCPC_ACCEPT);

		if (cfd == SYSERR) {
			break;
		}

		resume(create(ECHOP, ECHOSTK, ECHOPRI, ECHOPNAM, 1, cfd));
		/* closed by child */
	}

}

/*------------------------------------------------------------------------
 *  echop  -  handle a particular TCP echo request
 *------------------------------------------------------------------------
 */
PROCESS
echop(int cfd)
{
	int	cc, wr;
	char	buf[512];

	while (TRUE) {
		cc = read(cfd, buf, sizeof(buf));
		if (cc == TCPE_URGENTMODE || cc == TCPE_NORMALMODE)
			continue;
		if (cc <= 0 || cc == SYSERR)
			break;
		wr = write(cfd, buf, cc);
		if (wr <= 0 || wr == SYSERR)
			break;
	}
	close(cfd);
}
