/* rtpqueue.c - rtpqdequeue, rtpqinsert */

#include <rtp.h>

/*------------------------------------------------------------------------
 * rtpqdequeue - remove the oldest packet from the RTP packet queue
 *------------------------------------------------------------------------
 */
struct rtpln *
rtpqdequeue(void)
{  
	struct rtpln *p, *pln;
  
	(void) pthread_mutex_lock(&stm.stm_qmutex);
	if ((pln = stm.stm_qhead) != NULL) {
		if ((p = pln->rln_prev) != NULL) {
			stm.stm_qhead = p;
			p->rln_next = NULL;
		} else 
			stm.stm_qtail = stm.stm_qhead = NULL;
	}
	(void) pthread_mutex_unlock(&stm.stm_qmutex);
	return pln;
}

/*------------------------------------------------------------------------
 * rtpqinsert - insert a packet into the RTP packet queue
 *------------------------------------------------------------------------
 */
bool
rtpqinsert(struct rtpln *pln)
{  
	struct rtpln	*p, *q = NULL;
	bool            head = FALSE;

	(void) pthread_mutex_lock(&stm.stm_qmutex);
	for (p = stm.stm_qtail; p != NULL && p->rln_seq > pln->rln_seq;
	     q = p, p = p->rln_next);
	if (q != NULL)
		q->rln_next = pln;
	else
		stm.stm_qtail = pln;
	pln->rln_prev = q;
	if (p != NULL)
		p->rln_prev = pln;
	else
		stm.stm_qhead = pln;
	pln->rln_next = p;  
	head = pln == stm.stm_qhead;
	(void) pthread_mutex_unlock(&stm.stm_qmutex);
	return head;
}
