/* $TOG: Callback.c /main/46 1997/05/15 17:28:16 kaleb $ */

/***********************************************************
Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts,
Copyright 1993 by Sun Microsystems, Inc. Mountain View, CA.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Digital or Sun not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

SUN DISCLAIMS ALL WARRANTIES WITH REGARD TO  THIS  SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FIT-
NESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL SUN BE  LI-
ABLE  FOR  ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,  DATA  OR
PROFITS,  WHETHER  IN  AN  ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
THE USE OR PERFORMANCE OF THIS SOFTWARE.

******************************************************************/

/*

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

*/

#include "IntrinsicI.h"

static String XtNinvalidCallbackList = "invalidCallbackList";
static String XtNxtAddCallback = "xtAddCallback";
static String XtNxtRemoveCallback = "xtRemoveCallback";
static String XtNxtRemoveAllCallback = "xtRemoveAllCallback";
static String XtNxtCallCallback = "xtCallCallback";

/* However it doesn't contain a final NULL record */
#define ToList(p) ((XtCallbackList) ((p)+1))

static InternalCallbackList* FetchInternalList(widget, name)
    Widget	widget;
    String	name;
{
    XrmQuark quark;
    int n;
    CallbackTable offsets;
    InternalCallbackList* retval = NULL;

    quark = StringToQuark(name);
    LOCK_PROCESS;
    offsets = (CallbackTable) 
	widget->core.widget_class->core_class.callback_private;

    for (n = (int) *(offsets++); --n >= 0; offsets++)
	if (quark == (*offsets)->xrm_name) {
	    retval = (InternalCallbackList *) 
		((char *) widget - (*offsets)->xrm_offset - 1);
	    break;
	}
    UNLOCK_PROCESS;
    return retval;
}


void _XtAddCallback(callbacks, callback, closure)
    InternalCallbackList*   callbacks;
    XtCallbackProc	    callback;
    XtPointer		    closure;
{
    register InternalCallbackList icl;
    register XtCallbackList cl;
    register int count;
    
    icl = *callbacks;
    count = icl ? icl->count : 0;

    if (icl && icl->call_state) {
	icl->call_state |= _XtCBFreeAfterCalling;
	icl = (InternalCallbackList)
	    __XtMalloc(sizeof(InternalCallbackRec) +
		     sizeof(XtCallbackRec) * (count + 1));
	(void) memmove((char *)ToList(icl), (char *)ToList(*callbacks),
		       sizeof(XtCallbackRec) * count);
    } else {
	icl = (InternalCallbackList)
	    XtRealloc((char *) icl, sizeof(InternalCallbackRec) +
		      sizeof(XtCallbackRec) * (count + 1));
    }
    *callbacks = icl;
    icl->count = count + 1;
    icl->is_padded = 0;
    icl->call_state = 0;
    cl = ToList(icl) + count;
    cl->callback = callback;
    cl->closure = closure;
} /* _XtAddCallback */

void _XtAddCallbackOnce(callbacks, callback, closure)
    register InternalCallbackList*callbacks;
    XtCallbackProc	    callback;
    XtPointer		    closure;
{
    register XtCallbackList cl = ToList(*callbacks);
    register int i;
    
    for (i=(*callbacks)->count; --i >= 0; cl++)
	if (cl->callback == callback && cl->closure == closure)
	    return;

    _XtAddCallback(callbacks, callback, closure);
} /* _XtAddCallbackOnce */

#if NeedFunctionPrototypes
void XtAddCallback(
    Widget	    widget,
    _Xconst char*   name,
    XtCallbackProc  callback,
    XtPointer	    closure
    )
#else
void XtAddCallback(widget, name, callback, closure)
    Widget	    widget;
    String	    name;
    XtCallbackProc  callback;
    XtPointer	    closure;
#endif
{
    InternalCallbackList *callbacks;
    Widget hookobj;
    XtAppContext app = XtWidgetToApplicationContext(widget);

    LOCK_APP(app);
    callbacks = FetchInternalList(widget, name);
    if (!callbacks) {
	XtAppWarningMsg(app,
	       XtNinvalidCallbackList,XtNxtAddCallback,XtCXtToolkitError,
              "Cannot find callback list in XtAddCallback",
	      (String *)NULL, (Cardinal *)NULL);
	UNLOCK_APP(app);
	return;
    }
    _XtAddCallback(callbacks, callback, closure);
    if (!_XtIsHookObject(widget)) {
	hookobj = XtHooksOfDisplay(XtDisplayOfObject(widget));
	if (XtHasCallbacks(hookobj, XtNchangeHook) == XtCallbackHasSome) {
	    XtChangeHookDataRec call_data;

	    call_data.type = XtHaddCallback;
	    call_data.widget = widget;
	    call_data.event_data = (XtPointer) name;
	    XtCallCallbackList(hookobj, 
		((HookObject)hookobj)->hooks.changehook_callbacks, 
		(XtPointer)&call_data);
	}
    }
    UNLOCK_APP(app);
} /* XtAddCallback */

