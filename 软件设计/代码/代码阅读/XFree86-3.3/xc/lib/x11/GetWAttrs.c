/* $XConsortium: GetWAttrs.c,v 11.26 94/04/17 20:19:45 rws Exp $ */
/*

Copyright (c) 1986  X Consortium

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

*/

#define NEED_REPLIES
#include "Xlibint.h"

typedef struct _WAttrsState {
    unsigned long attr_seq;
    unsigned long geom_seq;
    XWindowAttributes *attr;
} _XWAttrsState;

static Bool
_XWAttrsHandler(dpy, rep, buf, len, data)
    register Display *dpy;
    register xReply *rep;
    char *buf;
    int len;
    XPointer data;
{
    register _XWAttrsState *state;
    xGetWindowAttributesReply replbuf;
    register xGetWindowAttributesReply *repl;
    register XWindowAttributes *attr;

    state = (_XWAttrsState *)data;
    if (dpy->last_request_read != state->attr_seq) {
	if (dpy->last_request_read == state->geom_seq &&
	    !state->attr &&
	    rep->generic.type == X_Error &&
	    rep->error.errorCode == BadDrawable)
	    return True;
	return False;
    }
    if (rep->generic.type == X_Error) {
	state->attr = (XWindowAttributes *)NULL;
	return False;
    }
    repl = (xGetWindowAttributesReply *)
	_XGetAsyncReply(dpy, (char *)&replbuf, rep, buf, len,
		     (SIZEOF(xGetWindowAttributesReply) - SIZEOF(xReply)) >> 2,
			True);
    attr = state->attr;
    attr->class = repl->class;
    attr->bit_gravity = repl->bitGravity;
    attr->win_gravity = repl->winGravity;
    attr->backing_store = repl->backingStore;
    attr->backing_planes = repl->backingBitPlanes;
    attr->backing_pixel = repl->backingPixel;
    attr->save_under = repl->saveUnder;
    attr->colormap = repl->colormap;
    attr->map_installed = repl->mapInstalled;
    attr->map_state = repl->mapState;
    attr->all_event_masks = repl->allEventMasks;
    attr->your_event_mask = repl->yourEventMask;
    attr->do_not_propagate_mask = repl->doNotPropagateMask;
    attr->override_redirect = repl->override;
    attr->visual = _XVIDtoVisual (dpy, repl->visualID);
    return True;
}

Status XGetWindowAttributes(dpy, w, attr)
     register Display *dpy;
     Window w;
     XWindowAttributes *attr;
{       
    xGetGeometryReply rep;
    register xResourceReq *req;
    register int i;
    register Screen *sp;
    _XAsyncHandler async;
    _XWAttrsState async_state;
 
    LockDisplay(dpy);
    GetResReq(GetWindowAttributes, w, req);

    async_state.attr_seq = dpy->request;
    async_state.geom_seq = 0;
    async_state.attr = attr;
    async.next = dpy->async_handlers;
    async.handler = _XWAttrsHandler;
    async.data = (XPointer)&async_state;
    dpy->async_handlers = &async;

    GetResReq(GetGeometry, w, req);

    async_state.geom_seq = dpy->request;

    if (!_XReply (dpy, (xReply *)&rep, 0, xTrue)) {
	DeqAsyncHandler(dpy, &async);
	UnlockDisplay(dpy);
	SyncHandle();
	return (0);
	}
    DeqAsyncHandler(dpy, &async);
    if (!async_state.attr) {
	UnlockDisplay(dpy);
	SyncHandle();
	return (0);
    }
    attr->x = cvtINT16toInt (rep.x);
    attr->y = cvtINT16toInt (rep.y);
    attr->width = rep.width;
    attr->height = rep.height;
    attr->border_width = rep.borderWidth;
    attr->depth = rep.depth;
    attr->root = rep.root;
    /* find correct screen so that applications find it easier.... */
    for (i = 0; i < dpy->nscreens; i++) {
	sp = &dpy->screens[i];
	if (sp->root == attr->root) {
	    attr->screen = sp;
	    break;
	}
    }
    UnlockDisplay(dpy);
    SyncHandle();
    return(1);
}

