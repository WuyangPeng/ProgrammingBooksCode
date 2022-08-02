/* ttyalloc.c - ttyalloc */

#include <conf.h>
#include <kernel.h>
#include <tty.h>

/*------------------------------------------------------------------------
 * ttyalloc - allocate a tty structure
 *------------------------------------------------------------------------
 */
struct tty *
ttyalloc()
{
	STATWORD	ps;
	int		i;

	disable(ps);
	for (i=0; i<Ntty; ++i)
		if (ttytab[i].tty_state == TTYS_FREE) {
			ttytab[i].tty_state = TTYS_ALLOC;
			restore(ps);
			return &ttytab[i];
		}
	restore(ps);
	return 0;
}
