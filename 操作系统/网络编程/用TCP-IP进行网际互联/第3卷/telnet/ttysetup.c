/* ttysetup.c - ttysetup */

#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>

#include "local.h"

/*------------------------------------------------------------------------
 * ttysetup - set up tty
 *------------------------------------------------------------------------
 */
int
ttysetup(void)
{
	extern struct termios	tntty;

	if (tcgetattr(0, &oldtty) < 0)	/* save original tty state	*/
		errexit("can't get tty modes: %s\n", strerror(errno));

	sg_erase = oldtty.c_cc[VERASE];
	sg_kill = oldtty.c_cc[VKILL];
	t_intrc = oldtty.c_cc[VINTR];
	t_quitc = oldtty.c_cc[VQUIT];
	t_flushc = oldtty.c_cc[VDISCARD];

	tntty = oldtty;		/* make a copy to change	*/

	/* disable some special characters */
	tntty.c_cc[VINTR] = _POSIX_VDISABLE;
	tntty.c_cc[VQUIT] = _POSIX_VDISABLE;
	tntty.c_cc[VSUSP] = _POSIX_VDISABLE;
#ifdef VDSUSP
	tntty.c_cc[VDSUSP] = _POSIX_VDISABLE;
#endif

	if (tcsetattr(0, TCSADRAIN, &tntty) < 0)
		errexit("can't set tty modes: %s\n", strerror(errno));
}
