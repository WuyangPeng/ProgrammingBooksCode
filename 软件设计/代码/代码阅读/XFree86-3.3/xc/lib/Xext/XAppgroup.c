/*
Copyright (c) 1996  X Consortium

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from the X Consortium.
*/

/* $XConsortium: XAppgroup.c /main/3 1996/11/13 14:44:26 lehors $ */





/* $XFree86: xc/lib/Xext/XAppgroup.c,v 1.2 1996/12/26 01:37:43 dawes Exp $ */

#ifdef WIN32
#define BOOL wBOOL
#undef Status
#define Status wStatus
#include <windows.h>
#undef Status
#define Status int
#undef BOOL
#endif

#define NEED_EVENTS
#define NEED_REPLIES
#include "Xlibint.h"
#include "Xagstr.h"
#include "Xext.h"
#include "extutil.h"

#if NeedVarargsPrototypes
#define Va_start(a,b) va_start(a,b)
#else
#define Va_start(a,b) va_start(a)
#endif

struct xagstuff {
    int attrib_mask;
    Bool app_group_leader;
    Bool single_screen;
    Window default_root;
    VisualID root_visual;
    Colormap default_colormap;
    unsigned long black_pixel;
    unsigned long white_pixel;
};

static XExtensionInfo _xag_info_data;
static XExtensionInfo *xag_info = &_xag_info_data;
static char *xag_extension_name = XAGNAME;

#define XagCheckExtension(dpy,i,val) \
  XextCheckExtension (dpy, i, xag_extension_name, val)

/*****************************************************************************
 *                                                                           *
 *			   private utility routines                          *
 *                                                                           *
 *****************************************************************************/

static int close_display();
static /* const */ XExtensionHooks xag_extension_hooks = {
    NULL,				/* create_gc */
    NULL,				/* copy_gc */
    NULL,				/* flush_gc */
    NULL,				/* free_gc */
    NULL,				/* create_font */
    NULL,				/* free_font */
    close_display,			/* close_display */
    NULL,				/* wire_to_event */
    NULL,				/* event_to_wire */
    NULL,				/* error */
    NULL,				/* error_string */
};

static XEXT_GENERATE_FIND_DISPLAY (find_display, xag_info, 
				   xag_extension_name, 
				   &xag_extension_hooks, 
				   0, NULL)

static XEXT_GENERATE_CLOSE_DISPLAY (close_display, xag_info)


/*****************************************************************************
 *                                                                           *
 *		    public Xag Extension routines                            *
 *                                                                           *
 *****************************************************************************/

Bool
XagQueryVersion(dpy, major_version_return, minor_version_return)
    Display* dpy;
    int* major_version_return; 
    int* minor_version_return;
{
    XExtDisplayInfo *info = find_display (dpy);
    xXagQueryVersionReply rep;
    xXagQueryVersionReq *req;

    XagCheckExtension (dpy, info, False);

    LockDisplay(dpy);
    GetReq(XagQueryVersion, req);
    req->reqType = info->codes->major_opcode;
    req->xagReqType = X_XagQueryVersion;
    req->client_major_version = XAG_MAJOR_VERSION;
    req->client_minor_version = XAG_MINOR_VERSION;
    if (!_XReply(dpy, (xReply *)&rep, 0, xTrue)) {
	UnlockDisplay(dpy);
	SyncHandle();
	return False;
    }
    *major_version_return = rep.server_major_version;
    *minor_version_return = rep.server_minor_version;
    UnlockDisplay(dpy);
    SyncHandle();
    return True;
}

static void
StuffToWire (dpy, stuff, req)
    Display* dpy;
    struct xagstuff* stuff;
    xXagCreateReq* req;
{
    unsigned long values[8];
    unsigned long* value = values;
    unsigned int nvalues;

    /* the order these are in is important */
    if (stuff->attrib_mask & XagSingleScreenMask)
	*value++ = stuff->single_screen;

    if (stuff->attrib_mask & XagDefaultRootMask)
	*value++ = stuff->default_root;

    if (stuff->attrib_mask & XagRootVisualMask)
	*value++ = stuff->root_visual;

    if (stuff->attrib_mask & XagDefaultColormapMask)
	*value++ = stuff->default_colormap;

    if (stuff->attrib_mask & XagBlackPixelMask)
	*value++ = stuff->black_pixel;

    if (stuff->attrib_mask & XagWhitePixelMask)
	*value++ = stuff->white_pixel;

    if (stuff->attrib_mask & XagAppGroupLeaderMask)
	*value++ = stuff->app_group_leader;

    req->length += (nvalues = value - values);

    nvalues <<= 2;
    Data32 (dpy, (long*) values, (long) nvalues);
}

