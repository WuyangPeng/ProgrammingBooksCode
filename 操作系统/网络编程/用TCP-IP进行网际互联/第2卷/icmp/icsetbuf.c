/* icsetbuf.c - icsetbuf */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  icsetbuf -  set up a buffer for an ICMP message
 *------------------------------------------------------------------------
 */
struct ep *
icsetbuf(int type, void *pa1, Bool *pisresp, Bool *piserr)
{
	struct	ep	*pep;

	*pisresp = *piserr = FALSE;

	switch (type) {
	case ICT_REDIRECT:
		pep = (struct ep *)getbuf(Net.netpool);
		if ((int)pep == SYSERR)
			return 0;
		memcpy(pep, pa1, MAXNETBUF);
		pa1 = (void *)pep;
		*piserr = TRUE;
		break;
	case ICT_DESTUR:
	case ICT_SRCQ:
	case ICT_TIMEX:
	case ICT_PARAMP:
		pep = (struct ep *)pa1;
		*piserr = TRUE;
		break;
	case ICT_ECHORP:
	case ICT_INFORP:
	case ICT_MASKRP:
		pep = (struct ep *)pa1;
		*pisresp = TRUE;
		break;
	case ICT_ECHORQ:
	case ICT_TIMERQ:
	case ICT_INFORQ:
	case ICT_MASKRQ:
		pep = (struct ep *)getbuf(Net.lrgpool);
		if ((int)pep == SYSERR)
			return 0;
		break;
	case ICT_TIMERP:		/* Not Implemented */
		/* IcmpOutTimestampsReps++; */
		IcmpOutErrors--;	/* Kludge: we increment above */
		freebuf(pa1);
		return 0;
	default:
		kprintf("icsetbuf: unknown ICMP type (%d)\n", type);
		return 0;
	}
	if (*piserr)
		*pisresp = TRUE;
	switch (type) {		/* Update MIB Statistics */
	case ICT_ECHORP:	IcmpOutEchos++;		break;
	case ICT_ECHORQ:	IcmpOutEchoReps++;	break;
	case ICT_DESTUR:	IcmpOutDestUnreachs++;	break;
	case ICT_SRCQ:		IcmpOutSrcQuenchs++;	break;
	case ICT_REDIRECT:	IcmpOutRedirects++;	break;
	case ICT_TIMEX:		IcmpOutTimeExcds++;	break;
	case ICT_PARAMP:	IcmpOutParmProbs++;	break;
	case ICT_TIMERQ:	IcmpOutTimestamps++;	break;
	case ICT_TIMERP:	IcmpOutTimestampReps++;	break;
	case ICT_MASKRQ:	IcmpOutAddrMasks++;	break;
	case ICT_MASKRP:	IcmpOutAddrMaskReps++;	break;
	}
	return pep;
}
