/* ripin.c - rip */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <proc.h>

#ifdef	RIP
/*------------------------------------------------------------------------
 *  rip  -  do the RIP route exchange protocol
 *------------------------------------------------------------------------
 */
PROCESS
rip(void)
{
	struct	xgram	ripbuf;
	struct	rip	*prip;
	int		fd, len;

	fd = open(UDP, ANYFPORT, (void *)UP_RIP);
	if (fd == SYSERR)
		panic("rip: cannot open rip port");
	riplock = screate(1);
	if (gateway)
		resume(create(ripout,RIPOSTK, RIPPRI, RIPONAM, RIPOARGC));

	while (TRUE) {
		len = read(fd, &ripbuf, sizeof(ripbuf));
		if (len == SYSERR)
			continue;
		prip = (struct rip *)ripbuf.xg_data;
		if (ripcheck(prip, len) != OK)
			continue;
		switch (prip->rip_cmd) {
		case RIP_RESPONSE:
			if (ripbuf.xg_fport == UP_RIP)
				riprecv(prip, len, ripbuf.xg_fip);
			break;
		case RIP_REQUEST:
			if (gateway || ripbuf.xg_fport != UP_RIP)
				riprepl(prip, len, ripbuf.xg_fip,
					ripbuf.xg_fport);
			break;
		default:
			break;
		}
	}
}
#endif	/* RIP */

Bool	dorip = FALSE;
int	rippid = BADPID;
int	riplock;
