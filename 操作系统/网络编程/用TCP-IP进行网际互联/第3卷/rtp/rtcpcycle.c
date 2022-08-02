/* rtcpcycle.c - rtcpcycle */

#include <rtcp.h>

/*------------------------------------------------------------------------
 * rtcpcycle - generate periodic RTCP receiver reports
 *------------------------------------------------------------------------
 */
void
rtcpcycle(void)
{
	int		length = RTCP_HEADERLEN + sizeof(ssrc_t) + 
				sizeof(struct rblock);
	char		buf[length];
	struct rtcp     *prtcp = (struct rtcp *) buf;
	struct rr       *prr = (struct rr *) prtcp->rtcp_data;
	struct rblock   *prb = (struct rblock *) prr->rr_rblock;
	int		exthiseq, cumexp, cyclost, cycexp;
	struct timeval	now, delay;
	double		wait = rtcpinterval(1, 0, PCMMU_BW * RTCP_BWFRAC,
			        FALSE, 0, &sn.sn_avgrtcp, TRUE);

	while (TRUE) {
	    (void) usleep((unsigned int) (wait * 1000000));
	    (void) pthread_mutex_lock(&stm.stm_smutex);
	    if (stm.stm_packets == stm.stm_recprior) {
		    if (++stm.stm_inactive == RTP_INACTTHRESH) {
		      rtcpsendbye();
		      exit(0);
		    }
		    (void) pthread_mutex_unlock(&stm.stm_smutex);
		    wait = rtcpinterval(2, 0, PCMMU_BW * RTCP_BWFRAC,
					FALSE, 0, &sn.sn_avgrtcp, FALSE);
		    continue;
	    }
	    prr->rr_ssrc = htonl(sn.sn_ssrc);
	    exthiseq = (stm.stm_roll << 16) | stm.stm_hiseq;
	    cumexp = exthiseq - stm.stm_firstseq + 1;
	    cycexp = cumexp - stm.stm_expprior;
	    cyclost = max(cycexp - (stm.stm_packets -
	            stm.stm_recprior), 0);
	    prb->rb_ssrc = htonl(stm.stm_ssrc);
	    prb->rb_fraclost = cycexp == 0 ? 0 : (cyclost << 8) / cycexp;
	    prb->rb_cumlost = hton24(max(min(cumexp - stm.stm_packets,
	            0x7fffff), -(1 << 23)));
	    prb->rb_hiseq = htonl(exthiseq);
	    prb->rb_jitter = htonl((unsigned int) stm.stm_jitter);
	    prb->rb_lastsrts = htonl(((stm.stm_ntp[1] & 0x0000ffff) << 16)
                    | ((stm.stm_ntp[0] & 0xffff0000) >> 16));
	    (void) gettimeofday(&now, NULL);
	    timersub(&now, &stm.stm_lastsr, &delay);
	    prb->rb_delay = stm.stm_lastsr.tv_sec != 0 ? htonl(
                    tv2lin(delay, 65536)) : 0;
	    rtcpheader(prtcp, 1, RTCP_RR, length);
	    (void) sendto(sn.sn_rtcpfd, prtcp, length, 0, (struct
	           sockaddr *) &sn.sn_rtcpto, sizeof(struct sockaddr_in));
	    stm.stm_expprior = cumexp;
	    stm.stm_recprior = stm.stm_packets;
	    (void) pthread_mutex_unlock(&stm.stm_smutex);
	    wait = rtcpinterval(2, 1, PCMMU_BW * RTCP_BWFRAC, FALSE,
                    length + 28, &sn.sn_avgrtcp, FALSE);
	}
}
