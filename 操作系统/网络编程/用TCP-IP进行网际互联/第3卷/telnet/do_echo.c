/* do_echo.c - do_echo */

#include <sys/types.h>

#include <termios.h>
#include <stdio.h>

#include "telnet.h"

char		doecho;		/* nonzero, if remote ECHO	*/
extern u_char	option_cmd;

/*------------------------------------------------------------------------
 * do_echo - handle TELNET WILL/WON'T ECHO option
 *------------------------------------------------------------------------
 */
int
do_echo(FILE *rfp, FILE *tfp, int c)
{
        struct termios  tio;
	static char	savec[2];
	int		ok, tfd = fileno(tfp);

	if (doecho) {
		if (option_cmd == TCWILL)
			return 0;	/* already doing ECHO		*/
	} else if (option_cmd == TCWONT)
		return 0;		/* already NOT doing ECHO	*/

        if (ok = tcgetattr(tfd, &tio) == 0) {
        	if (option_cmd == TCWILL) {
              	 	tio.c_lflag &= ~(ECHO | ICANON);
			/* VMIN & VTIME are overloaded with other chars,
			 * so save and restore them later.
			 */
			savec[0] = tio.c_cc[VMIN];
			savec[1] = tio.c_cc[VTIME];
			tio.c_cc[VMIN] = 1;
			tio.c_cc[VTIME] = 0;
		} else {
			tio.c_lflag |= (ECHO | ICANON);
			tio.c_cc[VMIN] = savec[0];
			tio.c_cc[VTIME] = savec[1];
		}
		ok &= tcsetattr(tfd, TCSADRAIN, &tio) == 0;
        }
	if (ok)
		doecho = !doecho;
        (void) putc(TCIAC, rfp);
        if (doecho)
                (void) putc(TCDO, rfp);
        else
                (void) putc(TCDONT, rfp);
	(void) putc((char)c, rfp);
	return 0;
}
