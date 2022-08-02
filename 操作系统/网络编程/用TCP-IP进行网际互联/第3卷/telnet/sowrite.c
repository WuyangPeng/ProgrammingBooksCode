/* sowrite.c - sowrite */

#include <sys/types.h>

#include <stdio.h>

#include "tnfsm.h"

extern struct fsm_trans	sostab[];
extern int		sostate;
extern unsigned char	sofsm[][NCHRS];

/*------------------------------------------------------------------------
 * sowrite - do output processing to the socket
 *------------------------------------------------------------------------
 */
int
sowrite(FILE *sfp, FILE *tfp, unsigned char *buf, int cc)
{
	struct fsm_trans	*pt;
	int			i, ki;

	for (i=0; i<cc; ++i) {
		int	c = buf[i];

		ki = sofsm[sostate][c];
		pt = &sostab[ki];

		if ((pt->ft_action)(sfp, tfp, c) < 0)
			sostate = KSREMOTE;	/* an error occurred	*/
		else
			sostate = pt->ft_next;
	}
}