/* ARGSUSED */
static void AddCallbacks(widget, callbacks, newcallbacks)
    Widget		    widget;
    InternalCallbackList   *callbacks;
    XtCallbackList	    newcallbacks;
{
    register InternalCallbackList icl;
    register int i, j;
    register XtCallbackList cl;

    icl = *callbacks;
    i = icl ? icl->count : 0;
    for (j=0, cl = newcallbacks; cl->callback; cl++, j++);
    if (icl && icl->call_state) {
	icl->call_state |= _XtCBFreeAfterCalling;
	icl = (InternalCallbackList) __XtMalloc(sizeof(InternalCallbackRec) +
					      sizeof(XtCallbackRec) * (i+j));
	(void) memmove((char *)ToList(*callbacks), (char *)ToList(icl), 
		       sizeof(XtCallbackRec) * i);
    } else {
	icl = (InternalCallbackList) XtRealloc((char *) icl,
					       sizeof(InternalCallbackRec) + 
					       sizeof(XtCallbackRec) * (i+j));
    }
    *callbacks = icl;
    icl->count = i+j;
    icl->is_padded = 0;
    icl->call_state = 0;
    for (cl = ToList(icl) + i; --j >= 0; )
	*cl++ = *newcallbacks++;
} /* AddCallbacks */

#if NeedFunctionPrototypes
void XtAddCallbacks(
    Widget	    widget,
    _Xconst char*   name,
    XtCallbackList  xtcallbacks
    )
#else
void XtAddCallbacks(widget, name, xtcallbacks)
    Widget	    widget;
    String	    name;
    XtCallbackList  xtcallbacks;
#endif
{
    InternalCallbackList* callbacks;
    Widget hookobj;
    XtAppContext app = XtWidgetToApplicationContext(widget);

    LOCK_APP(app);
    callbacks = FetchInternalList(widget, name);
    if (!callbacks) {
	XtAppWarningMsg(app,
	       XtNinvalidCallbackList,XtNxtAddCallback,XtCXtToolkitError,
              "Cannot find callback list in XtAddCallbacks",
	      (String *)NULL, (Cardinal *)NULL);
	UNLOCK_APP(app);
	return;
    }
    AddCallbacks(widget, callbacks, xtcallbacks);
    hookobj = XtHooksOfDisplay(XtDisplayOfObject(widget));
    if (XtHasCallbacks(hookobj, XtNchangeHook) == XtCallbackHasSome) {
	XtChangeHookDataRec call_data;

	call_data.type = XtHaddCallbacks;
	call_data.widget = widget;
	call_data.event_data = (XtPointer) name;
	XtCallCallbackList(hookobj, 
		((HookObject)hookobj)->hooks.changehook_callbacks, 
		(XtPointer)&call_data);
    }
    UNLOCK_APP(app);
} /* XtAddCallbacks */

void _XtRemoveCallback (callbacks, callback, closure)
    InternalCallbackList   *callbacks;
    XtCallbackProc	    callback;
    XtPointer		    closure;

{
    register InternalCallbackList icl;
    register int i, j;
    register XtCallbackList cl, ncl, ocl;

    icl = *callbacks;
    if (!icl) return;

    cl = ToList(icl);
    for (i=icl->count; --i >= 0; cl++) {
	if (cl->callback == callback && cl->closure == closure) {
	    if (icl->call_state) {
		icl->call_state |= _XtCBFreeAfterCalling;
		if (icl->count == 1) {
		    *callbacks = NULL;
		} else {
		    j = icl->count - i - 1;
		    ocl = ToList(icl);
		    icl = (InternalCallbackList)
			__XtMalloc(sizeof(InternalCallbackRec) +
				 sizeof(XtCallbackRec) * (i + j));
		    icl->count = i + j;
		    icl->is_padded = 0;
		    icl->call_state = 0;
		    ncl = ToList(icl);
		    while (--j >= 0)
			*ncl++ = *ocl++;
		    while (--i >= 0)
			*ncl++ = *++cl;
		    *callbacks = icl;
		}
	    } else {
		if (--icl->count) {
		    ncl = cl + 1;
		    while (--i >= 0)
			*cl++ = *ncl++;
		    icl = (InternalCallbackList)
			XtRealloc((char *) icl, sizeof(InternalCallbackRec)
				  + sizeof(XtCallbackRec) * icl->count);
		    icl->is_padded = 0;
		    *callbacks = icl;
		} else {
		    XtFree((char *) icl);
		    *callbacks = NULL;
		}
	    }
	    return;
	}
    }
} /* _XtRemoveCallback */

