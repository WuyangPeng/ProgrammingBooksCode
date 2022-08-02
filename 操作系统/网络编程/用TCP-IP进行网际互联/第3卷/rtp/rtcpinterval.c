/* rtcpinterval.c - rtcpinterval */

#include <rtcp.h>

/*------------------------------------------------------------------------
 * rtcpinterval - compute seconds until next RTCP cycle (from RFC 1889)
 *------------------------------------------------------------------------
 */
double
rtcpinterval(int members, int senders, double rtcp_bw, int we_sent,
        int packet_size, int *avg_rtcp_size, int initial)
{
	double const RTCP_MIN_TIME = 5.;
	double const RTCP_SENDER_BW_FRACTION = 0.25;
	double const RTCP_RCVR_BW_FRACTION = (1-RTCP_SENDER_BW_FRACTION);
	double const RTCP_SIZE_GAIN = (1./16.);  
	double	     t;
	double	     rtcp_min_time = RTCP_MIN_TIME;
	int	     n;

	if (initial) {
		rtcp_min_time /= 2;
		*avg_rtcp_size = 128;
	}
	n = members;
	if (senders > 0 && senders < members * RTCP_SENDER_BW_FRACTION) {
		if (we_sent) {
			rtcp_bw *= RTCP_SENDER_BW_FRACTION;
			n = senders;
		} else {
			rtcp_bw *= RTCP_RCVR_BW_FRACTION;
			n -= senders;
		}
	}
	*avg_rtcp_size += (packet_size - *avg_rtcp_size) * RTCP_SIZE_GAIN;
	t = (*avg_rtcp_size) * n / rtcp_bw;
	if (t < rtcp_min_time)
		t = rtcp_min_time;
	return t * (drand48() + 0.5);
}
