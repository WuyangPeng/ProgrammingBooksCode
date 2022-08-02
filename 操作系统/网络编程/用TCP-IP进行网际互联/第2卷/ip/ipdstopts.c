/* ipdstopts.c - ipdstopts */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  ipdstopts - do host handling of IP options
 *------------------------------------------------------------------------
 */
int
ipdstopts(struct netif *pni, struct ep *pep)
{
	struct	ip	*pip = (struct ip *)pep->ep_data;
	u_char		*popt, *popend;
	int		len;

	if (IP_HLEN(pip) == IPMHLEN)
		return OK;
	popt = pip->ip_data;
	popend = (u_char *)&pep->ep_data[IP_HLEN(pip)];

	/* NOTE: options not implemented yet */

	/* delete the options */
	len = pip->ip_len-IP_HLEN(pip);	/* data length	*/
	if (len)
		memcpy(pip->ip_data, &pep->ep_data[IP_HLEN(pip)], len);
	pip->ip_len = IPMHLEN + len;
	pip->ip_verlen = (pip->ip_verlen&0xf0) | IP_MINHLEN;
	return OK;
}
