/* ospf.c - ospf */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ports.h>
#include <proc.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  ospf -  start OSPF processes and become OSPF input process
 *------------------------------------------------------------------------
 */
PROCESS
ospf(void)
{
	struct	ep	*pep;
	struct	ip	*pip;
	struct	ospf	*po;
	struct	ospf_if	*pif;

	if (!gateway)
		return SYSERR;
	ospfinit();
	ospf_iport = pcreate(OSPFQLEN);
	if (ospf_iport == SYSERR)
		panic("ospf: cannot open ospf port");
	resume(create(ospfhello, OSPFHSTK, OSPFHPRI, OSPFHNAM, OSPFHARGC));

	while (TRUE) {
		pep = (struct ep *)preceive(ospf_iport);
		if (pep == (struct ep *)SYSERR)
			continue;
		pip = (struct ip *)pep->ep_data;
		po = (struct ospf *)((char *)pip + IP_HLEN(pip));
		if (ospfcheck(pep) != OK)
			continue;
		ospfnet2h(po);
		pep->ep_order |= EPO_OSPF;
		switch (po->ospf_type) {
		case T_HELLO:		ospf_hin(pep);
					break;
		case T_DATADESC:	ospf_ddin(pep);
					break;
		case T_LSREQ:		lsr_in(pep);
					break;
		case T_LSUPDATE:	lsu_in(pep);
					break;
		case T_LSACK:		lsack_in(pep);
					break;
		default:
			break;
		}
		pif = &ospf_if[pep->ep_ifn];
		if ((pif->if_state == IFS_WAITING &&
		    (pif->if_event&IFE_BSEEN)) ||
	    	    (pif->if_state >= IFS_DROTHER &&
		    (pif->if_event&IFE_NCHNG))) {
			if_elect(pep->ep_ifn);
			pif->if_event &= ~(IFE_BSEEN|IFE_NCHNG);
		}
		freebuf(pep);
	}
	return OK;	/* not reached */
}

Bool	doospf = FALSE;
int	ospfpid = BADPID;
int	ospf_iport;
