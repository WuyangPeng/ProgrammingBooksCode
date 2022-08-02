/* tcpdata.c - tcpdata */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpdata -  process an input segment's data section
 *------------------------------------------------------------------------
 */
int
tcpdata(struct tcb *ptcb, struct ep *pep)
{
	struct	ip	*pip = (struct ip *)pep->ep_data;
	struct	tcp	*ptcp = (struct tcp *)pip->ip_data;
	tcpseq		first, last, wlast;
	unsigned	pb;
	int		datalen, rwindow, i, pp;

	if (ptcp->tcp_code & TCPF_URG) {
		int	rup = ptcp->tcp_seq + ptcp->tcp_urgptr;
#ifdef BSDURG
		rup--;
#endif
		if (!(ptcb->tcb_flags & TCBF_RUPOK) ||
		    SEQCMP(rup, ptcb->tcb_rupseq) > 0) {
			ptcb->tcb_rupseq = rup;
			ptcb->tcb_flags |= TCBF_RUPOK;
		}
	}
	if (ptcp->tcp_code & TCPF_SYN) {
		ptcb->tcb_rnext++;
		ptcb->tcb_flags |= TCBF_NEEDOUT;
		++ptcp->tcp_seq;	/* so we start with data */
	}
	datalen = pip->ip_len - IP_HLEN(pip) - TCP_HLEN(ptcp);
	rwindow = ptcb->tcb_rbsize - ptcb->tcb_rbcount; 
	wlast = ptcb->tcb_rnext + rwindow-1;
	first = ptcp->tcp_seq;
	last = first + datalen - 1;
	if (SEQCMP(ptcb->tcb_rnext, first) > 0) {
		datalen -= ptcb->tcb_rnext - first;
		first = ptcb->tcb_rnext;
	}
	if (SEQCMP(last, wlast) > 0) {
		datalen -= last - wlast;
		ptcp->tcp_code &= ~TCPF_FIN;	/* cutting it off */
	}
	pb = ptcb->tcb_rbstart + ptcb->tcb_rbcount; /* == rnext, in buf */
	pb += first - ptcb->tcb_rnext;		/* distance in buf	*/
	pb %= ptcb->tcb_rbsize;			/* may wrap		*/
	pp = first - ptcp->tcp_seq;		/* distance in packet	*/
	for (i=0; i<datalen; ++i) {
		ptcb->tcb_rcvbuf[pb] = ptcp->tcp_data[pp++];
		if (++pb >= ptcb->tcb_rbsize)
			pb = 0;
	}
	tcpdodat(ptcb, ptcp, first, datalen);	/* deal with it		*/
	if (ptcb->tcb_flags & TCBF_NEEDOUT)
		tcpkick(ptcb);
	return OK;
}
