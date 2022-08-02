/* tcout.c - tcout */

#ifdef BSD
#include <newcurses.h>
#else
#include <curses.h>
#endif
#include <stdlib.h>
#include <stdio.h>

#define	TBUFSIZE	2048

int	xfputs(char *str, FILE *fp);

/*------------------------------------------------------------------------
 * tcout - print the indicated terminal capability on the given stream
 *------------------------------------------------------------------------
 */
int
tcout(char *cap, FILE *tfp)
{
	static init;
	static char	*term;
	static char	tbuf[TBUFSIZE], buf[TBUFSIZE], *bp = buf;
	char		*sv;

	if (!init) {
		init = 1;
		term = getenv("TERM");
	}
	if (term == 0 || tgetent(&tbuf[0], term) != 1)
		return 0;
	if (sv = tgetstr(cap, &bp)) {
		xfputs(sv, tfp);
		return 1;
	}
	return 0;
}
