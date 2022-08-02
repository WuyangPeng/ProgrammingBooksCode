/*	$NetBSD: localhostname.c,v 1.4 1997/10/13 03:42:27 lukem Exp $	*/

/*-
 * Copyright (c) 1996 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Jason R. Thorpe.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#ifndef lint
__RCSID("$NetBSD: localhostname.c,v 1.4 1997/10/13 03:42:27 lukem Exp $");
#endif

#include <sys/types.h>
#include <err.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "protos.h"

void
localhostname(buf, buflen)
	char *buf;
	size_t buflen;
{
	struct hostent *hp;
	char hostname[MAXHOSTNAMELEN];
	int i;

	if (gethostname(hostname, sizeof(hostname)))
		err(1, "gethostname");

	memset(buf, 0, buflen);

	/*
	 * If hostname appears to be fully-qualified,
	 * just return it.
	 */
	if (strchr(hostname, '.')) {
		snprintf(buf, buflen, "%s", hostname);
		return;
	}

	/*
	 * Lookup the host.  Return the first name that appears
	 * to be fully-qualified.
	 */
	hp = gethostbyname(hostname);
	if (hp == NULL)
		errx(1, "gethostbyname(%s) failed", hostname);

	if (strchr(hp->h_name, '.')) {
		snprintf(buf, buflen, "%s", hp->h_name);
		return;
	}

	if (hp->h_aliases != NULL && hp->h_aliases[0] != NULL) {
		for (i = 0; hp->h_aliases[i] != NULL; i++) {
			if (strchr(hp->h_aliases[i], '.')) {
				snprintf(buf, buflen, "%s", hp->h_aliases[i]);
				return;
			}
		}
	}

	/*
	 * As a last resort, just return hostname.
	 */
	snprintf(buf, buflen, "%s", hostname);
}
