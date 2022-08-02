/* scrinit.c - scrinit */

#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <stdio.h>

#include "telnet.h"
#include "local.h"

extern int		scrindex;
extern struct termios	tntty;

/*------------------------------------------------------------------------
 * scrinit - initialize tty modes for script file collection
 *------------------------------------------------------------------------
 */
int
scrinit(FILE *sfp, FILE *tfp, int c)
{
	struct termios	newtty;

	if (!doecho) {
		fprintf(tfp, "\nscripting requires remote ECHO.\n");
		return -1;
	}
	if (scrfp) {
		fprintf(tfp,"\nalready scripting to \"%s\".\n", scrname);
		return -1;
	}
	scrindex = 0;

	if (tcgetattr(0, &tntty))	/* save current tty settings	*/
		errexit("can't get tty modes: %s\n", strerror(errno));

	newtty = oldtty;
	newtty.c_cc[VINTR] = _POSIX_VDISABLE;	/* disable interrupt	*/
	newtty.c_cc[VQUIT] = _POSIX_VDISABLE;	/* disable interrupt	*/
	newtty.c_cc[VSUSP] = _POSIX_VDISABLE;	/* disable suspend	*/
#ifdef VDSUSP
	newtty.c_cc[VDSUSP] = _POSIX_VDISABLE;	/* disable suspend	*/
#endif

	if (tcsetattr(0, TCSADRAIN, &newtty))
		errexit("can't set tty modes: %s\n", strerror(errno));

	fprintf(tfp, "\nscript file: ");
	(void) fflush(tfp);
	return 0;
}
