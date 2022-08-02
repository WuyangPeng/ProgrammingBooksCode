/* rtpnewdata.c - rtpnewdata */

#include <rtp.h>

/*------------------------------------------------------------------------
 * rtpnewdata - determine if buffering is complete and signal read cond
 *------------------------------------------------------------------------
 */
void
rtpnewdata(void)
{
	mediatime_t           begin = 0, end = 0;

	(void) pthread_mutex_lock(&stm.stm_rmutex);
	if (stm.stm_buffering) {
		(void) pthread_mutex_lock(&stm.stm_qmutex);
		if (stm.stm_qhead != NULL) {
			begin = stm.stm_qhead->rln_rtp.rtp_time;
			end = stm.stm_qtail->rln_rtp.rtp_time;
		}
		(void) pthread_mutex_unlock(&stm.stm_qmutex);
		if (end - begin >= RTP_JITTHRESH) {
			stm.stm_clky = begin;
			(void) gettimeofday(&stm.stm_clkx, NULL);
			stm.stm_buffering = FALSE;
		}
	}
	(void) pthread_cond_signal(&stm.stm_rcond);
	(void) pthread_mutex_unlock(&stm.stm_rmutex);
}
