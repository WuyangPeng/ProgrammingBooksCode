/*
 * $XConsortium: gethost.c /main/25 1996/11/13 14:45:48 lehors $
 * $XFree86: xc/programs/xauth/gethost.c,v 3.8 1997/01/18 07:02:10 dawes Exp $
 *
 * 
Copyright (c) 1989  X Consortium

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from the X Consortium.
 * *
 * Author:  Jim Fulton, MIT X Consortium
 */

/* sorry, streams support does not really work yet */
#if defined(STREAMSCONN) && defined(SVR4)
#undef STREAMSCONN
#define TCPCONN
#endif

#ifdef WIN32
#include <X11/Xwinsock.h>
#define EPROTOTYPE WSAEPROTOTYPE
#endif
#include "xauth.h"
#include <X11/X.h>
#include <signal.h>
#include <setjmp.h>
#include <ctype.h>
#ifndef __TYPES__
#include <sys/types.h>
#define __TYPES__
#endif
#ifndef WIN32
#ifndef STREAMSCONN
#ifndef MINIX
#ifndef Lynx
#include <sys/socket.h>
#else
#include <socket.h>
#endif
#include <netdb.h>
#include <netinet/in.h>
#ifdef SYSV
#ifdef i386
#ifndef sco
#include <net/errno.h>
#endif /* !sco */
#endif /* i386 */
#endif /* SYSV */
#else /* MINIX */
#include <net/gen/netdb.h>
#endif /* !MINIX */
#endif /* !STREAMSCONN */
#endif /* !WIN32 */
#include <errno.h>
#ifdef X_NOT_STDC_ENV
extern int errno;
#endif

#ifdef MINIX
#ifdef MNX_TCPCONN
#define TCPCONN
#endif
#define EPROTOTYPE EGENERIC
#endif

#ifdef DNETCONN
#include <netdnet/dn.h>
#include <netdnet/dnetdb.h>
#endif

#ifdef SIGALRM
Bool nameserver_timedout = False;


/*
 * get_hostname - Given an internet address, return a name (CHARON.MIT.EDU)
 * or a string representing the address (18.58.0.13) if the name cannot
 * be found.  Stolen from xhost.
 */

static jmp_buf env;
static 
#ifdef SIGNALRETURNSINT
int
#else
void
#endif
nameserver_lost(sig)
{
  nameserver_timedout = True;
  longjmp (env, -1);
  /* NOTREACHED */
#ifdef SIGNALRETURNSINT
  return -1;				/* for picky compilers */
#endif
}
#endif

char *get_hostname (auth)
    Xauth *auth;
{
    struct hostent *hp = NULL;
#ifndef WIN32
    char *inet_ntoa();
#endif
#ifdef DNETCONN
    struct nodeent *np;
    static char nodeaddr[4 + 2 * DN_MAXADDL];
#endif /* DNETCONN */

    if (auth->address_length == 0)
	return "Illegal Address";
#ifdef TCPCONN
    if (auth->family == FamilyInternet) {
#ifdef SIGALRM
	/* gethostbyaddr can take a LONG time if the host does not exist.
	   Assume that if it does not respond in NAMESERVER_TIMEOUT seconds
	   that something is wrong and do not make the user wait.
	   gethostbyaddr will continue after a signal, so we have to
	   jump out of it. 
	   */
	nameserver_timedout = False;
	signal (SIGALRM, nameserver_lost);
	alarm (4);
	if (setjmp(env) == 0) {
#endif
	    hp = gethostbyaddr (auth->address, auth->address_length, AF_INET);
#ifdef SIGALRM
	}
	alarm (0);
#endif
	if (hp)
	  return (hp->h_name);
	else
	  return (inet_ntoa(*((struct in_addr *)(auth->address))));
    }
#endif
#ifdef DNETCONN
    if (auth->family == FamilyDECnet) {
	struct dn_naddr *addr_ptr = (struct dn_naddr *) auth->address;

	if (np = getnodebyaddr(addr_ptr->a_addr, addr_ptr->a_len, AF_DECnet)) {
	    sprintf(nodeaddr, "%s:", np->n_name);
	} else {
	    sprintf(nodeaddr, "%s:", dnet_htoa(auth->address));
	}
	return(nodeaddr);
    }
#endif

    return (NULL);
}

