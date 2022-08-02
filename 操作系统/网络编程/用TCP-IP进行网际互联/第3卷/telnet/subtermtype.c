/* subtermtype.c - subtermtype */

#include <sys/types.h>

#include <stdio.h>

#include "telnet.h"

extern char	*term;		/* terminal name, from initialization	*/

/*------------------------------------------------------------------------
 * subtermtype - do terminal type option subnegotation
 *------------------------------------------------------------------------
 */
int
subtermtype(FILE *sfp, FILE *tfp, int c)
{
	/* have received IAC.SB.TERMTYPE.SEND */

	(void) putc(TCIAC, sfp);
	(void) putc(TCSB, sfp);
	(void) putc(TOTERMTYPE, sfp);
	(void) putc(TT_IS, sfp);
	fputs(term, sfp);
	(void) putc(TCIAC, sfp);
	(void) putc(TCSE, sfp);
	return 0;
}
