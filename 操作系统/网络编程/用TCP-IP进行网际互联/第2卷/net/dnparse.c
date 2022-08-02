/* dnparse.c - dnparse */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ctype.h>

/*------------------------------------------------------------------------
 *  dnparse  -  parse foreign address specification; get IP and port #s
 *------------------------------------------------------------------------
 */
int
dnparse(char *fspec, IPaddr *paddr, unsigned short *pport)
{
	int	i;
	char	ch;

	if (fspec == ANYFPORT) {
		*pport = 0;
		return OK;
	}
	/* parse forms like 192.5.48.30:3 into (ip-address,port)	*/

	*paddr = dot2ip(fspec);
	fspec = index(fspec, ':');
	if (fspec == 0 || *fspec != ':')
		return SYSERR;
	fspec++;
	i = 0;
	while (isdigit(ch = *fspec++))
		i = 10*i + (ch - '0');
	if (i==0 || ch!='\0')
		return SYSERR;
	*pport = i;
	return OK;
}
