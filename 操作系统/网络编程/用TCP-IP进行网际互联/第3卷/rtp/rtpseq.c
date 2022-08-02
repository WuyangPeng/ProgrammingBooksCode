/* rtpseq.c - rtpinitseq, rtpupdateseq */

#include <rtp.h>

#define RTP_MAXDROPOUT		3000
#define RTP_MAXMISORDER		100
#define RTP_SEQMOD		(1 << 16)

/*------------------------------------------------------------------------
 * rtpinitseq - init vars related to seq numbers (adapted from RFC 1889)
 *------------------------------------------------------------------------
 */
void 
rtpinitseq(seq_t seq)
{
	stm.stm_firstseq = seq;
	stm.stm_hiseq = seq;
	stm.stm_roll = 0;
	stm.stm_packets = 0;
	stm.stm_recprior = 0;
	stm.stm_expprior = 0;  
}

/*------------------------------------------------------------------------
 * rtpupdateseq - check sequence number of packet, update counters
 *                (adapted from RFC 1889)
 *------------------------------------------------------------------------
 */
int
rtpupdateseq(seq_t seq)
{
	seq_t udelta = seq - stm.stm_hiseq;

	if (stm.stm_probation) {
		if (seq == stm.stm_hiseq + 1) {
			stm.stm_probation--;
			stm.stm_hiseq = seq;
			if (stm.stm_probation == 0) {
				rtpinitseq(seq);
				return OK;
			}
		} else {
			stm.stm_probation = RTP_MINSEQUENTIAL - 1;
			stm.stm_hiseq = seq;
		}
		return ERROR;
	} 
	else if (udelta < RTP_MAXDROPOUT) {
		if (seq < stm.stm_hiseq)
			stm.stm_roll++;
		stm.stm_hiseq = seq;
	}
	else if (udelta <= RTP_SEQMOD - RTP_MAXMISORDER) {
		if (seq == stm.stm_badseq)
			rtpinitseq(seq);
	} else {
		stm.stm_badseq = (seq + 1) & (RTP_SEQMOD - 1);
		return ERROR;
	}
	return OK;
}
