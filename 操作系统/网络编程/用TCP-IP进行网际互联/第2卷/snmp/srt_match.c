/* srt_match.c - srt_match */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <mib.h>
#include <stdarg.h>

/*------------------------------------------------------------------------
 * srt_match - check if a variable exists in the current Routing Table
 *------------------------------------------------------------------------
 */
int
srt_match(struct snbentry *bindl,
	  ... /* struct route **rtp, int *rtl,int *field */ )
{
	int 	oidi, i;
	Bool	found;
	struct route **rtp;
	va_list ap;
	int *rtl, *field;

	va_start(ap,bindl);
	rtp = va_arg(ap,struct route **);
	rtl = va_arg(ap,int *);
	field = va_arg(ap,int *);
	va_end(ap);

	oidi = SRT_OIDLEN;
	if ((*field = bindl->sb_oid.id[oidi++]) > SNUMF_RTTAB)
		return SYSERR;
	/* oidi points to IP address to match in the routing table. */
	for (found = FALSE, i = 0; !found && i < RT_TSIZE; i++)  
		for (*rtp = rttable[i]; *rtp; *rtp = (*rtp)->rt_next)
			if ((found = soipequ(&bindl->sb_oid.id[oidi],
					(*rtp)->rt_net, IP_ALEN)))
				break;
	if (!found ||				/* not there		*/
	    oidi + IP_ALEN != bindl->sb_oid.len) /* not end of object id*/
		return SYSERR;
	*rtl = i - 1;
	return OK;
}
#endif	/* SNMP */
