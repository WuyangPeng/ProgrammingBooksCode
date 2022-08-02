/* soputc.c - soputc */

#include <sys/types.h>

#include <stdio.h>

#include "telnet.h"
#include "local.h"

/*------------------------------------------------------------------------
 * soputc - move a character from the keyboard to the socket
 *------------------------------------------------------------------------
 */
int
soputc(FILE *sfp, FILE *tfp, int c)
{
	if (sndbinary) {
		if (c == TCIAC)
			(void) putc(TCIAC, sfp); /* byte-stuff IAC	*/
		(void) putc(c, sfp);
		return 0;
	}
	c &= 0x7f;	/* 7-bit ASCII only */
	if (c == t_intrc || c == t_quitc) {	/* Interrupt		*/
		(void) putc(TCIAC, sfp);
		(void) putc(TCIP, sfp);
	} else if (c == sg_erase) {		/* Erase Char		*/
		(void) putc(TCIAC, sfp);
		(void) putc(TCEC, sfp);
	} else if (c == sg_kill) {		/* Erase Line		*/
		(void) putc(TCIAC, sfp);
		(void) putc(TCEL, sfp);
	} else if (c == t_flushc) {		/* Abort Output		*/
		(void) putc(TCIAC, sfp);
		(void) putc(TCAO, sfp);
	} else
		(void) putc(c, sfp);
	return 0;
}
