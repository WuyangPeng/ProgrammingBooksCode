/*
 * $XConsortium: extutil.c /main/19 1996/09/24 22:33:20 dpw $
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
 *
 * Author:  Jim Fulton, MIT X Consortium
 *
 * 
 * 		       Xlib Extension-Writing Utilities
 * 
 * This package contains utilities for writing the client API for various
 * protocol extensions.  THESE INTERFACES ARE NOT PART OF THE X STANDARD AND
 * ARE SUBJECT TO CHANGE!
 * 
 *  Routines include:
 * 
 *         XextCreateExtension		called once per extension
 *         XextDestroyExtension		if no longer using extension
 *         XextAddDisplay		add another display
 *         XextRemoveDisplay		remove a display
 *         XextFindDisplay		is a display open
 * 
 * In addition, the following Xlib-style interfaces are provided:
 * 
 *         XSetExtensionErrorHandler	establish an extension error handler
 *         XMissingExtension		raise an error about missing ext
 */

#include <stdio.h>
#include "Xlibint.h"
#include "Xext.h"
#include "extutil.h"


/*
 * XextCreateExtension - return an extension descriptor containing context
 * information for this extension.  This object is passed to all Xext 
 * routines.
 */
XExtensionInfo *XextCreateExtension ()
{
    register XExtensionInfo *info =
      (XExtensionInfo *) Xmalloc (sizeof (XExtensionInfo));

    if (info) {
	info->head = NULL;
	info->cur = NULL;
	info->ndisplays = 0;
    }
    return info;
}


/*
 * XextDestroyExtension - free memory the given extension descriptor
 */
void XextDestroyExtension (info)
    XExtensionInfo *info;
{
    info->head = NULL;			/* to catch refs after this */
    info->cur = NULL;
    info->ndisplays = 0;
    XFree ((char *) info);
}



/*
 * XextAddDisplay - add a display to this extension
 */
XExtDisplayInfo *XextAddDisplay (extinfo, dpy, ext_name, hooks, nevents, data)
    XExtensionInfo *extinfo;
    Display *dpy;
    char *ext_name;
    XExtensionHooks *hooks;
    int nevents;
    XPointer data;
{
    XExtDisplayInfo *dpyinfo;

    dpyinfo = (XExtDisplayInfo *) Xmalloc (sizeof (XExtDisplayInfo));
    if (!dpyinfo) return NULL;
    dpyinfo->display = dpy;
    dpyinfo->data = data;
    dpyinfo->codes = XInitExtension (dpy, ext_name);

    /*
     * if the server has the extension, then we can initialize the 
     * appropriate function vectors
     */
    if (dpyinfo->codes) {
	int i, j;

	for (i = 0, j = dpyinfo->codes->first_event; i < nevents; i++, j++) {
	    XESetWireToEvent (dpy, j, hooks->wire_to_event);
	    XESetEventToWire (dpy, j, hooks->event_to_wire);
	}
	if (hooks->create_gc)
	  XESetCreateGC (dpy, dpyinfo->codes->extension, hooks->create_gc);
	if (hooks->copy_gc)
	  XESetCopyGC (dpy, dpyinfo->codes->extension, hooks->copy_gc);
	if (hooks->flush_gc)
	  XESetFlushGC (dpy, dpyinfo->codes->extension, hooks->flush_gc);
	if (hooks->free_gc)
	  XESetFreeGC (dpy, dpyinfo->codes->extension, hooks->free_gc);
	if (hooks->create_font)
	  XESetCreateFont (dpy, dpyinfo->codes->extension, hooks->create_font);
	if (hooks->free_font)
	  XESetFreeFont (dpy, dpyinfo->codes->extension, hooks->free_font);
	if (hooks->close_display)
	  XESetCloseDisplay (dpy, dpyinfo->codes->extension, 
			     hooks->close_display);
	if (hooks->error)
	  XESetError (dpy, dpyinfo->codes->extension, hooks->error);
	if (hooks->error_string)
	  XESetErrorString (dpy, dpyinfo->codes->extension,
			    hooks->error_string);
    } else if (hooks->close_display) {
	/* The server doesn't have this extension.
	 * Use a private Xlib-internal extension to hang the close_display
	 * hook on so that the "cache" (extinfo->cur) is properly cleaned.
	 * (XBUG 7955)
	 */
	XExtCodes *codes = XAddExtension(dpy);
	if (!codes) {
	    XFree(dpyinfo);
	    return NULL;
	}
	XESetCloseDisplay (dpy, codes->extension, hooks->close_display);
    }

    /*
     * now, chain it onto the list
     */
    _XLockMutex(_Xglobal_lock);
    dpyinfo->next = extinfo->head;
    extinfo->head = dpyinfo;
    extinfo->cur = dpyinfo;
    extinfo->ndisplays++;
    _XUnlockMutex(_Xglobal_lock);
    return dpyinfo;
}


