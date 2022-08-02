/* will_termtype.c - will_termtype */

#include <sys/types.h>

#include <stdlib.h>
#include <stdio.h>

#include "telnet.h"

char		termtype;	/* non-zero if received "DO TERMTYPE"	*/
char		*term;		/* terminal name			*/
extern u_char	option_cmd;

int	do_txbinary(FILE *,FILE *,int), will_txbinary(FILE *,FILE *,int);

/*------------------------------------------------------------------------
 * will_termtype - handle telnet "do/don't" TERMINAL-TYPE option
 *------------------------------------------------------------------------
 */
int
will_termtype(FILE *sfp, FILE *tfp, int c)
{
	if (termtype) {
		if (option_cmd == TCDO)
			return 0;
	} else if (option_cmd == TCDONT)
		return 0;
	termtype = !termtype;
	if (termtype)
		if (!term && !(term = getenv("TERM")))
			termtype = !termtype;	/* can't do it... */
	(void) putc(TCIAC, sfp);
	if (termtype)
		(void) putc(TCWILL, sfp);
	else
		(void) putc(TCWONT, sfp);
	(void) putc((char)c, sfp);
	if (termtype) {	/* set up binary data path; send WILL, DO */
		option_cmd = TCWILL;
		(void) do_txbinary(sfp, tfp, TOTXBINARY);
		option_cmd = TCDO;
		(void) will_txbinary(sfp, tfp, TOTXBINARY);
	}
	return 0;
}
