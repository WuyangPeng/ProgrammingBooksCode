/* sync.c - tcdm, rcvurg */

#include <stdio.h>

char	synching;	/* non-zero, if we are doing telnet SYNCH	*/

/*------------------------------------------------------------------------
 * tcdm - handle the telnet "DATA MARK" command (marks end of SYNCH)
 *------------------------------------------------------------------------
 */
int
tcdm(FILE *sfp, FILE *tfp, int c)
{
	if (synching > 0)
		synching--;
	return 0;
}

/*------------------------------------------------------------------------
 * rcvurg - receive urgent data input (indicates a telnet SYNCH)
 *------------------------------------------------------------------------
 */
int
rcvurg(int sig)
{
	synching++;
}
