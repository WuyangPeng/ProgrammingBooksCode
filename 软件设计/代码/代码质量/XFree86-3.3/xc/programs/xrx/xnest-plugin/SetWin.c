/* $XConsortium: SetWin.c /main/3 1996/09/27 20:44:56 lehors $ */
/*

Copyright (C) 1996 X Consortium

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Soft-
ware"), to deal in the Software without restriction, including without
limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to
whom the Software is furnished to do so, subject to the following condi-
tions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABIL-
ITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT
SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABIL-
ITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization from
the X Consortium.

*/

/*
 * RX plug-in module based on the UnixTemplate file provided by Netcape.
 */

/* -*- Mode: C; tab-width: 4; -*- */
/******************************************************************************
 * Copyright (c) 1996 Netscape Communications. All rights reserved.
 ******************************************************************************/
/*
 * UnixShell.c
 *
 * Netscape Client Plugin API
 * - Function that need to be implemented by plugin developers
 *
 * This file defines a "Template" plugin that plugin developers can use
 * as the basis for a real plugin.  This shell just provides empty
 * implementations of all functions that the plugin can implement
 * that will be called by Netscape (the NPP_xxx methods defined in 
 * npapi.h). 
 *
 * dp Suresh <dp@netscape.com>
 *
 */

#include "RxPlugin.h"
#include <Xm/XmStrDefs.h>

/***********************************************************************
 * Sometimes the plugin widget gets stupidly destroyed, that is whenever
 * Netscape relayouts the page. This callback reparents the Xnest
 * window to the root window so it does not get destroyed as well.
 * Eventually the NPP_SetWindow function should be called and we'll
 * reparent it back under the plugin.
 ***********************************************************************/
static void
DestroyCB (Widget widget, XtPointer client_data, XtPointer call_data)
{
    PluginInstance* This = (PluginInstance*) client_data;
    int i;
#ifdef PLUGIN_TRACE
    fprintf (stderr, "DestroyCB, This: 0x%x\n", This);
#endif
    This->plugin_widget = NULL;
    This->status_widget = NULL;
    if (This->dont_reparent == RxFalse) {
	XUnmapWindow(XtDisplay(widget), This->window);
	XReparentWindow(XtDisplay(widget), This->window,
			RootWindowOfScreen(XtScreen(widget)), 0, 0);
	This->dont_reparent = RxTrue;
    } else
	This->dont_reparent = RxFalse;
    /* 
     * not worth removing event handlers on this widget since it's
     * about to be destroyed anyway.
     */
}


/***********************************************************************
 * Sometimes the plugin widget gets stupidly resized, because of poor
 * geometry when its child (that is the status widget) gets destroyed.
 * So this callback resizes it back to the right size.
 * Note that this could lead to an endless battle, but it appears that
 * it doesn't so far...
 ***********************************************************************/
static void
ResizeCB (Widget widget, XtPointer client_data, XtPointer call_data)
{
    PluginInstance* This = (PluginInstance*) client_data;
    Arg args[5];
    int n;

#ifdef PLUGIN_TRACE
    fprintf (stderr, "ResizeCB, This: 0x%x\n", This);
#endif
    /* make sure plugin widget gets the same size back */
    n = 0;
    XtSetArg(args[n], XmNwidth, This->width); n++;
    XtSetArg(args[n], XmNheight, This->height); n++;
    XtSetValues(This->plugin_widget, args, n);
}

/***********************************************************************
 * This function gets called first when the plugin widget is created and
 * then whenever the plugin is changed.
 ***********************************************************************/
NPError 
NPP_SetWindow(NPP instance, NPWindow* window)
{
    PluginInstance* This;
    Display *display;
    Widget netscape_widget;
    pid_t pid;

    if (instance == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

    if (window == NULL)
	return NPERR_NO_ERROR;

    This = (PluginInstance*) instance->pdata;

    /*
     * PLUGIN DEVELOPERS:
     *	Before setting window to point to the
     *	new window, you may wish to compare the new window
     *	info to the previous window (if any) to note window
     *	size changes, etc.
     */
    display = ((NPSetWindowCallbackStruct *)window->ws_info)->display;
    netscape_widget = XtWindowToWidget(display, (Window) window->window);

    if (This->plugin_widget != netscape_widget) {

	/* We have a new widget store it */
	This->plugin_widget = netscape_widget;
	This->width = window->width;
	This->height = window->height;

	XtAddCallback (This->plugin_widget, XtNdestroyCallback, 
		       DestroyCB, (XtPointer) This);
	XtAddCallback (This->plugin_widget, XmNresizeCallback, 
		       ResizeCB, (XtPointer) This);

	if (This->window == None) {

	    This->window = XCreateSimpleWindow(display, (Window)window->window,
					       0, 0,
					       window->width, window->height,
					       0, 0, 0);
	    XMapWindow(display, This->window);

	    This->display_num = RxpXnestDisplayNumber();
#ifdef PLUGIN_TRACE
	    fprintf(stderr, "Windows: %ld %ld\n",
		    (Window) window->window, XtWindow(This->window));
#endif
	    pid = fork();
	    if (pid == 0) {		/* child process */
		static char *argv[] = {
		    "Xnest",
		    "-ac",		/* no access control (sic!) */
		    ":00",		/* display number */
		    "-parent",
		    "01234567890123456789",	/* parent window id */
		    NULL
		};
		close(ConnectionNumber(display));

		sprintf(argv[2], ":%d", This->display_num);
		sprintf(argv[4], "%ld", This->window);
		/* exec Xnest */
		execvp("Xnest", argv);
		perror("Xnest");
		return NPERR_GENERIC_ERROR;
	    } else {			/* parent process */
		/* store child pid so we can kill it later on */
		This->child_pid = pid;
	    }
	} else {
		/* Xnest is either under the RootWindow or the old widget */
		XReparentWindow(display, This->window, (Window)window->window,
				0, 0);
		if (This->dont_reparent == RxTrue)
		    XMapWindow(display, This->window);
		if (This->state != RUNNING)
		    RxpSetStatusWidget(This, This->state);
	}
	if (This->dont_reparent != RxFalse) /* can be True or Undef */
	    This->dont_reparent = RxFalse;
	else
	    This->dont_reparent = RxTrue;
    }

    return NPERR_NO_ERROR;
}