#if NeedFunctionPrototypes
void XtRemoveCallback (
    Widget	    widget,
    _Xconst char*   name,
    XtCallbackProc  callback,
    XtPointer	    closure
    )
#else
void XtRemoveCallback (widget, name, callback, closure)
    Widget	    widget;
    String	    name;
    XtCallbackProc  callback;
    XtPointer	    closure;
#endif
{
    InternalCallbackList *callbacks;
    Widget hookobj;
    XtAppContext app = XtWidgetToApplicationContext(widget);

    LOCK_APP(app);
    callbacks = FetchInternalList(widget, name);
    if (!callbacks) {
	XtAppWarningMsg(app,
	       XtNinvalidCallbackList,XtNxtRemoveCallback,XtCXtToolkitError,
              "Cannot find callback list in XtRemoveCallback",
	      (String *)NULL, (Cardinal *)NULL);
	UNLOCK_APP(app);
	return;
    }
    _XtRemoveCallback(callbacks, callback, closure);
    hookobj = XtHooksOfDisplay(XtDisplayOfObject(widget));
    if (XtHasCallbacks(hookobj, XtNchangeHook) == XtCallbackHasSome) {
	XtChangeHookDataRec call_data;

	call_data.type = XtHremoveCallback;
	call_data.widget = widget;
	call_data.event_data = (XtPointer) name;
	XtCallCallbackList(hookobj, 
		((HookObject)hookobj)->hooks.changehook_callbacks, 
		(XtPointer)&call_data);
    }
    UNLOCK_APP(app);
} /* XtRemoveCallback */


#if NeedFunctionPrototypes
void XtRemoveCallbacks (widget, name, xtcallbacks)
    Widget	    widget;
    _Xconst char*   name;
    XtCallbackList  xtcallbacks;
#else
void XtRemoveCallbacks (widget, name, xtcallbacks)
    Widget	    widget;
    String	    name;
    XtCallbackList  xtcallbacks;
#endif
{
    InternalCallbackList *callbacks;
    Widget hookobj;
    int i;
    InternalCallbackList icl;
    XtCallbackList cl, ccl, rcl;
    XtAppContext app = XtWidgetToApplicationContext(widget);

    LOCK_APP(app);
    callbacks = FetchInternalList(widget, name);
    if (!callbacks) {
	XtAppWarningMsg(app,
	       XtNinvalidCallbackList,XtNxtRemoveCallback,XtCXtToolkitError,
              "Cannot find callback list in XtRemoveCallbacks",
	      (String *)NULL, (Cardinal *)NULL);
	UNLOCK_APP(app);
	return;
    }

    icl = *callbacks;
    if (!icl) {
	UNLOCK_APP(app);
	return;
    }

    i = icl->count;
    cl = ToList(icl);
    if (icl->call_state) {
	icl->call_state |= _XtCBFreeAfterCalling;
	icl = (InternalCallbackList)__XtMalloc(sizeof(InternalCallbackRec) +
					     sizeof(XtCallbackRec) * i);
	icl->count = i;
	icl->call_state = 0;
    }
    ccl = ToList(icl);
    while (--i >= 0) {
	*ccl++ = *cl;
	for (rcl=xtcallbacks; rcl->callback; rcl++) {
	    if (cl->callback == rcl->callback && cl->closure == rcl->closure) {
		ccl--;
		icl->count--;
		break;
	    }
	}
	cl++;
    }
    if (icl->count) {
	icl = (InternalCallbackList)
	    XtRealloc((char *)icl, (sizeof(InternalCallbackRec) +
				    sizeof(XtCallbackRec) * icl->count));
	icl->is_padded = 0;
	*callbacks = icl;
    } else {
	XtFree((char *)icl);
	*callbacks = NULL;
    }
    hookobj = XtHooksOfDisplay(XtDisplayOfObject(widget));
    if (XtHasCallbacks(hookobj, XtNchangeHook) == XtCallbackHasSome) {
	XtChangeHookDataRec call_data;

	call_data.type = XtHremoveCallbacks;
	call_data.widget = widget;
	call_data.event_data = (XtPointer) name;
	XtCallCallbackList(hookobj, 
		((HookObject)hookobj)->hooks.changehook_callbacks, 
		(XtPointer)&call_data);
    }
    UNLOCK_APP(app);
} /* XtRemoveCallbacks */


