/* do_noga.c - do_noga */

#include <sys/types.h>

#include <stdio.h>

#include "telnet.h"

extern u_char	option_cmd;

/*------------------------------------------------------------------------
 * do_noga - don't do telnet Go-Ahead's
 *------------------------------------------------------------------------
 */
int
do_noga(FILE *sfp, FILE *tfp, int c)
{
	static	noga;

	if (noga) {
		if (option_cmd == TCWILL)
			return 0;
	} else if (option_cmd == TCWONT)
		return 0;
	noga = !noga;
	(void) putc(TCIAC, sfp);
	if (noga)
		(void) putc(TCDO, sfp);
	else
		(void) putc(TCDONT, sfp);
	(void) putc((char)c, sfp);
	return 0;
}
