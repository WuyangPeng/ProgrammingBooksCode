/* ttwrite.c - ttwrite */

#include <sys/types.h>

#include <stdio.h>

#include "tnfsm.h"

extern struct fsm_trans	ttstab[];
extern unsigned char	ttfsm[][NCHRS];
extern int		ttstate;

/*------------------------------------------------------------------------
 * ttwrite - do output processing for (local) network virtual printer
 *------------------------------------------------------------------------
 */
int
ttwrite(FILE *sfp, FILE *tfp, unsigned char *buf, int cc)
{
	struct fsm_trans	*pt;
	int			i, ti;

	for (i=0; i<cc; ++i) {
		int	c = buf[i];

		ti = ttfsm[ttstate][c];
		pt = &ttstab[ti];

		(pt->ft_action)(sfp, tfp, c);
		ttstate = pt->ft_next;
	}
}
