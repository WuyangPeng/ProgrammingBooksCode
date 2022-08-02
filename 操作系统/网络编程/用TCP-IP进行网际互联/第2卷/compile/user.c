/* user.c - main */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <user.h>

#include <proc.h>

struct user utab[] = {
	{ 0, "root", "Xinu Root", 0 },
	{ 3954, "dls", "David L Stevens", 0 },
	{ -1, 0, 0, 0 }
};


static long flags;


user1()
{
	if (open(TTY0, SERIAL0, 0) == SYSERR)
		kprintf("open(tty0, serial0) failed\n");

	while(TRUE) {
		login(TTY0);
		shell(TTY0);
	}
}

/*------------------------------------------------------------------------
 *  main  --  user main program
 *------------------------------------------------------------------------
 */
main()
{
extern int *sltop, slnempty;
	STATWORD	ps;
	struct pentry	*pptr;
	long		*saddr;
	IPaddr myaddr;
	char myname[32];
	int	now;
	int i;

	getutim(&now);

/*	resume(create(user1, 8192, INITPRIO, "tty1", 0)); */

	while(TRUE) {
		login(CONSOLE);
		shell(CONSOLE);
	}
}

#if __GNUC__ >= 2
void __main() {}
#endif
