/* ee_wstrt.c - ee_wstrt */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ee.h>

static count = 0;

/*------------------------------------------------------------------------
 * ee_wstrt - start output on an Intel EtherExpress
 *------------------------------------------------------------------------
 */
int
ee_wstrt(ped)
struct etdev	*ped;
{
	STATWORD	ps;
	struct tbd	*ptdb;
	unsigned int	csr;
	struct ep	*pep;
	int		len, isbcast;

	disable(ps);
	if (ped->ed_xpending) {
		restore(ps);
		return OK;
	}
	ped->ed_xpending++;
	pep = (struct ep *)deq(ped->ed_outq);
	switch ((int)pep) {
	case 0:
		ped->ed_xpending--;
		restore(ps);
		return OK;
	case EE_SETMULTI:
		restore(ps);
		return ee_cmd(ped, EECMD_MCSET|EECMD_I, ped->ed_mca,
			ped->ed_mcc);
	default:
		break;
	}
	isbcast = !memcmp(pep->ep_dst, ped->ed_bcast, EP_ALEN);
	len = pep->ep_len;
	/* this version supports one packet per interrupt only */

	memcpy(ped->ed_xmbuf, &pep->ep_eh, pep->ep_len);
	ptdb = ped->ed_tbd;
	ptdb->tbd_count = len;
	ptdb->tbd_eof = 1;
	freebuf(pep);
	restore(ps);
	if (isbcast)
		nif[ped->ed_ifnum].ni_onucast++;
	else
		nif[ped->ed_ifnum].ni_oucast++;
	nif[ped->ed_ifnum].ni_ooctets += len;
	return ee_cmd(ped, EECMD_TX|EECMD_I);
}
