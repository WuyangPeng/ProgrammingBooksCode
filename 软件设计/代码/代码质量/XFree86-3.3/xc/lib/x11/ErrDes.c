/*
 * $XConsortium: ErrDes.c /main/41 1996/10/22 14:18:04 kaleb $
 * $XFree86: xc/lib/X11/ErrDes.c,v 3.4 1996/12/24 08:46:43 dawes Exp $
 */

/***********************************************************

Copyright (c) 1987, 1988  X Consortium

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


Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

#include "Xlibint.h"
#include <X11/Xos.h>
#include "Xresource.h"
#include <stdio.h>

#ifndef ERRORDB
#define ERRORDB "/usr/lib/X11/XErrorDB"
#endif

#ifdef __STDC__
#define Const const
#else
#define Const /**/
#endif

/*
 * descriptions of errors in Section 4 of Protocol doc (pp. 350-351); more
 * verbose descriptions are given in the error database
 */
static Const char * Const _XErrorList[] = {
    /* No error	*/		"no error",
    /* BadRequest */		"BadRequest",
    /* BadValue	*/		"BadValue",
    /* BadWindow */		"BadWindow",
    /* BadPixmap */		"BadPixmap",
    /* BadAtom */		"BadAtom",
    /* BadCursor */		"BadCursor",
    /* BadFont */		"BadFont",
    /* BadMatch	*/		"BadMatch",
    /* BadDrawable */		"BadDrawable",
    /* BadAccess */		"BadAccess",
    /* BadAlloc	*/		"BadAlloc",
    /* BadColor */  		"BadColor",
    /* BadGC */  		"BadGC",
    /* BadIDChoice */		"BadIDChoice",
    /* BadName */		"BadName",
    /* BadLength */		"BadLength",
    /* BadImplementation */	"BadImplementation",
};


XGetErrorText(dpy, code, buffer, nbytes)
    register int code;
    register Display *dpy;
    char *buffer;
    int nbytes;
{
    char buf[150];
    register _XExtension *ext;
    _XExtension *bext = (_XExtension *)NULL;

    if (nbytes == 0) return 0;
    if (code <= BadImplementation && code > 0) {
	sprintf(buf, "%d", code);
	(void) XGetErrorDatabaseText(dpy, "XProtoError", buf, _XErrorList[code],
				     buffer, nbytes);
    } else
	buffer[0] = '\0';
    /* call out to any extensions interested */
    for (ext = dpy->ext_procs; ext; ext = ext->next) {
 	if (ext->error_string)
 	    (*ext->error_string)(dpy, code, &ext->codes, buffer, nbytes);
	if (ext->codes.first_error &&
	    ext->codes.first_error < code &&
	    (!bext || ext->codes.first_error > bext->codes.first_error))
	    bext = ext;
    }    
    if (!buffer[0] && bext) {
	sprintf(buf, "%s.%d", bext->name, code - bext->codes.first_error);
	(void) XGetErrorDatabaseText(dpy, "XProtoError", buf, "", buffer, nbytes);
    }
    if (!buffer[0])
	sprintf(buffer, "%d", code);
    return 0;
}

#if NeedFunctionPrototypes
/*ARGSUSED*/
XGetErrorDatabaseText(
    Display *dpy,
    register _Xconst char *name,
    register _Xconst char *type,
    _Xconst char *defaultp,
    char *buffer,
    int nbytes)
#else
/*ARGSUSED*/
XGetErrorDatabaseText(dpy, name, type, defaultp, buffer, nbytes)
    Display *dpy;
    register char *name, *type;
    char *defaultp;
    char *buffer;
    int nbytes;
#endif
{

    static XrmDatabase db = NULL;
    XrmString type_str;
    XrmValue result;
    char temp[BUFSIZ];

    if (nbytes == 0) return 0;

    if (!db) {
	/* the Xrm routines expect to be called with the global
	   mutex unlocked. */
	XrmDatabase temp_db;
	int do_destroy;

	XrmInitialize();
	temp_db = XrmGetFileDatabase(ERRORDB);

	_XLockMutex(_Xglobal_lock);
	if (!db) {
	    db = temp_db;
	    do_destroy = 0;
	} else
	    do_destroy = 1;	/* we didn't need to get it after all */
	_XUnlockMutex(_Xglobal_lock);

	if (do_destroy)
	    XrmDestroyDatabase(temp_db);
    }

    if (db)
    {
	if (strlen(name) + 1 + strlen(type) + 1 <= BUFSIZ) {
	    sprintf(temp, "%s.%s", name, type);
	} else {
	    strncpy(temp, name, BUFSIZ);
	    temp[BUFSIZ - 1] = '\0';
	    if (strlen(name) + 2 < BUFSIZ) {
		strcat(temp, ".");
		strncat(temp, type, BUFSIZ - strlen(name) - 2);
	    }
	}
	XrmGetResource(db, temp, "ErrorType.ErrorNumber", &type_str, &result);
    }
    else
	result.addr = (XPointer)NULL;
    if (!result.addr) {
	result.addr = (XPointer) defaultp;
	result.size = strlen(defaultp) + 1;
    }
    (void) strncpy (buffer, (char *) result.addr, nbytes);
    if (result.size > nbytes) buffer[nbytes-1] = '\0';
    return 0;
}
