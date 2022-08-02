/* $XConsortium: Popup.c,v 1.35 94/04/17 20:14:35 kaleb Exp $ */

/***********************************************************

Copyright (c) 1987, 1988, 1994  X Consortium

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

#include "IntrinsicI.h"
#include "ShellP.h"

#if NeedFunctionPrototypes
void _XtPopup(
    Widget      widget,
    XtGrabKind  grab_kind,
    _XtBoolean  spring_loaded
    )
#else
void _XtPopup(widget, grab_kind, spring_loaded)
    Widget      widget;
    XtGrabKind  grab_kind;
    Boolean     spring_loaded;
#endif
{
    register ShellWidget shell_widget = (ShellWidget) widget;

    if (! XtIsShell(widget)) {
	XtAppErrorMsg(XtWidgetToApplicationContext(widget),
		"invalidClass","xtPopup",XtCXtToolkitError,
                "XtPopup requires a subclass of shellWidgetClass",
                  (String *)NULL, (Cardinal *)NULL);
    }

    if (! shell_widget->shell.popped_up) {
	XtGrabKind call_data = grab_kind;
	XtCallCallbacks(widget, XtNpopupCallback, (XtPointer)&call_data);
	shell_widget->shell.popped_up = TRUE;
	shell_widget->shell.grab_kind = grab_kind;
	shell_widget->shell.spring_loaded = spring_loaded;
	if (shell_widget->shell.create_popup_child_proc != NULL) {
	    (*(shell_widget->shell.create_popup_child_proc))(widget);
	}
	if (grab_kind == XtGrabExclusive) {
	    XtAddGrab(widget, TRUE, spring_loaded);
	} else if (grab_kind == XtGrabNonexclusive) {
	    XtAddGrab(widget, FALSE, spring_loaded);
	}
	XtRealizeWidget(widget);
	XMapRaised(XtDisplay(widget), XtWindow(widget));
    } else
	XRaiseWindow(XtDisplay(widget), XtWindow(widget));

} /* _XtPopup */

#if NeedFunctionPrototypes
void XtPopup (Widget widget, XtGrabKind grab_kind)
#else
void XtPopup (widget, grab_kind)
    Widget  widget;
    XtGrabKind grab_kind;
#endif
{
    Widget hookobj;

    switch (grab_kind) {

      case XtGrabNone:
      case XtGrabExclusive:
      case XtGrabNonexclusive:
	break;

      default:
	XtAppWarningMsg(
		XtWidgetToApplicationContext(widget),
		"invalidGrabKind","xtPopup",XtCXtToolkitError,
		"grab kind argument has invalid value; XtGrabNone assumed",
		(String *)NULL, (Cardinal *)NULL);
	grab_kind = XtGrabNone;
    }
	
    _XtPopup(widget, grab_kind, FALSE);

    hookobj = XtHooksOfDisplay(XtDisplay(widget));
    if (XtHasCallbacks(hookobj, XtNchangeHook) == XtCallbackHasSome) {
	XtChangeHookDataRec call_data;

	call_data.type = XtHpopup;
	call_data.widget = widget;
	call_data.event_data = (XtPointer)grab_kind;
	XtCallCallbackList(hookobj, 
		((HookObject)hookobj)->hooks.changehook_callbacks, 
		(XtPointer)&call_data);
    }
} /* XtPopup */

void XtPopupSpringLoaded (widget)
    Widget widget;
{
    Widget hookobj;

    _XtPopup(widget, XtGrabExclusive, True);

    hookobj = XtHooksOfDisplay(XtDisplay(widget));
    if (XtHasCallbacks(hookobj, XtNchangeHook) == XtCallbackHasSome) {
	XtChangeHookDataRec call_data;

	call_data.type = XtHpopupSpringLoaded;
	call_data.widget = widget;
	XtCallCallbackList(hookobj, 
		((HookObject)hookobj)->hooks.changehook_callbacks, 
		(XtPointer)&call_data);
    }
}

void XtPopdown(widget)
    Widget  widget;
{
    /* Unmap a shell widget if it is mapped, and remove from grab list */
    Widget hookobj;
    ShellWidget shell_widget = (ShellWidget) widget;

    if (! XtIsShell(widget)) {
	XtAppErrorMsg(XtWidgetToApplicationContext(widget),
		"invalidClass","xtPopdown",XtCXtToolkitError,
            "XtPopdown requires a subclass of shellWidgetClass",
              (String *)NULL, (Cardinal *)NULL);
    }

    if (shell_widget->shell.popped_up) {
	XtGrabKind grab_kind = shell_widget->shell.grab_kind;
	XWithdrawWindow(XtDisplay(widget), XtWindow(widget),
			XScreenNumberOfScreen(XtScreen(widget)));
	if (grab_kind != XtGrabNone) {
	    XtRemoveGrab(widget);
	}
	shell_widget->shell.popped_up = FALSE;
	XtCallCallbacks(widget, XtNpopdownCallback, (XtPointer)&grab_kind);
    }

    hookobj = XtHooksOfDisplay(XtDisplay(widget));
    if (XtHasCallbacks(hookobj, XtNchangeHook) == XtCallbackHasSome) {
	XtChangeHookDataRec call_data;

	call_data.type = XtHpopdown;
	call_data.widget = widget;
	XtCallCallbackList(hookobj, 
		((HookObject)hookobj)->hooks.changehook_callbacks, 
		(XtPointer)&call_data);
    }
} /* XtPopdown */

/* ARGSUSED */
void XtCallbackPopdown(widget, closure, call_data)
    Widget  widget;
    XtPointer closure;
    XtPointer call_data;
{
    register XtPopdownID id = (XtPopdownID) closure;

    XtPopdown(id->shell_widget);
    if (id->enable_widget != NULL) {
	XtSetSensitive(id->enable_widget, TRUE);
    }
} /* XtCallbackPopdown */



