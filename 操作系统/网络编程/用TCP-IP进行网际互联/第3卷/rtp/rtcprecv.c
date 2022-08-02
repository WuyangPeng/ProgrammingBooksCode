/* rtcprecv.c - rtcprecv */

#include <rtcp.h>

/*------------------------------------------------------------------------
 * rtcprecv - receive and process RTCP sender reports
 *------------------------------------------------------------------------
 */
void
rtcprecv(void)
{
	char		rtcpbuf[RTCP_MAXPACKETSZ];
	struct rtcp	*prtcp = (struct rtcp *) rtcpbuf;
	struct sr	*psr = (struct sr *) prtcp->rtcp_data;

	while(TRUE) {
		(void) recv(sn.sn_rtcpfd, prtcp, RTCP_MAXPACKETSZ, 0);
		prtcp->rtcp_length = ntohs(prtcp->rtcp_length);
		if (prtcp->rtcp_ver == RTP_CURRVERS &&
		    prtcp->rtcp_type == RTCP_SR && 
		    ntohl(psr->sr_ssrc) == stm.stm_ssrc) {
			stm.stm_inactive = 0;
			(void) gettimeofday(&stm.stm_lastsr, NULL);
			stm.stm_ntp[0] = ntohl(psr->sr_fracts);
			stm.stm_ntp[1] = ntohl(psr->sr_intts);
		}
	}
}
