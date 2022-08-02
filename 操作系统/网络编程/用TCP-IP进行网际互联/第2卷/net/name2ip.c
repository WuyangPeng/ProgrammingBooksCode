/* name2ip.c - name2ip, gname, resolve */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <mem.h>

static IPaddr resolve(char *);
static IPaddr gname(char *);

/*------------------------------------------------------------------------
 *  name2ip  -  return the IP address for a given DNS name
 *------------------------------------------------------------------------
 */
IPaddr
name2ip(char *nam)
{
	Bool	isnum;
	char	*p;

	isnum = TRUE;
	for (p=nam; *p; ++p) {
		isnum &= ((*p >= '0' && *p <= '9') || *p == '.');
		if (!isnum)
			break;
	}
	if (isnum)
		return dot2ip(nam);
	return resolve(nam);
}

/*------------------------------------------------------------------------
 *  gname  -  use the DNS to look up the name
 *------------------------------------------------------------------------
 */
static IPaddr
gname(char *nam)
{
	IPaddr	ip;
	char	tmpstr[64];		/* temporary string buffer	*/
	char	*buf;			/* buffer to hold domain query	*/
	int	dg, i;
	register char	*p, *p2, *p3;
	register struct	dn_mesg *dnptr;

	dnptr = (struct dn_mesg *) (buf = (char *) getmem(DN_MLEN));
	dnptr->dn_id = 0;
	dnptr->dn_opparm = hs2net(DN_RD);
	dnptr->dn_qcount = hs2net(1);
	dnptr->dn_acount = dnptr->dn_ncount = dnptr->dn_dcount = 0;
	p = dnptr->dn_qaaa;

	strcpy(tmpstr, nam);
	p2 = tmpstr;
	while (p3=index(p2, '.')) {
		*p3 = '\0';
		dn_cat(p, p2);
		p2 = p3+1;
	}
	dn_cat(p, p2);
	*p++ = NULLCH;	/* terminate name */

	/* Add query type and query class fields to name */

	( (struct dn_qsuf *)p )->dn_type = hs2net(DN_QTHA);
	( (struct dn_qsuf *)p )->dn_clas = hs2net(DN_QCIN);
	p += sizeof(struct dn_qsuf);

	/* send query */

	dg = open(UDP, NSERVER, ANYLPORT);
	control(dg, DG_SETMODE, DG_DMODE | DG_TMODE);
	write (dg, buf, p - buf);
	if ( (i = read(dg, buf, DN_MLEN)) == SYSERR || i == TIMEOUT) {
		close(dg);
		freemem(buf, DN_MLEN);
		return (IPaddr)SYSERR;
	}
	close(dg);
	if (net2hs(dnptr->dn_opparm) & DN_RESP ||
	    net2hs(dnptr->dn_acount) <= 0) {
		freemem(buf, DN_MLEN);
		return (IPaddr)SYSERR;
	}
	/* In answer, skip name and remainder of resource record header	*/

	while (*p != NULLCH)
		if (*p & DN_CMPRS) 	/* compressed section of name	*/
			*++p = NULLCH;
		else
			p += *p + 1;
	p += DN_RLEN + 1;

	/* Copy IP to user */

	for (i=0; i < IP_ALEN; ++i)
		((char *)&ip)[i] = *p++;
	freemem(buf, DN_MLEN);
	return ip;
}

/*------------------------------------------------------------------------
 *  resolve  -  do shorthand DNS name resolution
 *------------------------------------------------------------------------
 */
static IPaddr
resolve(char *nam)
{
	IPaddr	ip;
	char	myname[64];
	char	name_buf[100];
	char	*name_suffix;

	/* if it ends in a 'dot', remove it and try exactly once */
	if (nam[strlen(nam)-1] == '.') {
		strcpy(name_buf, nam);
		name_buf[strlen(name_buf)-1] = NULLCH;
		return gname(name_buf);
	}
	if (getname(myname) == SYSERR)
		return (IPaddr)SYSERR;
	name_suffix = myname;

	/* tack on successively smaller suffixes of MY name */
	while (name_suffix = index(++name_suffix, '.')) {
		sprintf(name_buf, "%s%s", nam, name_suffix);
		if ((ip = gname(name_buf)) != (unsigned) SYSERR)
			return ip;
	}
	return gname(nam);		/* try the original	*/
}
