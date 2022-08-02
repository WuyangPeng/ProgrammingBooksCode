/* rtpupdate.c - rtpupdate */

#include <rtp.h>

/*------------------------------------------------------------------------
 * rtpupdate - update statistics with each RTP packet received
 *------------------------------------------------------------------------
 */
int
rtpupdate(struct rtp *header)
{
	struct timeval	now, deltatv;
	int		delta, D;

	(void) pthread_mutex_lock(&stm.stm_smutex);
	if (rtpupdateseq(header->rtp_seq) == ERROR) {
		(void) pthread_mutex_unlock(&stm.stm_smutex);
		return ERROR;
	}
	(void) gettimeofday(&now, NULL);
	if (stm.stm_packets++ != 0) {
		timersub(&now, &stm.stm_lastrec, &deltatv);
		delta = tv2lin(deltatv, PCMMU_CLKRT);
		D = delta - (header->rtp_time - stm.stm_lastts);
		D = (D < 0 ? -D : D);
		stm.stm_jitter += ((double) D - stm.stm_jitter) / 16.0;
	}
	stm.stm_inactive = 0;
	stm.stm_lastts = header->rtp_time;
	stm.stm_lastrec = now;
	(void) pthread_mutex_unlock(&stm.stm_smutex);
	return OK;
}