Bool 
#if NeedVarargsPrototypes
XagCreateEmbeddedApplicationGroup(
    Display* dpy,
    VisualID root_visual,
    Colormap default_colormap,
    unsigned long black_pixel,
    unsigned long white_pixel,
    XAppGroup* app_group_return)
#else
XagCreateEmbeddedApplicationGroup(dpy, root_visual, default_colormap, black_pixel, white_pixel, app_group_return)
    Display* dpy;
    VisualID root_visual;
    Colormap default_colormap;
    unsigned long black_pixel, white_pixel;
    XAppGroup* app_group_return;
#endif
{
    va_list var;
    XExtDisplayInfo *info = find_display (dpy);
    xXagCreateReq *req;
    struct xagstuff stuff;

    XagCheckExtension (dpy, info, False);

    LockDisplay(dpy);
    stuff.app_group_leader = True;
    stuff.single_screen = True;
    stuff.default_root = RootWindow (dpy, DefaultScreen(dpy));
    stuff.root_visual = root_visual;
    stuff.default_colormap = default_colormap;
    stuff.attrib_mask = 
	XagAppGroupLeaderMask | XagSingleScreenMask | XagDefaultRootMask |
	XagRootVisualMask | XagDefaultColormapMask;
    if (default_colormap != None) {
	stuff.black_pixel = black_pixel;
	stuff.white_pixel = white_pixel;
	stuff.attrib_mask |= XagBlackPixelMask | XagWhitePixelMask;
    }
    /* might do some validation here */
    GetReq(XagCreate, req);
    req->reqType = info->codes->major_opcode;
    req->xagReqType = X_XagCreate;
    *app_group_return = req->app_group = XAllocID(dpy);
    req->attrib_mask = stuff.attrib_mask;
    StuffToWire (dpy, &stuff, req);
    UnlockDisplay(dpy);
    SyncHandle();
    return True;
}

Bool 
#if NeedVarargsPrototypes
XagCreateNonembeddedApplicationGroup(
    Display* dpy,
    XAppGroup* app_group_return)
#else
XagCreateNonembeddedApplicationGroup(dpy, app_group_return)
    Display* dpy;
    XAppGroup* app_group_return;
#endif
{
    va_list var;
    XExtDisplayInfo *info = find_display (dpy);
    xXagCreateReq *req;
    struct xagstuff stuff;
    unsigned long values[8];
    unsigned long* value = values;

    XagCheckExtension (dpy, info, False);

    LockDisplay(dpy);
    stuff.app_group_leader = False;
    stuff.single_screen = False;
    stuff.attrib_mask = XagAppGroupLeaderMask | XagSingleScreenMask;
    /* might do some validation here */
    GetReq(XagCreate, req);
    req->reqType = info->codes->major_opcode;
    req->xagReqType = X_XagCreate;
    *app_group_return = req->app_group = XAllocID(dpy);
    req->attrib_mask = stuff.attrib_mask;
    StuffToWire (dpy, &stuff, req);
    UnlockDisplay(dpy);
    SyncHandle();
    return True;
}

Bool XagDestroyApplicationGroup(dpy,app_group)
    Display* dpy;
    XAppGroup app_group;
{
    XExtDisplayInfo *info = find_display (dpy);
    xXagDestroyReq *req;

    XagCheckExtension (dpy, info, False);

    LockDisplay(dpy);
    GetReq(XagDestroy, req);
    req->reqType = info->codes->major_opcode;
    req->xagReqType = X_XagDestroy;
    req->app_group = app_group;
    UnlockDisplay(dpy);
    SyncHandle();
    return True;
}

Bool
#if NeedVarargsPrototypes
XagGetApplicationGroupAttributes(
    Display* dpy,
    XAppGroup app_group,
    ...)
#else
XagGetApplicationGroupAttributes(dpy, app_group, va_alist)
    Display* dpy;
    XAppGroup app_group;
    va_dcl
