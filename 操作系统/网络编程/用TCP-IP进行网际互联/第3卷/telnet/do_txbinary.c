/* do_txbinary.c - do_txbinary */

#include <sys/types.h>

#include <stdio.h>

#include "telnet.h"

char		rcvbinary;	/* non-zero if remote TRANSMIT-BINARY	*/
extern u_char	option_cmd;

/*------------------------------------------------------------------------
 * do_txbinary - handle telnet "will/won't" TRANSMIT-BINARY option
 *------------------------------------------------------------------------
 */
int
do_txbinary(FILE *sfp, FILE *tfp, int c)
{
	if (rcvbinary) {
		if (option_cmd == TCWILL)
			return 0;
	} else if (option_cmd == TCWONT)
		return 0;
	rcvbinary = !rcvbinary;
	(void) putc(TCIAC, sfp);
	if (rcvbinary)
		(void) putc(TCDO, sfp);
	else
		(void) putc(TCDONT, sfp);
	(void) putc((char)c, sfp);
	return 0;
}
