/* tfcoalesce.c - tfcoalesce */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <mem.h>

/*------------------------------------------------------------------------
 *  tfcoalesce -  join TCP fragments
 *------------------------------------------------------------------------
 */
int
tfcoalesce(struct tcb *ptcb, unsigned datalen, struct tcp *ptcp)
{
	struct tcpfrag	*tf = 0;
	int		newcount;

	ptcb->tcb_rnext += datalen;
	ptcb->tcb_rbcount += datalen;
	if (ptcb->tcb_rnext == ptcb->tcb_finseq)
		goto alldone;
	if ((ptcb->tcb_rnext - ptcb->tcb_pushseq) >= 0) {
		ptcp->tcp_code |= TCPF_PSH;
		ptcb->tcb_pushseq = 0;
	}
	if (ptcb->tcb_rsegq < 0)	/* see if this closed a hole */
		return OK;
	tf = (struct tcpfrag *)deq(ptcb->tcb_rsegq);
	if (tf == 0)
		return OK;
	while ((tf->tf_seq - ptcb->tcb_rnext) <= 0) {
		newcount = tf->tf_len - (ptcb->tcb_rnext - tf->tf_seq);
		if (newcount > 0) {
			ptcb->tcb_rnext += newcount;
			ptcb->tcb_rbcount += newcount;
		}
		if (ptcb->tcb_rnext == ptcb->tcb_finseq)
			goto alldone;
		if ((ptcb->tcb_rnext - ptcb->tcb_pushseq) >= 0) {
			ptcp->tcp_code |= TCPF_PSH;
			ptcb->tcb_pushseq = 0;
		}
		freemem(tf, sizeof(struct tcpfrag));
		tf = (struct tcpfrag *)deq(ptcb->tcb_rsegq);
		if (tf == 0) {
			freeq(ptcb->tcb_rsegq);
			ptcb->tcb_rsegq = EMPTY;
			return OK;
		}
	}
	enq(ptcb->tcb_rsegq, tf, -tf->tf_seq); /* got one too many	*/
	return OK;
alldone:
	if (tf)
		freemem(tf, sizeof(struct tcpfrag));
	while (tf = (struct tcpfrag *)deq(ptcb->tcb_rsegq))
		freemem(tf, sizeof(struct tcpfrag));
	freeq(ptcb->tcb_rsegq);
	ptcb->tcb_rsegq = EMPTY;
	ptcp->tcp_code |= TCPF_FIN;
	return OK;
}
