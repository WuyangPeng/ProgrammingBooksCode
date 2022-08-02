/* ethdemux.c - ethdemux */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  ethdemux - select a port to send an incoming packet (ETHER or OTHER?)
 *------------------------------------------------------------------------
 */
int ethdemux(etptr, bn)
struct	etblk	*etptr;
int		bn;
{
	struct	bre	*pbre;
	struct	le_md	*pmd;
	struct	otblk	*otptr;
	struct	ep	*pep;
	int		noth, readlen, errs, ifnum;
	char		*dest;

	ifnum = etptr->etintf;
	pbre = &etptr->etbrr[bn];
	pmd = pbre->pmd;
	errs = pmd->lmd_flags & (RMD_FRAM|RMD_OFLO|RMD_CRC|RMD_BUFF);
	if ( errs != 0) {
		if (errs & RMD_FRAM)
			kprintf("ethread: framing error\n");
		if (errs & RMD_OFLO)
			kprintf("ethread: buffer overflow\n");
		if (errs & RMD_CRC)
			kprintf("ethread: CRC error\n");
		if (errs & RMD_BUFF)
			kprintf("ethread: don't own next buffer\n");
		goto drop;
	}
	readlen = pmd->lmd_mcnt;
	if (readlen > (EP_DLEN+18))
		goto drop;
	pep = (struct ep *)nbgetbuf(Net.netpool);
	if (pep == 0) {
		if (ifnum >= 0 && ifnum < NIF)
			nif[ifnum].ni_idiscard++;
		goto drop2;
	}
	blkcopy(&pep->ep_eh, pbre->buf, readlen-EP_CRC);
	/* give this buffer back to the ethernet chip */
	pmd->lmd_flags = LMD_OWN;
	pbre->flags = 0;
	/* deliver it to the interface */

#if	Noth > 0
	dest = (char *)pep->ep_dst;
	for (noth=0; noth<Noth; ++noth) {
		otptr = etptr->etoth[noth];
		if (otptr == 0 || !otptr->ot_valid)
			continue;
	   	if (blkequ(dest, otptr->ot_paddr, EP_ALEN) ||
				blkequ(dest, otptr->ot_baddr, EP_ALEN))
			break;
	}
	if (noth != Noth)
		ifnum = otptr->ot_intf;
#endif	/* Noth > 0 */
	if (ifnum < 0)
		return freebuf(pep);
	if (nif[ifnum].ni_state != NIS_UP) {
		nif[ifnum].ni_idiscard++;
		return freebuf(pep);
	}
	pep->ep_type = net2hs(pep->ep_type);
	ni_in(&nif[ifnum], pep, readlen);
	return OK;
drop:
	if (ifnum >= 0 && ifnum < NIF)
		nif[ifnum].ni_ierrors++;
drop2:
	/* give this buffer back to the ethernet chip */
	pmd->lmd_flags = LMD_OWN;
	pbre->flags = 0;
	return SYSERR;
}
