/* will_notsup.c - will_notsup */

#include <sys/types.h>

#include <stdio.h>

#include "telnet.h"

/*------------------------------------------------------------------------
 * will_notsup - handle an unsupported telnet "do/don't" option
 *------------------------------------------------------------------------
 */
int
will_notsup(FILE *sfp, FILE *tfp, int c)
{
	(void) putc(TCIAC, sfp);
	(void) putc(TCWONT, sfp);
	(void) putc((char)c, sfp);
	return 0;
}