#endif
{
    va_list var;
    XExtDisplayInfo *info = find_display (dpy);
    xXagGetAttrReq *req;
    xXagGetAttrReply rep;
    int attr;

    XagCheckExtension (dpy, info, False);

    LockDisplay(dpy);
    GetReq(XagGetAttr, req);
    req->reqType = info->codes->major_opcode;
    req->xagReqType = X_XagGetAttr;
    req->app_group = app_group;
    if (!_XReply(dpy, (xReply *)&rep, 0, xFalse)) {
	UnlockDisplay(dpy);
	SyncHandle();
	return False;
    }
    Va_start (var, app_group);
    for (attr = va_arg(var, int); attr != 0; attr = va_arg(var, int)) {
	void* ptr;

	switch (attr) {
	case XagNappGroupLeader:
	    ptr = va_arg(var, void*);
	    *(Bool*)ptr = rep.app_group_leader;
	    break;
	case XagNsingleScreen:
	    ptr = va_arg(var, void*);
	    *(Bool*)ptr = rep.single_screen;
	    break;
	case XagNdefaultRoot:
	    ptr = va_arg(var, void*);
	    *(Window*)ptr = rep.default_root;
	    break;
	case XagNrootVisual:
	    ptr = va_arg(var, void*);
	    *(VisualID*)ptr = rep.root_visual;
	    break;
	case XagNdefaultColormap:
	    ptr = va_arg(var, void*);
	    *(Colormap*)ptr = rep.default_colormap;
	    break;
	case XagNblackPixel:
	    ptr = va_arg(var, void*);
	    *(unsigned long*)ptr = rep.black_pixel;
	    break;
	case XagNwhitePixel:
	    ptr = va_arg(var, void*);
	    *(unsigned long*)ptr = rep.white_pixel;
	    break;
	}
    }
    va_end (var);
    UnlockDisplay(dpy);
    SyncHandle();
    return True;
}

Bool
XagQueryApplicationGroup(dpy, resource, app_group_return)
    Display* dpy;
    XID resource;
    XAppGroup* app_group_return;
{
    XExtDisplayInfo *info = find_display (dpy);
    xXagQueryReq *req;
    xXagQueryReply rep;

    XagCheckExtension (dpy, info, False);

    LockDisplay(dpy);
    GetReq(XagQuery, req);
    req->reqType = info->codes->major_opcode;
    req->xagReqType = X_XagQuery;
    req->resource = resource;
    if (!_XReply(dpy, (xReply *)&rep, 0, xFalse)) {
	UnlockDisplay(dpy);
	SyncHandle();
	return False;
    }
    *app_group_return = rep.app_group;
    UnlockDisplay(dpy);
    SyncHandle();
    return True;

}

Bool
XagCreateAssociation(dpy, window_return, system_window)
    Display* dpy;
    Window* window_return;
    void* system_window;
{
#ifdef WIN32
    long tmp = *(HWND*) system_window;
    XExtDisplayInfo *info = find_display (dpy);
    xXagCreateAssocReq *req;

    XagCheckExtension (dpy, info, False);

    LockDisplay(dpy);
    GetReq(XagCreateAssoc, req);
    req->reqType = info->codes->major_opcode;
    req->xagReqType = X_XagCreateAssoc;
    *window_return = req->window = XAllocID(dpy);
    req->window_type = XagWindowTypeWin32;
    req->system_window_len = sizeof(HWND);
    Data32 (dpy, (long*) tmp, 1L);
    req->length++;
    UnlockDisplay(dpy);
    SyncHandle();
#else
    /* other platforms go here */

    /* this whole thing could be arranged better, but since X need
     * only short-circuit the protocol and WIN32 is the only other 
     * platform the XC supports, it will suffice for now.
     */
    *window_return = *(Window*)system_window;
#endif
    return True;
}

Bool
XagDestroyAssociation(dpy, window)
    Display* dpy;
    Window window;
{
#ifdef WIN32
    XExtDisplayInfo *info = find_display (dpy);
    xXagDestroyAssocReq *req;

    XagCheckExtension (dpy, info, False);

    LockDisplay(dpy);
    GetReq(XagDestroyAssoc, req);
    req->reqType = info->codes->major_opcode;
    req->xagReqType = X_XagDestroyAssoc;
    req->window = window;
    UnlockDisplay(dpy);
    SyncHandle();
#endif
    return True;
}

