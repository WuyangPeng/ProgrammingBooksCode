/* $XConsortium: XQueryDv.c,v 1.14 94/04/17 20:18:10 rws Exp $ */
/* $XFree86: xc/lib/Xi/XQueryDv.c,v 3.0 1996/08/25 13:52:59 dawes Exp $ */

/************************************************************

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

Copyright (c) 1989 by Hewlett-Packard Company, Palo Alto, California.

			All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the name of Hewlett-Packard not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.

HEWLETT-PACKARD DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
HEWLETT-PACKARD BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

********************************************************/

/***********************************************************************
 *
 * XQueryDeviceState - Query the state of an extension input device.
 *
 */

#include "XI.h"
#include "XIproto.h"
#include "Xlibint.h"
#include "XInput.h"
#include "extutil.h"
#include "XIint.h"

XDeviceState
*XQueryDeviceState (dpy, dev)
    register Display *dpy;
    XDevice *dev;
    {       
    int				i,j;
    int				rlen;
    int				size = 0;
    xQueryDeviceStateReq 	*req;
    xQueryDeviceStateReply 	rep;
    XDeviceState		*state = NULL;
    XInputClass			*any, *Any;
    char			*data;
    XExtDisplayInfo *info = XInput_find_display (dpy);

    LockDisplay (dpy);
    if (_XiCheckExtInit(dpy, XInput_Initial_Release) == -1)
	return ((XDeviceState *) NoSuchExtension);

    GetReq(QueryDeviceState,req);		
    req->reqType = info->codes->major_opcode;
    req->ReqType = X_QueryDeviceState;
    req->deviceid = dev->device_id;

    if (! _XReply (dpy, (xReply *) &rep, 0, xFalse)) 
	{
	UnlockDisplay(dpy);
	SyncHandle();
	return (XDeviceState *) NULL;
	}

    rlen = rep.length << 2;
    if (rlen > 0)
	{
	data = Xmalloc (rlen);
	if (!data)
	    {
	    _XEatData (dpy, (unsigned long) rlen);
    	    UnlockDisplay(dpy);
    	    SyncHandle();
    	    return ((XDeviceState *) NULL);
	    }
	_XRead (dpy, data, rlen);

	for (i=0, any=(XInputClass *) data; i<(int)rep.num_classes; i++)
	    {
	    switch (any->class)
		{
		case KeyClass:
		    size += sizeof (XKeyState);
		    break;
		case ButtonClass:
		    size += sizeof (XButtonState);
		    break;
		case ValuatorClass:
		    {
		    xValuatorState *v = (xValuatorState *) any;
		    size += (sizeof (XValuatorState) + 
			(v->num_valuators * sizeof(int)));
		    }
		    break;
		}
	    any = (XInputClass *) ((char *) any + any->length);
	    }
	state = (XDeviceState *) Xmalloc (size + sizeof(XDeviceState));
	if (!state)
	    {
    	    UnlockDisplay(dpy);
    	    SyncHandle();
    	    return ((XDeviceState *) NULL);
	    }
	state->device_id = dev->device_id;
	state->num_classes = rep.num_classes;
	state->data = (XInputClass *) (state + 1);

	Any = state->data; 
	for (i=0, any=(XInputClass *) data; i<(int)rep.num_classes; i++)
	    {
	    switch (any->class)
		{
		case KeyClass:
		    {
		    xKeyState *k = (xKeyState *) any;
		    XKeyState *K = (XKeyState *) Any;
		    K->class = k->class;
		    K->length = sizeof (XKeyState);
		    K->num_keys = k->num_keys;
		    memcpy ((char *) &K->keys[0], (char *) &k->keys[0], 32);
		    Any = (XInputClass *) (K+1);
		    }
		    break;
		case ButtonClass:
		    {
		    xButtonState *b = (xButtonState *) any;
		    XButtonState *B = (XButtonState *) Any;
		    B->class = b->class;
		    B->length = sizeof (XButtonState);
		    B->num_buttons = b->num_buttons;
		    memcpy ((char *) &B->buttons[0], (char *) &b->buttons[0],
			    32);
		    Any = (XInputClass *) (B+1);
		    }
		    break;
		case ValuatorClass:
		    {
		    xValuatorState *v = (xValuatorState *) any;
		    XValuatorState *V = (XValuatorState *) Any;
		    CARD32 *valuators = (CARD32 *) (v+1);
		    V->class = v->class;
		    V->length = sizeof (XValuatorState);
		    V->num_valuators = v->num_valuators;
		    V->mode = v->mode;
		    Any = (XInputClass *) (V+1);
		    V->valuators = (int *) Any;
		    for (j=0; j<(int)V->num_valuators; j++)
			*(V->valuators + j) = *valuators++;
		    Any = (XInputClass *)((char *) Any + 
			V->num_valuators * sizeof (int));
		    }
		    break;
		}
	    any = (XInputClass *) ((char *) any + any->length);
	    }
	Xfree(data);
	}

    UnlockDisplay(dpy);
    SyncHandle();
    return (state);
    }

XFreeDeviceState (list)
    XDeviceState *list;
    {
    XFree ((char *)list);
    }
