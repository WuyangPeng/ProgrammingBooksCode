/* ttputc.c - ttputc */

#include <sys/types.h>

#include <stdio.h>

#include "telnet.h"

int	tcout(char *cap, FILE *tfp);
int	xputc(char ch, FILE *fp);

/*------------------------------------------------------------------------
 * ttputc - print a single character on a Network Virtual Terminal
 *------------------------------------------------------------------------
 */
int
ttputc(FILE *sfp, FILE *tfp, int c)
{
	static	last_char;
	int	tc;

	if (rcvbinary) { 
		(void) xputc(c, tfp);	/* print uninterpretted	*/
		return 0;
	}
	if (synching)			/* no data, if in SYNCH	*/
		return 0;

	if ((last_char == VPCR && c == VPLF) ||
	    (last_char == VPLF && c == VPCR)) {
		(void) xputc(VPLF, tfp);
		last_char = 0;
		return 0;
	}
	if (last_char == VPCR)
		(void) tcout("cr", tfp);
	else if (last_char == VPLF)
		(void) tcout("do", tfp);
	if (c >= ' ' && c < TCIAC)	/* printable ASCII	*/
		(void) xputc(c, tfp);
	else {				/* NVT special		*/
		switch (c) {
		case VPLF: 		/* see if CR follows	*/
		case VPCR:	tc = 1;	/* see if LF follows	*/
				break;
		case VPBEL:	tc = tcout("bl", tfp);
				break;
		case VPBS:	tc = tcout("bc", tfp);
				break;
		case VPHT:	tc = tcout("ta", tfp);
				break;
		case VPVT:	tc = tcout("do", tfp);
				break;
		case VPFF:	tc = tcout("cl", tfp);
				break;
		default:
			tc = 1;
			break;	/* no action */
		}
		if (!tc)		/* if no termcap, assume ASCII */
			(void) xputc(c, tfp);
	}
	last_char = c;
	return 0;
}
