/* rtcpheader.c - rtcpheader */

#include <rtcp.h>

/*------------------------------------------------------------------------
 * rtcpheader - fill in an RTCP header in network byte order
 *------------------------------------------------------------------------
 */
void
rtcpheader(struct rtcp *prtcp, int count, unsigned char type,  int length)
{
	prtcp->rtcp_ver = RTP_CURRVERS;
	prtcp->rtcp_count = count;
	prtcp->rtcp_type = type;
	prtcp->rtcp_length = htons((length / 4) - 1);
	prtcp->rtcp_pad = FALSE;
}
