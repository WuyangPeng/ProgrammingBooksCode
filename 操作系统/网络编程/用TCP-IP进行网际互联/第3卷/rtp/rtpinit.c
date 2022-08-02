/* rtpinit.c - rtpinit */

#include <rtcp.h>

struct session  sn;
struct stream	stm;

/*------------------------------------------------------------------------
 * rtpinit - initialize RTP session and stream structs, join mcast group
 *------------------------------------------------------------------------
 */
void
rtpinit(unsigned int mca, int port)
{
	struct ip_mreq	mreq;
	int		reuse = TRUE;
	unsigned char	ttl = RTCP_TTL;
	pthread_t	th;

	(void) memset(&sn, 0, sizeof(struct session));
	(void) bpinit();
	sn.sn_ssrc = random();
	sn.sn_rtpfd = socket(PF_INET, SOCK_DGRAM, 0);
	sn.sn_rtcpfd = socket(PF_INET, SOCK_DGRAM, 0);
	(void) setsockopt(sn.sn_rtpfd, SOL_SOCKET, SO_REUSEADDR, &reuse,
			  sizeof(reuse));  
	(void) setsockopt(sn.sn_rtcpfd, SOL_SOCKET, SO_REUSEADDR, &reuse,
			  sizeof(reuse));
	sn.sn_rtcpto.sin_family = AF_INET;
	sn.sn_rtcpto.sin_addr.s_addr = mca;
	sn.sn_rtcpto.sin_port = htons(port);  
	(void) bind(sn.sn_rtpfd, (struct sockaddr *) &sn.sn_rtcpto,
		    sizeof(struct sockaddr_in));
	sn.sn_rtcpto.sin_port = htons(port + 1);
	(void) bind(sn.sn_rtcpfd, (struct sockaddr *) &sn.sn_rtcpto,
		    sizeof(struct sockaddr_in));
	mreq.imr_multiaddr.s_addr = mca;
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);  
	(void) setsockopt(sn.sn_rtpfd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
			  &mreq, sizeof(mreq));
	(void) setsockopt(sn.sn_rtcpfd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
			  &mreq, sizeof(mreq));  
	(void) setsockopt(sn.sn_rtcpfd, IPPROTO_IP, IP_MULTICAST_TTL,
			  &ttl, sizeof(ttl));
	stm.stm_buffering = TRUE;
	stm.stm_probation = RTP_MINSEQUENTIAL;
	(void) pthread_mutex_init(&stm.stm_qmutex, NULL);
	(void) pthread_mutex_init(&stm.stm_smutex, NULL);
	(void) pthread_mutex_init(&stm.stm_rmutex, NULL);
	(void) pthread_cond_init(&stm.stm_rcond, NULL);
	(void) pthread_create(&th, NULL, (void*(*)(void*))rtprecv, NULL);
	(void) pthread_create(&th, NULL, (void*(*)(void*))rtcprecv, NULL);
}
