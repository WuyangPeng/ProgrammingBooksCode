/* scrwrap.c - scrwrap */

#include <sys/file.h>

#include <termios.h>
#include <stdio.h>
#include <string.h>

#include "local.h"

extern struct termios	tntty;
extern char		scrname[];
extern int		scrindex, errno;

/*------------------------------------------------------------------------
 * scrwrap - wrap-up script filename collection
 *------------------------------------------------------------------------
 */
int
scrwrap(FILE *sfp, FILE *tfp, int c)
{
	int	fd;

	if (scrindex) {
		scrname[scrindex] = '\0';
		scrindex = 0;
		fd = open(scrname, O_WRONLY|O_CREAT|O_TRUNC, 0644);
		if (fd < 0)
			fprintf(tfp, "\ncan't write \"%s\": %s\n",
				scrname, strerror(errno));
		else
			scrfp = fdopen(fd, "w");
	}
	if (tcsetattr(0, TCSADRAIN, &tntty) < 0)
		errexit("tcsetattr: %s\n", strerror(errno));
	return 0;
}
