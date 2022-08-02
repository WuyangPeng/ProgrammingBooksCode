/* rtprecv.c - rtprecv */

#include <rtcp.h>

/*------------------------------------------------------------------------
 * rtprecv - receive and process an RTP packet
 *------------------------------------------------------------------------
 */
void
rtprecv()
{
	struct rtpln	*pln; 
	struct rtp	*prtp;
	pthread_t	thrid;

	while(TRUE) {
		pln = (struct rtpln *) bpget();
		prtp = &pln->rln_rtp;
		pln->rln_len = recv(sn.sn_rtpfd, prtp, RTP_BPBUFSZ -
		        sizeof(struct rtpln), 0);
		if (pln->rln_len < RTP_MINHDRLEN || prtp->rtp_ver != 
		        RTP_CURRVERS) {
			bpfree(pln);
			continue;
		}
		prtp->rtp_seq = ntohs(prtp->rtp_seq);
		prtp->rtp_time = ntohl(prtp->rtp_time);
		prtp->rtp_ssrc = ntohl(prtp->rtp_ssrc);
		if(sn.sn_ssrc == prtp->rtp_ssrc) {
			rtcpsendbye();
			sn.sn_ssrc = random();
			bpfree(pln);
			continue;
		}
		if (!sn.sn_detected && prtp->rtp_payload == PCMMU_ID) {
			stm.stm_ssrc = prtp->rtp_ssrc;
			sn.sn_detected = TRUE;
			(void) pthread_create(&thrid, NULL,
			        (void *(*)(void *)) rtcpcycle, NULL);
		}
		if (prtp->rtp_ssrc != stm.stm_ssrc || rtpupdate(prtp) == 
		        ERROR) {
			bpfree(pln);
			continue;
		}
		pln->rln_seq = ((stm.stm_roll) << 16) | prtp->rtp_seq;
		if (rtpqinsert(pln) || stm.stm_buffering)
			rtpnewdata();
	}
}
