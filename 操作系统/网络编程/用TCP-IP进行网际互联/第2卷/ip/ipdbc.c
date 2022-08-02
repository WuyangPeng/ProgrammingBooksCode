/* ipdbc.c - ipdbc */

#include <conf.h>
#include <kernel.h>
#include <network.h>

struct	route *rtget(IPaddr, Bool);

/*------------------------------------------------------------------------
 * ipdbc - handle IP directed broadcast copying
 *------------------------------------------------------------------------
 */
void
ipdbc(unsigned ifnum, struct ep *pep, struct route *prt)
{
	struct	ip	*pip = (struct ip *)pep->ep_data;
	struct	ep	*pep2;
	struct	route	*prt2;
	int		len;

	if (prt->rt_ifnum != NI_LOCAL)
		return;			/* not ours		*/
	if (!isbrc(pip->ip_dst))
		return;			/* not broadcast	*/

	prt2 = rtget(pip->ip_dst, RTF_LOCAL);
	if (prt2 == NULL)
		return;
	if (prt2->rt_ifnum == ifnum) {	/* not directed		*/
		rtfree(prt2);
		return;
	}

	/* directed broadcast; make a copy */

	/* len = ether header + IP packet */

	len = EP_HLEN + pip->ip_len;
	if (len > EP_MAXLEN)
		pep2 = (struct ep *)getbuf(Net.lrgpool);
	else
		pep2 = (struct ep *)getbuf(Net.netpool);
	if (pep2 == (struct ep *)SYSERR) {
		rtfree(prt2);
		return;
	}
	memcpy(pep2, pep, len);
	/* send a copy to the net */

	ipputp(prt2->rt_ifnum, pip->ip_dst, pep2);
	rtfree(prt2);

	return;		/* continue; "pep" goes locally in IP	*/
}
