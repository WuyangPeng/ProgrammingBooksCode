/* x_arp.c - x_arp */

#include <conf.h>
#include <kernel.h>
#include <network.h>

static parp(), xarpusage();

/*------------------------------------------------------------------------
 *  x_arp  -  print ARP tables
 *------------------------------------------------------------------------
 */
COMMAND	x_arp(stdin, stdout, stderr, nargs, args)
int	stdin, stdout, stderr, nargs;
char	*args[];
{
	if (nargs != 1)
		return xarpusage(stderr);
	arpprint(stdout);
	return OK;
}

static
xarpusage(int stderr)
{
	char *str="usage: arp\n";

	write(stderr, str, strlen(str));
	return OK;
}
