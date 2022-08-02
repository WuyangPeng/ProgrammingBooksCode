/* playaudio.c - playaudio */

#include <rtp.h>

/*------------------------------------------------------------------------
 * playaudio - dequeue and play packets
 *------------------------------------------------------------------------
 */
void
playaudio(void)
{
	struct rtp	*prtp;
	struct rtpln	*pln;
	struct timespec	waketimets;
	struct timeval	now, deltatv, waketimetv;
	mediatime_t	mnow, readfrom, delay;
	int		audiodev, samples, offset, profile = APF_NETWORK;

	audiodev = open("/dev/audio", O_WRONLY);
	(void) ioctl(audiodev, SNDCTL_DSP_PROFILE, &profile);
	(void) pthread_mutex_lock(&stm.stm_rmutex);
	while (TRUE) {    
	    if (stm.stm_buffering || (pln = rtpqdequeue()) == NULL) {
		    (void) pthread_cond_wait(&stm.stm_rcond,
		            &stm.stm_rmutex);
		    continue;
	    }
	    prtp = &pln->rln_rtp;
	    (void) gettimeofday(&now, NULL);
	    timersub(&now, &stm.stm_clkx, &deltatv);
	    mnow = tv2lin(deltatv, PCMMU_CLKRT) + stm.stm_clky;
	    samples = pln->rln_len - rtphdrlen(prtp);
	    if (rtptsgt(mnow, prtp->rtp_time + samples - 1)) {
		    bpfree(pln);
		    continue;
	    }
	    readfrom = rtptsmax(prtp->rtp_time, mnow);
	    if (rtptsgt(readfrom, mnow + RTP_LEEWAY)) {
		    (void) rtpqinsert(pln);      
		    delay = readfrom - mnow - RTP_LEEWAY;
		    waketimetv.tv_sec = delay / PCMMU_CLKRT;
		    waketimetv.tv_usec = (int) (((delay % PCMMU_CLKRT) /
                            (double) PCMMU_CLKRT) * 1000000);
		    timeradd(&now, &waketimetv, &waketimetv);
		    TIMEVAL_TO_TIMESPEC(&waketimetv, &waketimets);
		    (void) pthread_cond_timedwait(&stm.stm_rcond,
                            &stm.stm_rmutex, &waketimets);
		    continue;
	    }
	    offset = readfrom - prtp->rtp_time;
	    if (prtp->rtp_mark)
		    (void) ioctl(audiodev, SNDCTL_DSP_SYNC);
	    (void) write(audiodev, rtpdata(prtp) + offset, samples -
                    offset);
	    bpfree(pln);
	}
}
