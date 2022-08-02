/* do_notsup.c - do_notsup */

#include <sys/types.h>

#include <stdio.h>

#include "telnet.h"

extern u_char	option_cmd;

/*------------------------------------------------------------------------
 * do_notsup - handle an unsupported telnet "will/won't" option
 *------------------------------------------------------------------------
 */
int
do_notsup(FILE *sfp, FILE *tfp, int c)
{
	(void) putc(TCIAC, sfp);
	(void) putc(TCDONT, sfp);
	(void) putc((char)c, sfp);
	return 0;
}
