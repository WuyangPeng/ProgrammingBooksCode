/* snerr.c - snerr */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <io.h>

#ifdef	SNMP

#include <ctype.h>
#include <snmp.h>

/*------------------------------------------------------------------------
 * snerr - tell the user that an erroneous packet was received
 *------------------------------------------------------------------------
 */
void
snerr(int stdout, struct req_desc *rqdp)
{
	struct 	snbentry *bindl;
	int	i;
	char	buf[128];
	
	if (sna2b(rqdp) == SYSERR)
		return;
	for (bindl = rqdp->bindlf, i = 1; bindl && i != rqdp->err_idx;
		bindl = bindl->sb_next, i++)
	    /* empty */;
	sprintf(buf, "Received error %d for object ", rqdp->err_stat);
	write(stdout, buf, strlen(buf));
	snmpprint_objid(stdout, &bindl->sb_oid);
	write(stdout, "\n", 1);
}
#endif	/* SNMP */
