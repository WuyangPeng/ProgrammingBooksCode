/* ee_demux.c - ee_demux */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ee.h>

/*------------------------------------------------------------------------
 * ee_demux - demultiplex an input packet from an Intel EtherExpress
 *------------------------------------------------------------------------
 */
int
ee_demux(ped)
struct etdev	*ped;
{
	struct rbd	*prbd = ped->ed_rbd;
	struct rfd	*prfd = ped->ed_rfd;
	struct scb	*pscb = ped->ed_scb;
	struct ep	*pep, *ee_get();
	int		csr = ped->ed_pdev->dvcsr;
	int		ifnum;

	ifnum = ped->ed_ifnum;
	if (ifnum < 0 || ifnum >= NIF)
		return;
	while (prfd->rfd_status & RSTAT_C) {
		if (nif[ifnum].ni_state == NIS_UP)
			pep = ee_get(ped, prfd, prbd);
		else
			pep = 0;
		prfd->rfd_cmd = EECMD_EL;
		prfd->rfd_status = 0;
		ped->ed_rfdend->rfd_cmd &= ~EECMD_EL;
		ped->ed_rfdend = prfd;
		ped->ed_rfd = prfd =
			(struct rfd *)IO2H(ped, prfd->rfd_next);

		prbd->rbd_el = 1;
		prbd->rbd_valid = prbd->rbd_eof = 0;
		ped->ed_rbdend->rbd_el = 0;
		ped->ed_rbdend = prbd;
		ped->ed_rbd = prbd =
			(struct rbd *)IO2H(ped, prbd->rbd_next);
		/*
		 * ni_in can cause a context switch, so restart receive
		 * unit, if necessary, here.
		 */
		pscb->scb_rfaoff = H2IO(ped, ped->ed_rfd);
		if ((pscb->scb_status & STAT_RUR) == 0) {
			ee_wait(ped);
			pscb->scb_cmd = SCBCMD_RUS;
			outb(csr+CAC, 0);
			ee_wait(ped);
			ee_ack(ped, pscb->scb_status & STAT_CNA);
		}
		if (pep) {
#ifdef	NETMON
			nm_in(&nif[ifnum], pep, pep->ep_len);
			if (!ethmatch(&nif[ifnum], pep->ep_dst, pep->ep_len))
				freebuf(pep);
			else
#endif	/* NETMON */
			ni_in(&nif[ifnum], pep, pep->ep_len);
		}
		/* context switch may have changed prfd & prbd; re-set */
		prfd = ped->ed_rfd;
		prbd = ped->ed_rbd;
	}
}

struct ep *
ee_get(ped, prfd, prbd)
struct etdev	*ped;
struct rfd	*prfd;
struct rbd	*prbd;
{
	struct ep	*pep;
	int		ifnum = ped->ed_ifnum;

	if ((prfd->rfd_status & RSTAT_OK) == 0) {
		nif[ifnum].ni_idiscard++;
		return 0;
	}
	pep = (struct ep *)nbgetbuf(Net.netpool);
	if (pep == 0) {
		if (ifnum >= 0 && ifnum < NIF)
			nif[ifnum].ni_idiscard++;
		return 0;
	}
	prbd = (struct rbd *)IO2H(ped, prfd->rfd_rbd);
	if (!prbd->rbd_valid) {
		freebuf(pep);
		return 0;
	}
	pep->ep_len = prbd->rbd_count;
	if (pep->ep_len - sizeof(struct eh) > EP_DLEN) {
		kprintf("ee%d: packet too large (%d)\n",
			pep->ep_len);
		nif[ifnum].ni_idiscard++;
		freebuf(pep);
		return 0;
	}
	memcpy(&pep->ep_eh, IO2H(ped, prbd->rbd_buf), pep->ep_len);
	pep->ep_type = net2hs(pep->ep_type);
	pep->ep_order = EPO_NET;
	return pep;
}