#ifdef TCPCONN
/*
 * cribbed from lib/X/XConnDis.c
 */
static Bool get_inet_address (name, resultp)
    char *name;
    unsigned int *resultp;		/* return */
{
    unsigned int hostinetaddr = inet_addr (name);
    struct hostent *host_ptr;
    struct sockaddr_in inaddr;		/* dummy variable for size calcs */

#ifndef INADDR_NONE
#define INADDR_NONE -1
#endif

    if (hostinetaddr == INADDR_NONE) {
	if ((host_ptr = gethostbyname (name)) == NULL) {
	    /* No such host! */
	    errno = EINVAL;
	    return False;
	}
	/* Check the address type for an internet host. */
	if (host_ptr->h_addrtype != AF_INET) {
	    /* Not an Internet host! */
	    errno = EPROTOTYPE;
	    return False;
	}
 
	memmove( (char *)&hostinetaddr, (char *)host_ptr->h_addr, 
	      sizeof(inaddr.sin_addr));
    }
    *resultp = hostinetaddr;
    return True;
}
#endif

#ifdef DNETCONN
static Bool get_dnet_address (name, resultp)
    char *name;
    struct dn_naddr *resultp;
{
    struct dn_naddr *dnaddrp, dnaddr;
    struct nodeent *np;

    if (dnaddrp = dnet_addr (name)) {	/* stolen from xhost */
	dnaddr = *dnaddrp;
    } else {
	if ((np = getnodebyname (name)) == NULL) return False;
	dnaddr.a_len = np->n_length;
	memmove( dnaddr.a_addr, np->n_addr, np->n_length);
    }
    *resultp = dnaddr;
    return True;
}
#endif

char *get_address_info (family, fulldpyname, prefix, host, lenp)
    int family;
    char *fulldpyname;
    int prefix;
    char *host;
    int *lenp;
{
    char *retval = NULL;
    int len = 0;
    char *src = NULL;
#ifdef TCPCONN
    unsigned int hostinetaddr;
    struct sockaddr_in inaddr;		/* dummy variable for size calcs */
#endif
#ifdef DNETCONN
    struct dn_naddr dnaddr;
#endif
    char buf[255];

    /*
     * based on the family, set the pointer src to the start of the address
     * information to be copied and set len to the number of bytes.
     */
    switch (family) {
      case FamilyLocal:			/* hostname/unix:0 */
					/* handle unix:0 and :0 specially */
	if (prefix == 0 && (strncmp (fulldpyname, "unix:", 5) == 0 ||
			    fulldpyname[0] == ':')) {
	    extern char *get_local_hostname();

	    if (!get_local_hostname (buf, sizeof buf)) {
		len = 0;
	    } else {
		src = buf;
		len = strlen (buf);
	    }
	} else {
	    src = fulldpyname;
	    len = prefix;
	}
	break;
      case FamilyInternet:		/* host:0 */
#ifdef TCPCONN
	if (!get_inet_address (host, &hostinetaddr)) return NULL;
	src = (char *) &hostinetaddr;
	len = 4; /* sizeof inaddr.sin_addr, would fail on Cray */
	break;
#else
	return NULL;
#endif
      case FamilyDECnet:		/* host::0 */
#ifdef DNETCONN
	if (!get_dnet_address (host, &dnaddr)) return NULL;
	src = (char *) &dnaddr;
	len = (sizeof dnaddr);
	break;
#else
	/* fall through since we don't have code for it */
#endif
      default:
	src = NULL;
	len = 0;
    }

    /*
     * if source was provided, allocate space and copy it
     */
    if (len == 0 || !src) return NULL;

    retval = malloc (len);
    if (retval) {
	memmove( retval, src, len);
	*lenp = len;
    }
    return retval;
}
