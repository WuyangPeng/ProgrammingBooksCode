/* ttynew.c - ttynew */

#include <conf.h>
#include <kernel.h>
#include <tty.h>

extern struct tchars dfltchars;

/*------------------------------------------------------------------------
 * ttynew - allocate and initialize a tty structure
 *------------------------------------------------------------------------
 */
struct tty *
ttynew()
{
	struct tty	*ptty, *ttyalloc();

	ptty = ttyalloc();
	if(ptty == 0)
		return 0;
	ptty->tty_tchars = dfltchars;	/* struct copy */

	ptty->tty_cpid = getpid();

	ptty->tty_isema = screate(0);
	ptty->tty_iflags = 0;
	ptty->tty_istart = 0;
	ptty->tty_icount = 0;

	ptty->tty_osema = screate(OBLEN);
	ptty->tty_oflags = 0;
	ptty->tty_ostart = 0;
	ptty->tty_ocount = 0;
	return ptty;
}

#define	CNTRL(c) ((c) - 'a' + 1)

struct tchars  dfltchars = {
	'\b', CNTRL('c'), CNTRL('x'), CNTRL('v'), CNTRL('r'),
	CNTRL('d'), CNTRL('s'), CNTRL('q'), CNTRL('z'), CNTRL('w'),
	'\n', CNTRL('t')
};
