/* ethmcast.c - ethmcast */

#include <conf.h>
#include <kernel.h>
#include <network.h>

Eaddr	multitemplate = { 0x01, 0x00, 0x5E, 0x00, 0x00, 0x00 };

/*------------------------------------------------------------------------
 *  ethmcast -  generate & set an IP multicast Ethernet address
 *------------------------------------------------------------------------
 */
int
ethmcast(int op, int dev, Eaddr hwa, IPaddr ipa)
{
	ipa = net2hl(ipa);
	memcpy(hwa, multitemplate, EP_ALEN);

	/* add in low-order 23 bits of IP multicast address */
	hwa[3] = (ipa >> 16) & 0x7f;
	hwa[4] = (ipa >> 8);
	hwa[5] = ipa;

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