void _XtRemoveAllCallbacks (callbacks)
    InternalCallbackList *callbacks;
{
    register InternalCallbackList icl = *callbacks;

    if (icl) {
	if (icl->call_state)
	    icl->call_state |= _XtCBFreeAfterCalling;
	else
	    XtFree((char *) icl);
	*callbacks = NULL;
    }
} /* _XtRemoveAllCallbacks */

#if NeedFunctionPrototypes
void XtRemoveAllCallbacks(widget, name)
    Widget widget;
    _Xconst char* name;
#else
void XtRemoveAllCallbacks(widget, name)
    Widget widget;
    String name;
#endif
{
    InternalCallbackList *callbacks;
    Widget hookobj;
    XtAppContext app = XtWidgetToApplicationContext(widget);

    LOCK_APP(app);
    callbacks = FetchInternalList(widget, name);
    if (!callbacks) {
	XtAppWarningMsg(app,
	       XtNinvalidCallbackList,XtNxtRemoveAllCallback,XtCXtToolkitError,
              "Cannot find callback list in XtRemoveAllCallbacks",
	      (String *)NULL, (Cardinal *)NULL);
	UNLOCK_APP(app);
	return;
    }
    _XtRemoveAllCallbacks(callbacks);
    hookobj = XtHooksOfDisplay(XtDisplayOfObject(widget));
    if (XtHasCallbacks(hookobj, XtNchangeHook) == XtCallbackHasSome) {
	XtChangeHookDataRec call_data;

	call_data.type = XtHremoveAllCallbacks;
	call_data.widget = widget;
	call_data.event_data = (XtPointer) name;
	XtCallCallbackList(hookobj, 
		((HookObject)hookobj)->hooks.changehook_callbacks, 
		(XtPointer)&call_data);
    }
    UNLOCK_APP(app);
} /* XtRemoveAllCallbacks */

InternalCallbackList _XtCompileCallbackList(xtcallbacks)
    XtCallbackList xtcallbacks;
{
    register int n;
    register XtCallbackList xtcl, cl;
    register InternalCallbackList callbacks;

    for (n=0, xtcl=xtcallbacks; xtcl->callback; n++, xtcl++) {};
    if (n == 0) return (InternalCallbackList) NULL;

    callbacks = (InternalCallbackList) __XtMalloc(sizeof(InternalCallbackRec) +
						sizeof(XtCallbackRec) * n);
    callbacks->count = n;
    callbacks->is_padded = 0;
    callbacks->call_state = 0;
    cl = ToList(callbacks);
    while (--n >= 0)
	*cl++ = *xtcallbacks++;
    return(callbacks);
} /* _XtCompileCallbackList */


XtCallbackList _XtGetCallbackList(callbacks)
    InternalCallbackList *callbacks;
{
    register int i;
    register InternalCallbackList icl;
    register XtCallbackList cl, ocl;

    icl = *callbacks;
    if (!icl) {
	static XtCallbackRec emptyList[1] = { {NULL, NULL} };
	return (XtCallbackList)emptyList;
    }
    if (icl->is_padded)
	return ToList(icl);
    i = icl->count;
    if (icl->call_state) {
	icl->call_state |= _XtCBFreeAfterCalling;
	ocl = ToList(icl);
	icl = (InternalCallbackList) __XtMalloc(sizeof(InternalCallbackRec) +
					      sizeof(XtCallbackRec) * (i+1));
	icl->count = i;
	icl->call_state = 0;
	cl = ToList(icl);
	while (--i >= 0)
	    *cl++ = *ocl++;
    } else {
	icl = (InternalCallbackList) XtRealloc((char *)icl,
					       sizeof(InternalCallbackRec) +
					       sizeof(XtCallbackRec) * (i+1));
	cl = ToList(icl) + i;
    }
    icl->is_padded = 1;
    cl->callback = (XtCallbackProc) NULL;
    cl->closure = NULL;
    *callbacks = icl;
    return ToList(icl);
}

#if NeedFunctionPrototypes
void XtCallCallbacks(
    Widget   widget,
    _Xconst char* name,
    XtPointer call_data
    )
#else
void XtCallCallbacks(widget, name, call_data)
    Widget   widget;
    String   name;
    XtPointer call_data;
