/* suspend.c - */

#include <sys/types.h>
#include <sys/signal.h>

#include <stdio.h>
#include <string.h>

#include "local.h"

extern struct termios	tntty;

/*------------------------------------------------------------------------
 * suspend - suspend execution temporarily
 *------------------------------------------------------------------------
 */
int
suspend(FILE *sfp, FILE *tfp, int c)
{
	if (tcgetattr(0, &tntty) < 0)	/* save current tty state	*/
		errexit("can't get tty modes: %s\n", strerror(errno));
	if (tcsetattr(0, TCSADRAIN, &oldtty) < 0) /* restore old state	*/
		errexit("can't set tty modes: %s\n", strerror(errno));

	(void) kill(0, SIGTSTP);

	if (tcgetattr(0, &oldtty) < 0)	/* may have changed		*/
		errexit("can't get tty modes: %s\n", strerror(errno));
	if (tcsetattr(0, TCSADRAIN, &tntty) < 0) /* back to telne modes*/
		errexit("can't set tty modes: %s\n", strerror(errno));
	return 0;
}
