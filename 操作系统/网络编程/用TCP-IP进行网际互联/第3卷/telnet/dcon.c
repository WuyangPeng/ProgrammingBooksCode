/* dcon.c - dcon */

#include <stdlib.h>
#include <stdio.h>
#include <termios.h>

#include "local.h"

/*------------------------------------------------------------------------
 * dcon - disconnect from remote
 *------------------------------------------------------------------------
 */
int
dcon(FILE *sfp, FILE *tfp, int c)
{
	fprintf(tfp, "disconnecting.\n");
	(void) tcsetattr(0, TCSADRAIN, &oldtty);
	exit(0);
}
