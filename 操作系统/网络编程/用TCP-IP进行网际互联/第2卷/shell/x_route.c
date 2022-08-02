/* x_route.c - x_route */

#include <conf.h>
#include <kernel.h>
#include <network.h>

static	int	xrtusage();
struct	route	*rtget();

/*------------------------------------------------------------------------
 *  x_route  -  add/delete routes
 *------------------------------------------------------------------------
 */
COMMAND	x_route(stdin, stdout, stderr, nargs, args)
int	stdin, stdout, stderr, nargs;
char	*args[];
{
	Bool	isadd;
	char	str[80];
	IPaddr	dest, mask, gw;
	int	metric, ttl;
	int	i;

	if (nargs < 4)
		return xrtusage(stderr);

	if (strcmp(args[1], "add") == 0)
		isadd = TRUE;
	else if (strcmp(args[1], "delete") == 0)
		isadd = FALSE;
	else
		return xrtusage(stderr);
	if ((isadd && nargs != 7) || (!isadd && nargs != 4))
		return xrtusage(stderr);
	dest = dot2ip(args[2]);
	mask = dot2ip(args[3]);

	if (isadd) {
		struct route *prt;

		gw = dot2ip(args[4]);

		metric = atoi(args[5]);
		ttl = atoi(args[6]);

		prt = rtget(gw, 1);
		if (prt == NULL) {
			sprintf(str, "route: no route to gateway\n");
			write(stderr, str, strlen(str));
		}
		if(rtadd(dest,mask,gw,metric,prt->rt_ifnum,ttl) == SYSERR){
			sprintf(str, "route: add failed\n");
			write(stderr, str, strlen(str));
		}
		rtfree(prt);
	} else {
		if (rtdel(dest, mask) == SYSERR) {
			sprintf(str, "route: delete failed\n");
			write(stderr, str, strlen(str));
		}
	}

	return(OK);
}

static
xrtusage(stderr)
{
	char *str = "usage:\troute add <dest> <mask> <gateway> <metric> <ttl>\n\troute delete <dest> <mask>\n";

	write(stderr, str, strlen(str));
	return OK;
}

