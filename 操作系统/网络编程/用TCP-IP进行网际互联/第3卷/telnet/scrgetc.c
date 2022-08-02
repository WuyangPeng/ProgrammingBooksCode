/* scrgetc.c - scrgetc */

#include <termios.h>
#include <string.h>
#include <stdio.h>

#include "local.h"

#define	SFBUFSZ		2048	/* script filename buffer size	*/

struct termios	tntty;
FILE		*scrfp;
char		scrname[SFBUFSZ];
int		scrindex;

/*------------------------------------------------------------------------
 * scrgetc - begin session scripting
 *------------------------------------------------------------------------
 */
int
scrgetc(FILE *sfp, FILE *tfp, int c)
{
	scrname[scrindex++] = c;
	if (scrindex >= SFBUFSZ) {	/* too far */
		fprintf(tfp, "\nname too long\n");
		if (tcsetattr(0, TCSADRAIN, &oldtty) < 0)
			errexit("tcsetattr: %s\n", strerror(errno));
		return -1;
	}
	return 0;
}