#endif
{
    InternalCallbackList *callbacks;
    InternalCallbackList icl;
    XtCallbackList cl;
    int i;
    char ostate;
    XtAppContext app = XtWidgetToApplicationContext(widget);

    LOCK_APP(app);
    callbacks = FetchInternalList(widget, name);
    if (!callbacks) {
	XtAppWarningMsg(app,
	       XtNinvalidCallbackList,XtNxtCallCallback,XtCXtToolkitError,
              "Cannot find callback list in XtCallCallbacks",
	      (String *)NULL, (Cardinal *)NULL);
	UNLOCK_APP(app);
	return;
    }

    icl = *callbacks;
    if (!icl) {
	UNLOCK_APP(app);
	return;
    }
    cl = ToList(icl);
    if (icl->count == 1) {
	(*cl->callback) (widget, cl->closure, call_data);
	UNLOCK_APP(app);
	return;
    }
    ostate = icl->call_state;
    icl->call_state = _XtCBCalling;
    for (i = icl->count; --i >= 0; cl++)
	(*cl->callback) (widget, cl->closure, call_data);
    if (ostate)
	icl->call_state |= ostate;
    else if (icl->call_state & _XtCBFreeAfterCalling)
	XtFree((char *)icl);
    else
	icl->call_state = ostate;
    UNLOCK_APP(app);
} /* XtCallCallbacks */


#if NeedFunctionPrototypes
XtCallbackStatus XtHasCallbacks(
     Widget		widget,
     _Xconst char*	callback_name
     )
#else
XtCallbackStatus XtHasCallbacks(widget, callback_name)
     Widget		widget;
     String		callback_name;
#endif
{
    InternalCallbackList *callbacks;
    XtCallbackStatus retval = XtCallbackHasSome;
    WIDGET_TO_APPCON(widget);

    LOCK_APP(app);
    callbacks = FetchInternalList(widget, callback_name);
    if (!callbacks)
	retval = XtCallbackNoList;
    else if (!*callbacks)
	retval = XtCallbackHasNone;
    UNLOCK_APP(app);
    return retval;
} /* XtHasCallbacks */


void XtCallCallbackList(widget, callbacks, call_data)
    Widget widget;
    XtCallbackList callbacks;
    XtPointer call_data;
{
    register InternalCallbackList icl;
    register XtCallbackList cl;
    register int i;
    char ostate;
    WIDGET_TO_APPCON(widget);

    LOCK_APP(app);
    if (!callbacks) {
	UNLOCK_APP(app);
	return;
    }
    icl = (InternalCallbackList)callbacks;
    cl = ToList(icl);
    if (icl->count == 1) {
	(*cl->callback) (widget, cl->closure, call_data);
	UNLOCK_APP(app);
	return;
    }
    ostate = icl->call_state;
    icl->call_state = _XtCBCalling;
    for (i = icl->count; --i >= 0; cl++)
	(*cl->callback) (widget, cl->closure, call_data);
    if (ostate)
	icl->call_state |= ostate;
    else if (icl->call_state & _XtCBFreeAfterCalling)
	XtFree((char *)icl);
    else
	icl->call_state = 0;
    UNLOCK_APP(app);
} /* XtCallCallbackList */

void _XtPeekCallback(widget, callbacks, callback, closure)
    Widget widget;
    XtCallbackList callbacks;
    XtCallbackProc *callback;
    XtPointer *closure;
{
    register InternalCallbackList icl = (InternalCallbackList) callbacks;
    register XtCallbackList cl;

    if (!callbacks) {
	*callback = (XtCallbackProc) NULL;
	return;
    }
    cl = ToList(icl);
    *callback = cl->callback;
    *closure = cl->closure;
    return;
}

void _XtCallConditionalCallbackList(widget, callbacks, call_data, cond_proc)
    Widget widget;
    XtCallbackList callbacks;
    XtPointer call_data;
    _XtConditionProc cond_proc;
{
    register InternalCallbackList icl;
    register XtCallbackList cl;
    register int i;
    char ostate;
    WIDGET_TO_APPCON(widget);

    LOCK_APP(app);
    if (!callbacks) {
	UNLOCK_APP(app);
	return;
    }
    icl = (InternalCallbackList)callbacks;
    cl = ToList(icl);
    if (icl->count == 1) {
	(*cl->callback) (widget, cl->closure, call_data);
	(void) (*cond_proc)(call_data);
	UNLOCK_APP(app);
	return;
    }
    ostate = icl->call_state;
    icl->call_state = _XtCBCalling;
    for (i = icl->count; --i >= 0; cl++) {
	(*cl->callback) (widget, cl->closure, call_data);
	if (! (*cond_proc)(call_data))
	    break;
    }
    if (ostate)
	icl->call_state |= ostate;
    else if (icl->call_state & _XtCBFreeAfterCalling)
	XtFree((char *)icl);
    else
	icl->call_state = 0;
    UNLOCK_APP(app);
}
