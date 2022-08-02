/* ttinit.c - ttinit */

#include <sys/types.h>

#include <stdio.h>

#include "tnfsm.h"

extern struct fsm_trans	ttstab[], sostab[], substab[];
extern unsigned char	ttfsm[][NCHRS], sofsm[][NCHRS], subfsm[][NCHRS];
extern int		ttstate, sostate, substate;

int
fsminit(unsigned char fsm[][NCHRS], struct fsm_trans ttab[], int nstates);

/*------------------------------------------------------------------------
 * fsmbuild - build the Finite State Machine data structures
 *------------------------------------------------------------------------
 */
int
fsmbuild()
{
	fsminit(ttfsm, ttstab, NTSTATES);
	ttstate = TSDATA;

	fsminit(sofsm, sostab, NKSTATES);
	sostate = KSREMOTE;

	fsminit(subfsm, substab, NSSTATES);
	substate = SS_START;
}
