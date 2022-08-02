/* ue_demux.c - ue_demux */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ue.h>

/*------------------------------------------------------------------------
 * ue_demux - demultiplex an input packet from an SMC Ultra
 *------------------------------------------------------------------------
 */
int
ue_demux(pud)
struct utdev	*pud;
{
	struct ep	*pep;
	struct urb	*prb;
	int		ifnum;

	prb = (struct urb *) (pud->ud_iomem + (pud->ud_nextbuf << 8));
	ifnum = pud->ud_ifnum;
	if (ifnum < 0 || ifnum >= NIF)
		goto drop;
	if (nif[ifnum].ni_state != NIS_UP) {
		nif[ifnum].ni_idiscard++;
		goto drop;
	}
	while (prb->urb_rstat) {
		pep = (struct ep *)nbgetbuf(Net.netpool);
		if (pep == 0) {
			if (ifnum >= 0 && ifnum < NIF)
				nif[ifnum].ni_idiscard++;
			goto drop;
		}
		pud->ud_nextbuf = prb->urb_next;
		pep->ep_len = prb->urb_len - EP_CRC;	/* drop CRC */
		if (pep->ep_len < 0 || pep->ep_len > 1514) {
			ue_dbuf(pud);
			kprintf("ue_demux: len %d too large prb %X\n",
				pep->ep_len, prb);
			freebuf(pep);
			uewr(pud->ud_pdev->dvcsr, BOUND, pud->ud_nextbuf);
		} else {
			ueget(&pep->ep_eh, prb->urb_data, pep->ep_len,
				pud->ud_rmin, pud->ud_rmax);
			uewr(pud->ud_pdev->dvcsr, BOUND, pud->ud_nextbuf);
			pep->ep_type = net2hs(pep->ep_type);
			pep->ep_order = EPO_NET;
#ifdef	NETMON
			nm_in(&nif[ifnum], pep, pep->ep_len);
			if (!ethmatch(&nif[ifnum], pep->ep_dst, pep->ep_len))
				freebuf(pep);
			else
#endif	/* NETMON */
			ni_in(&nif[ifnum], pep, pep->ep_len);
		}
		/* check for more */
		prb = (struct urb *) (pud->ud_iomem + (pud->ud_nextbuf << 8));
	}
	return OK;
drop:
	if (ifnum >= 0 && ifnum < NIF)
		nif[ifnum].ni_ierrors++;
	uewr(pud->ud_pdev->dvcsr, BOUND, prb->urb_next);
	pud->ud_nextbuf = prb->urb_next;
	return SYSERR;
}

ueget(pdst, psrc, count, pmin, pmax)
unsigned char	*pdst, *psrc, *pmax, *pmin;
int		count;
{
	int	part;

	if (count < 0 || count > 1514) {
		kprintf("bogus buffer at %X, count %d invalid\n", psrc, count);
		return SYSERR;
	}
	count += EP_CRC;	/* not included in arg */
	part = pmax - psrc;
	if (part < count) {
		memcpy(pdst, psrc, part);
		/* zero each buffer's  RSTAT & len */
		(int)psrc &= ~(UE_BUFSIZE-1);
		for (; psrc < pmax; psrc += UE_BUFSIZE) {
			psrc[0] = 0;	/* rstat 	*/
			psrc[2] = 0;	/* len		*/
			psrc[3] = 0;	/* len		*/
		}
		psrc = pmin;
		pdst += part;
		count -= part;
	}
	memcpy(pdst, psrc, count-EP_CRC);
	/* zero each buffer's  RSTAT & len */
	pmax = psrc + count;
	(int)psrc &= ~(UE_BUFSIZE-1);
	for (; psrc < pmax; psrc += UE_BUFSIZE) {
		psrc[0] = 0;	/* rsstat	*/
		psrc[2] = 0;	/* len1		*/
		psrc[3] = 0;	/* len2		*/
	}
	return OK;
}
