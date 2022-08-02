/* ee_mcast.c - ee_mcadd, ee_mcdel, ee_mcset */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <i386.h>
#include <ee.h>

/*------------------------------------------------------------------------
 * ee_mcadd - add multicast addresses for Intel EtherExpress16
 *------------------------------------------------------------------------
 */
int
ee_mcadd(ped, mca)
struct etdev	*ped;
Eaddr		mca;
{
	STATWORD	ps;
	int		i;

#ifdef MULTICAST
	disable(ps);
	for (i=0; i<ped->ed_mcc; ++i)
		if (!memcmp(mca, ped->ed_mca[i], sizeof mca)) {
			restore(ps);
			return OK;	/* already there */
		}
	memcpy(ped->ed_mca[i], mca, EP_ALEN);
	ped->ed_mcc++;
	restore(ps);
	while (enq(ped->ed_outq, (void *)EE_SETMULTI, -1) < 0) {
		/* queue full; retry later */
		sleep10(1);
	}
	ee_wstrt(ped);
	return OK;
#else	/* MULTICAST */
	return SYSERR;
#endif	/* MULTICAST */
}

/*------------------------------------------------------------------------
 * ee_mcdel - delete multicast addresses for Intel EtherExpress16
 *------------------------------------------------------------------------
 */
int
ee_mcdel(ped, mca)
struct etdev	*ped;
Eaddr		mca;
{
	STATWORD	ps;
	int		i;

#ifdef	MULTICAST
	disable(ps);
	for (i=0; i<ped->ed_mcc; ++i)
		if (!memcmp(mca, ped->ed_mca[i], EP_ALEN))
			break;
	if (i == ped->ed_mcc) {
		restore(ps);
		return OK;
	}
	i++;
	for (; i<ped->ed_mcc; ++i)
		memcpy(ped->ed_mca[i-1], ped->ed_mca[i], EP_ALEN);
	ped->ed_mcc--;
	restore(ps);
	while (enq(ped->ed_outq, (void *)EE_SETMULTI, -1) < 0) {
		/* queue full; retry later */
		sleep10(1);
	}
	ee_wstrt(ped);
	return OK;
#else	/* MULTICAST */
	return SYSERR;
#endif	/* MULTICAST */
}

mcdump(ped)
struct etdev	*ped;
{
	int	i, j;

	kprintf("mcc %d\n", ped->ed_mcc);
	for (i=0; i<ped->ed_mcc; ++i) {
		kprintf("%d) ", i);
		for (j=0; j<EP_ALEN-1; ++j)
			kprintf("%02x:", ped->ed_mca[i][j]);
		kprintf("%02x\n", ped->ed_mca[i][j]);
	}
}
