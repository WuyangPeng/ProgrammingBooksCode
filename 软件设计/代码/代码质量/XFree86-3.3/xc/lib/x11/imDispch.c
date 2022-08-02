/* $XConsortium: imDispch.c,v 1.4 94/03/26 16:57:53 rws Exp $ */
/******************************************************************

                Copyright 1993, 1994 by FUJITSU LIMITED

Permission to use, copy, modify, distribute, and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and
that both that copyright notice and this permission notice appear
in supporting documentation, and that the name of FUJITSU LIMITED
not be used in advertising or publicity pertaining to distribution
of the software without specific, written prior permission.
FUJITSU LIMITED makes no representations about the suitability of
this software for any purpose. 
It is provided "as is" without express or implied warranty.

FUJITSU LIMITED DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
EVENT SHALL FUJITSU LIMITED BE LIABLE FOR ANY SPECIAL, INDIRECT OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.

  Author: Takashi Fujiwara     FUJITSU LIMITED 
                               fujiwara@a80.tech.yk.fujitsu.co.jp

******************************************************************/

#include <X11/Xlib.h>
#include "Xlibint.h"
#include "Xutil.h"
#include "Xlcint.h"
#include "Ximint.h"

Public Bool
#if NeedFunctionPrototypes
_XimRegProtoIntrCallback(
    Xim		 im,
    CARD16	 major_code,
    CARD16	 minor_code,
    Bool	(*proc)(
#if NeedNestedPrototypes
                        Xim, INT16, XPointer, XPointer
#endif
			),

    XPointer	 call_data)
#else
_XimRegProtoIntrCallback(im, major_code, minor_code, proc, call_data)
    Xim		 im;
    CARD16	 major_code;
    CARD16	 minor_code;
    Bool	(*proc)();
    XPointer	 call_data;
#endif /* NeedFunctionPrototypes */
{
    XimProtoIntrRec    *rec;

    if (!(rec = (XimProtoIntrRec *)Xmalloc(sizeof(XimProtoIntrRec))))
        return False;
    rec->func       = proc;
    rec->major_code = major_code;
    rec->minor_code = minor_code;
    rec->call_data  = call_data;
    rec->next       = im->private.proto.intrproto;
    im->private.proto.intrproto = rec;
    return True;
}

Public void
_XimFreeProtoIntrCallback(im)
    Xim		im;
{
    register XimProtoIntrRec *rec, *next;

    for (rec = im->private.proto.intrproto; rec;) {
	next = rec->next;
	Xfree(rec);
	rec = next;
    }
    im->private.proto.intrproto = NULL;
    return;
}

Private Bool
#if NeedFunctionPrototypes
_XimTransportIntr(
    Xim		 im,
    INT16	 len,
    XPointer	 data,
    XPointer	 call_data)
#else
_XimTransportIntr(im, len, data, call_data)
    Xim		 im;
    INT16	 len;
    XPointer	 data;
    XPointer	 call_data;
#endif
{
    Xim			 call_im = (Xim)call_data;
    XimProtoIntrRec	*rec = call_im->private.proto.intrproto;
    CARD8		 major_opcode = *((CARD8 *)data);
    CARD8		 minor_opcode = *((CARD8 *)data + 1);

    for (; rec; rec = rec->next) {
	if ((major_opcode == (CARD8)rec->major_code)
	 && (minor_opcode == (CARD8)rec->minor_code))
	    if ((*rec->func)(call_im, len, data, rec->call_data))
		return True;
    }
    return False;
}

Public Bool
_XimDispatchInit(im)
    Xim		 im;
{
    if (_XimRegisterDispatcher(im, _XimTransportIntr, (XPointer)im))
	return True;
    return False;
}
