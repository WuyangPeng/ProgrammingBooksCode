/* rtcpsendbye.c - rtcpsendbye */

#include <rtcp.h>

/*------------------------------------------------------------------------
 * rtcpsendbye - generate an RTCP bye message
 *------------------------------------------------------------------------
 */
void
rtcpsendbye(void)
{

	int		length = RTCP_HEADERLEN + sizeof(ssrc_t);
	char		buf[length];
	struct rtcp	*prtcp = (struct rtcp *) buf;

	*((ssrc_t *) prtcp->rtcp_data) = htonl(sn.sn_ssrc);
	rtcpheader(prtcp, 1, RTCP_BYE, length);
	(void) sendto(sn.sn_rtcpfd, prtcp, length, 0, (struct sockaddr *)
                &sn.sn_rtcpto, sizeof(struct sockaddr_in));
}
