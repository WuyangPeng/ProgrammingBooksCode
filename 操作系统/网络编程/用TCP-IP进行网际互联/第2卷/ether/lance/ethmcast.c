/* ethmcast.c - ethmcast */

#include <conf.h>
#include <kernel.h>
#include <network.h>

Eaddr	template = { 0x01, 0x00, 0x5E, 0x00, 0x00, 0x00 };

/*------------------------------------------------------------------------
 *  ethmcast -  generate & set an IP multicast hardware address
 *------------------------------------------------------------------------
 */
int ethmcast(op, dev, hwa, ipa)
int		op;
int		dev;
Eaddr		hwa;
IPaddr		ipa;
{
	blkcopy(hwa, template, EP_ALEN);
	/* add in low-order 23 bits of IP multicast address */
	hwa[3] = ipa[1] & 0x7;
	hwa[4] = ipa[2];
	hwa[5] = ipa[3];

	switch (op) {
	case NI_MADD:
		return control(dev, EPC_MADD, hwa);
		break;
	case NI_MDEL:
		return control(dev, EPC_MDEL, hwa);
		break;
	}
	return OK;
}
