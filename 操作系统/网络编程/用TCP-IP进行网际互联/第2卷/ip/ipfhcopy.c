/* ipfhcopy.c - ipfhcopy */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  ipfhcopy -  copy the hardware, IP header, and options for a fragment
 *------------------------------------------------------------------------
 */
int
ipfhcopy(struct ep *pepto, struct ep *pepfrom, unsigned offindg)
{
	struct	ip	*pipfrom = (struct ip *)pepfrom->ep_data;
	unsigned	i, maxhlen, olen, otype;
	unsigned	hlen = (IP_MINHLEN<<2);

	if (offindg == 0) {
		memcpy(pepto, pepfrom, EP_HLEN+IP_HLEN(pipfrom));
		return IP_HLEN(pipfrom);
	}
	memcpy(pepto, pepfrom, EP_HLEN+hlen);

	/* copy options */

	maxhlen = IP_HLEN(pipfrom);
	i = hlen;
	while (i < maxhlen) {
		otype = pepfrom->ep_data[i];
		olen = pepfrom->ep_data[++i];
		if (otype & IPO_COPY) {
			memcpy(&pepto->ep_data[hlen],
				&pepfrom->ep_data[i-1], olen);
			hlen += olen;
		} else if (otype == IPO_NOP || otype == IPO_EOOP) {
			pepto->ep_data[hlen++] = otype;
			olen = 1;
		}
		i += olen-1;
		
		if (otype == IPO_EOOP)
			break;
	}
	/* pad to a multiple of 4 octets */
	while (hlen % 4)
		pepto->ep_data[hlen++] = IPO_NOP;
	return hlen;
}