/*
 * XextRemoveDisplay - remove the indicated display from the extension object
 */
int XextRemoveDisplay (extinfo, dpy)
    XExtensionInfo *extinfo;
    Display *dpy;
{
    XExtDisplayInfo *dpyinfo, *prev;

    /*
     * locate this display and its back link so that it can be removed
     */
    _XLockMutex(_Xglobal_lock);
    prev = NULL;
    for (dpyinfo = extinfo->head; dpyinfo; dpyinfo = dpyinfo->next) {
	if (dpyinfo->display == dpy) break;
	prev = dpyinfo;
    }
    if (!dpyinfo) {
	_XUnlockMutex(_Xglobal_lock);
	return 0;		/* hmm, actually an error */
    }

    /*
     * remove the display from the list; handles going to zero
     */
    if (prev)
	prev->next = dpyinfo->next;
    else
	extinfo->head = dpyinfo->next;

    extinfo->ndisplays--;
    if (dpyinfo == extinfo->cur) extinfo->cur = NULL;  /* flush cache */
    _XUnlockMutex(_Xglobal_lock);

    Xfree ((char *) dpyinfo);
    return 1;
}


/*
 * XextFindDisplay - look for a display in this extension; keeps a cache
 * of the most-recently used for efficiency.
 */
XExtDisplayInfo *XextFindDisplay (extinfo, dpy)
    XExtensionInfo *extinfo;
    Display *dpy;
{
    register XExtDisplayInfo *dpyinfo;

    /*
     * see if this was the most recently accessed display
     */
    if ((dpyinfo = extinfo->cur)&& dpyinfo->display == dpy) return dpyinfo;


    /*
     * look for display in list
     */
    _XLockMutex(_Xglobal_lock);
    for (dpyinfo = extinfo->head; dpyinfo; dpyinfo = dpyinfo->next) {
	if (dpyinfo->display == dpy) {
	    extinfo->cur = dpyinfo;	/* cache most recently used */
	    _XUnlockMutex(_Xglobal_lock);
	    return dpyinfo;
	}
    }
    _XUnlockMutex(_Xglobal_lock);

    return NULL;
}



static int _default_exterror (dpy, ext_name, reason)
    Display *dpy;
    char *ext_name;
    char *reason;
{
    fprintf (stderr, "Xlib:  extension \"%s\" %s on display \"%s\".\n",
	     ext_name, reason, DisplayString(dpy));
    return 0;
}


/*
 * XSetExtensionErrorHandler - sets the handler that gets called when a 
 * requested extension is referenced.  This should eventually move into Xlib.
 */

extern int (*_XExtensionErrorFunction)();

#if NeedFunctionPrototypes
int (*XSetExtensionErrorHandler(
    int (*handler)(
#if NeedNestedPrototypes
		   Display*,
		   char *,
		   char *
#endif
		   )
))()
#else
int (*XSetExtensionErrorHandler(handler))()
    int (*handler)();
#endif
{
    int (*oldhandler)() = _XExtensionErrorFunction;

    _XExtensionErrorFunction = (handler ? handler :
				_default_exterror);
    return oldhandler;
}


/*
 * XMissingExtension - call the extension error handler
 */
#if NeedFunctionPrototypes
int XMissingExtension (
    Display *dpy,
    _Xconst char *ext_name)
#else
int XMissingExtension (dpy, ext_name)
    Display *dpy;
    char *ext_name;
#endif
{
    int (*func)() = (_XExtensionErrorFunction ?
		     _XExtensionErrorFunction : _default_exterror);

    if (!ext_name) ext_name = X_EXTENSION_UNKNOWN;
    return (*func) (dpy, ext_name, X_EXTENSION_MISSING);
}
