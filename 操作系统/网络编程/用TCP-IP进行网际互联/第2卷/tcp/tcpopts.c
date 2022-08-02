/* tcpopts.c - tcpopts */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  tcpopts - handle TCP options for an inbound segment
 *------------------------------------------------------------------------
 */
int
tcpopts(struct tcb *ptcb, struct ep *pep)
{
	struct	ip	*pip = (struct ip *)pep->ep_data;
	struct	tcp	*ptcp = (struct tcp *)pip->ip_data;
	u_char		*popt, *popend;
	int		len;

	if (TCP_HLEN(ptcp) == TCPMHLEN)
		return OK;
	popt = ptcp->tcp_data;
	popend = &pip->ip_data[TCP_HLEN(ptcp)];
	do {
		switch (*popt) {
		case TPO_NOOP:	popt++;
				/* fall through */
		case TPO_EOOL:	break;
		case TPO_MSS:
			popt += tcpsmss(ptcb, ptcp, popt);
			break;
		default:
			popt++;	/* skip option code */
			if (*popt > 0 && *popt <= popend - popt - 1)
				popt += *popt - 1;
			else
				popt = popend;	/* bogus option length */
			break;
		}
	} while (*popt != TPO_EOOL && popt<popend);

	/* delete the options */
	len = pip->ip_len-IP_HLEN(pip)-TCP_HLEN(ptcp);
	if (len)
		memcpy(ptcp->tcp_data,&pip->ip_data[TCP_HLEN(ptcp)],len);
	pip->ip_len = IP_HLEN(pip) + TCPMHLEN + len;
	ptcp->tcp_offset = TCPHOFFSET;
	return OK;
}
