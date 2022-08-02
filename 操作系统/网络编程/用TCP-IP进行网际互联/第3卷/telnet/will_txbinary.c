/* will_txbinary.c - will_txbinary */

#include <sys/types.h>

#include <stdio.h>

#include "telnet.h"

char		sndbinary;	/* non-zero if TRANSMIT-BINARY		*/
extern u_char	option_cmd;

/*------------------------------------------------------------------------
 * will_txbinary - handle telnet "do/don't" TRANSMIT-BINARY option
 *------------------------------------------------------------------------
 */
int
will_txbinary(FILE *sfp, FILE *tfp, int c)
{
	if (sndbinary) {
		if (option_cmd == TCDO)
			return 0;
	} else if (option_cmd == TCDONT)
		return 0;
	sndbinary = !sndbinary;
	(void) putc(TCIAC, sfp);
	if (sndbinary)
		(void) putc(TCWILL, sfp);
	else
		(void) putc(TCWONT, sfp);
	(void) putc((char)c, sfp);
	return 0;
}
