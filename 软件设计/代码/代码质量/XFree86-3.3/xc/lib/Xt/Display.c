/* $TOG: Display.c /main/114 1997/05/15 17:28:57 kaleb $ */

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
/* $XFree86: xc/lib/Xt/Display.c,v 3.4.2.3 1997/05/31 13:34:31 dawes Exp $ */

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

#ifndef X_NOT_STDC_ENV
#include <stdlib.h>
#else
extern char* getenv();
#endif

#ifdef XTHREADS
void (*_XtProcessLock)() = NULL;
void (*_XtProcessUnlock)() = NULL;
void (*_XtInitAppLock)() = NULL;
#endif

static String XtNnoPerDisplay = "noPerDisplay";

extern void _XtHeapInit();
extern void _XtHeapFree();
extern XrmDatabase _XtPreparseCommandLine();

ProcessContext _XtGetProcessContext()
{
    static ProcessContextRec processContextRec = {
	(XtAppContext)NULL,
	(XtAppContext)NULL,
	(ConverterTable)NULL,
	{(XtLanguageProc)NULL, (XtPointer)NULL}
    };

    return &processContextRec;
}


XtAppContext _XtDefaultAppContext()
{
    ProcessContext process = _XtGetProcessContext();
    XtAppContext app;

    LOCK_PROCESS;
    if (process->defaultAppContext == NULL) {
	process->defaultAppContext = XtCreateApplicationContext();
    }
    app = process->defaultAppContext;
    UNLOCK_PROCESS;
    return app;
}

static void AddToAppContext(d, app)
	Display *d;
	XtAppContext app;
{
#define DISPLAYS_TO_ADD 4

	if (app->count >= app->max) {
	    app->max += DISPLAYS_TO_ADD;
	    app->list = (Display **) XtRealloc((char *)app->list,
		    (unsigned) app->max * sizeof(Display *));
	}

	app->list[app->count++] = d;
	app->rebuild_fdlist = TRUE;
#ifndef USE_POLL
	if (ConnectionNumber(d) + 1 > app->fds.nfds) {
	    app->fds.nfds = ConnectionNumber(d) + 1;
	}
#else
	app->fds.nfds++;
#endif
#undef DISPLAYS_TO_ADD
}

static void XtDeleteFromAppContext(d, app)
	Display *d;
	register XtAppContext app;
{
	register int i;

	for (i = 0; i < app->count; i++) if (app->list[i] == d) break;

	if (i < app->count) {
	    if (i <= app->last && app->last > 0) app->last--;
	    for (i++; i < app->count; i++) app->list[i-1] = app->list[i];
	    app->count--;
	}
	app->rebuild_fdlist = TRUE;
	app->fds.nfds--;
}

static XtPerDisplay NewPerDisplay(dpy)
	Display *dpy;
{
	PerDisplayTablePtr pd;

	pd = XtNew(PerDisplayTable);
	LOCK_PROCESS;
	pd->dpy = dpy;
	pd->next = _XtperDisplayList;
	_XtperDisplayList = pd;
	UNLOCK_PROCESS;
	return &(pd->perDpy);
}

static XtPerDisplay InitPerDisplay(dpy, app, name, classname)
    Display *dpy;
    XtAppContext app;
    String name;
    String classname;
{
    extern void _XtAllocTMContext();
    XtPerDisplay pd;

    AddToAppContext(dpy, app);

    pd = NewPerDisplay(dpy);
    _XtHeapInit(&pd->heap);
    pd->destroy_callbacks = NULL;
    pd->region = XCreateRegion();
    pd->case_cvt = NULL;
    pd->defaultKeycodeTranslator = XtTranslateKey;
    pd->keysyms_serial = 0;
    pd->keysyms = NULL;
    XDisplayKeycodes(dpy, &pd->min_keycode, &pd->max_keycode);
    pd->modKeysyms = NULL;
    pd->modsToKeysyms = NULL;
    pd->appContext = app;
    pd->name = XrmStringToName(name);
    pd->class = XrmStringToClass(classname);
    pd->being_destroyed = False;
    pd->GClist = NULL;
    pd->pixmap_tab = NULL;
    pd->language = NULL;
    pd->rv = False;
    pd->last_event.xany.serial = 0;
    pd->last_timestamp = 0;
    _XtAllocTMContext(pd);
    pd->mapping_callbacks = NULL;

    pd->pdi.grabList = NULL;
    pd->pdi.trace = NULL;
    pd->pdi.traceDepth = 0;
    pd->pdi.traceMax = 0;
    pd->pdi.focusWidget = NULL;
    pd->pdi.activatingKey = 0;
    pd->pdi.keyboard.grabType = XtNoServerGrab;
    pd->pdi.pointer.grabType  = XtNoServerGrab;
    _XtAllocWWTable(pd);
    pd->per_screen_db = (XrmDatabase *)__XtCalloc(ScreenCount(dpy),
						sizeof(XrmDatabase));
    pd->cmd_db = (XrmDatabase)NULL;
    pd->server_db = (XrmDatabase)NULL;
    pd->dispatcher_list = NULL;
    pd->ext_select_list = NULL;
    pd->ext_select_count = 0;
    pd->hook_object = NULL;
#if 0
    pd->hook_object = _XtCreate("hooks", "Hooks", hookObjectClass,
	(Widget)NULL, (Screen*)DefaultScreenOfDisplay(dpy),
	(ArgList)NULL, 0, (XtTypedArgList)NULL, 0, 
	(ConstraintWidgetClass)NULL);
#endif
    return pd;
}

#if NeedFunctionPrototypes
Display *XtOpenDisplay(
	XtAppContext app,
	_Xconst char* displayName,
	_Xconst char* applName,
	_Xconst char* className,
	XrmOptionDescRec *urlist,
	Cardinal num_urs,
	int *argc,
	String *argv
	)
#else
Display *XtOpenDisplay(app, displayName, applName, className,
		urlist, num_urs, argc, argv)
	XtAppContext app;
	String displayName, applName, className;
	XrmOptionDescRec *urlist;
	Cardinal num_urs;
	int *argc;
	String *argv;
#endif
{
	Display *d;
	XrmDatabase db = 0;
	XtPerDisplay pd;
	String language = NULL;

	LOCK_APP(app);
	LOCK_PROCESS;
	/* parse the command line for name, display, and/or language */
	db = _XtPreparseCommandLine(urlist, num_urs, *argc, argv, &applName,
				    (displayName ? NULL : &displayName),
				    (app->process->globalLangProcRec.proc ?
				     &language : NULL));
	UNLOCK_PROCESS;
	d = XOpenDisplay(displayName);

	if (! applName && !(applName = getenv("RESOURCE_NAME"))) {
	    if (*argc > 0 && argv[0] && *argv[0]) {
#ifdef WIN32
		char *ptr = strrchr(argv[0], '\\');
#else
		char *ptr = strrchr(argv[0], '/');
#endif
#ifdef __EMX__
		char *dot_ptr,*ptr2;
		ptr2 = strrchr(argv[0],'\\');
		if (ptr2 > ptr) ptr = ptr2;
		dot_ptr = strrchr(argv[0],'.');
		if (dot_ptr && (dot_ptr > ptr)) *dot_ptr='\0';
#endif  /* This will remove the .exe suffix under OS/2 */

		if (ptr) applName = ++ptr;
		else applName = argv[0];
	    } else
		applName = "main";
	}

	if (d) {
	    pd = InitPerDisplay(d, app, applName, className);
	    pd->language = language;
	    _XtDisplayInitialize(d, pd, applName, urlist, num_urs, argc, argv);
	} else {
	    int len;
	    displayName = XDisplayName(displayName);
	    len = strlen (displayName);
	    app->display_name_tried = (String) __XtMalloc (len + 1);
	    strncpy ((char*) app->display_name_tried, displayName, len + 1);
	    app->display_name_tried[len] = '\0';
	}
	if (db) XrmDestroyDatabase(db);
	UNLOCK_APP(app);
	return d;
}

Display *
_XtAppInit(app_context_return, application_class, options, num_options,
	   argc_in_out, argv_in_out, fallback_resources)
XtAppContext * app_context_return;
String application_class;
XrmOptionDescRec *options;
Cardinal num_options;
int *argc_in_out;
String **argv_in_out, * fallback_resources;
{
    String *saved_argv;
    int i;
    Display *dpy;

/*
 * Save away argv and argc so we can set the properties later 
 */
    
    saved_argv = (String *)
	__XtMalloc( (Cardinal)((*argc_in_out + 1) * sizeof(String)) );

    for (i = 0 ; i < *argc_in_out ; i++) saved_argv[i] = (*argv_in_out)[i];
    saved_argv[i] = NULL;	/* NULL terminate that sucker. */


    *app_context_return = XtCreateApplicationContext();

    LOCK_APP((*app_context_return));
    if (fallback_resources) /* save a procedure call */
	XtAppSetFallbackResources(*app_context_return, fallback_resources);

    dpy = XtOpenDisplay(*app_context_return, (String) NULL, NULL,
			application_class,
			options, num_options, argc_in_out, *argv_in_out);

    if (!dpy) {
	String param = (*app_context_return)->display_name_tried;
	Cardinal param_count = 1;
	XtErrorMsg("invalidDisplay","xtInitialize",XtCXtToolkitError,
                   "Can't open display: %s", &param, &param_count);
	XtFree((char *) (*app_context_return)->display_name_tried);
    }
    *argv_in_out = saved_argv;
    UNLOCK_APP((*app_context_return));
    return dpy;
}

#if NeedFunctionPrototypes
void
XtDisplayInitialize(
	XtAppContext app,
	Display *dpy,
	_Xconst char* name,
	_Xconst char* classname,
	XrmOptionDescRec *urlist,
	Cardinal num_urs,
	int *argc,
	String *argv
	)
#else
void
XtDisplayInitialize(app, dpy, name, classname, urlist, num_urs, argc, argv)
	XtAppContext app;
	Display *dpy;
	String name, classname;
	XrmOptionDescRec *urlist;
	Cardinal num_urs;
	int *argc;
	String *argv;
#endif
{
    XtPerDisplay pd;
    XrmDatabase db = 0;

    LOCK_APP(app);
    pd = InitPerDisplay(dpy, app, name, classname);
    LOCK_PROCESS;
    if (app->process->globalLangProcRec.proc)
	/* pre-parse the command line for the language resource */
	db = _XtPreparseCommandLine(urlist, num_urs, *argc, argv, NULL, NULL,
				    &pd->language);
    UNLOCK_PROCESS;
    _XtDisplayInitialize(dpy, pd, name, urlist, num_urs, argc, argv);
    if (db) XrmDestroyDatabase(db);
    UNLOCK_APP(app);
}

XtAppContext XtCreateApplicationContext()
{
	XtAppContext app = XtNew(XtAppStruct);
#ifdef XTHREADS
	app->lock_info = NULL;
	app->lock = NULL;
	app->unlock = NULL;
	app->yield_lock = NULL;
	app->restore_lock = NULL;
	app->free_lock = NULL;
#endif
	INIT_APP_LOCK(app);
	LOCK_APP(app);
	LOCK_PROCESS;
	app->process = _XtGetProcessContext();
	app->next = app->process->appContextList;
	app->process->appContextList = app;
	app->langProcRec.proc = app->process->globalLangProcRec.proc;
	app->langProcRec.closure = app->process->globalLangProcRec.closure;
	app->destroy_callbacks = NULL;
	app->list = NULL;
	app->count = app->max = app->last = 0;
	app->timerQueue = NULL;
	app->workQueue = NULL;
	app->signalQueue = NULL;
	app->input_list = NULL;
	app->outstandingQueue = NULL;
	app->errorDB = NULL;
	_XtSetDefaultErrorHandlers(&app->errorMsgHandler, 
		&app->warningMsgHandler, &app->errorHandler, 
		&app->warningHandler);
	app->action_table = NULL;
	_XtSetDefaultSelectionTimeout(&app->selectionTimeout);
	_XtSetDefaultConverterTable(&app->converterTable);
	app->sync = app->being_destroyed = app->error_inited = FALSE;
	app->in_phase2_destroy = NULL;
#ifndef USE_POLL
	FD_ZERO(&app->fds.rmask);
	FD_ZERO(&app->fds.wmask);
	FD_ZERO(&app->fds.emask);
#endif
	app->fds.nfds = 0;
	app->input_count = app->input_max = 0;
	_XtHeapInit(&app->heap);
	app->fallback_resources = NULL;
	_XtPopupInitialize(app);
	app->action_hook_list = NULL;
	app->block_hook_list = NULL;
	app->destroy_list_size = app->destroy_count = app->dispatch_level = 0;
	app->destroy_list = NULL;
#ifndef NO_IDENTIFY_WINDOWS
	app->identify_windows = False;
#endif
	app->free_bindings = NULL;
	app->display_name_tried = NULL;
	app->dpy_destroy_count = 0;
	app->dpy_destroy_list = NULL;
	app->exit_flag = FALSE;
	app->rebuild_fdlist = TRUE;
	UNLOCK_PROCESS;
	UNLOCK_APP(app);
	return app;
}

#if NeedFunctionPrototypes
void XtAppSetExitFlag (
    XtAppContext app)
#else
void XtAppSetExitFlag (app)
    XtAppContext app;
#endif
{
    LOCK_APP(app);
    app->exit_flag = TRUE;
    UNLOCK_APP(app);
}

#if NeedFunctionPrototypes
Boolean XtAppGetExitFlag (
    XtAppContext app)
#else
Boolean XtAppGetExitFlag (app)
    XtAppContext app;
#endif
{
    Boolean retval;
    LOCK_APP(app);
    retval = app->exit_flag;
    UNLOCK_APP(app);
    return retval;
}

static void DestroyAppContext(app)
	XtAppContext app;
{
	XtAppContext* prev_app;

	prev_app = &app->process->appContextList;
	while (app->count-- > 0) XtCloseDisplay(app->list[app->count]);
	if (app->list != NULL) XtFree((char *)app->list);
	_XtFreeConverterTable(app->converterTable);
	_XtCacheFlushTag(app, (XtPointer)&app->heap);
	_XtFreeActions(app->action_table);
	if (app->destroy_callbacks != NULL) {
	    XtCallCallbackList((Widget) NULL,
			       (XtCallbackList)app->destroy_callbacks, 
			       (XtPointer)app);
	    _XtRemoveAllCallbacks(&app->destroy_callbacks);
	}
	while (app->timerQueue) XtRemoveTimeOut((XtIntervalId)app->timerQueue);
	while (app->workQueue) XtRemoveWorkProc((XtWorkProcId)app->workQueue);
	while (app->signalQueue) XtRemoveSignal((XtSignalId)app->signalQueue);
	if (app->input_list) _XtRemoveAllInputs(app);
	XtFree((char*)app->destroy_list);
	_XtHeapFree(&app->heap);
	while (*prev_app != app) prev_app = &(*prev_app)->next;
	*prev_app = app->next;
	if (app->process->defaultAppContext == app)
	    app->process->defaultAppContext = NULL;
	if (app->free_bindings) _XtDoFreeBindings (app);
	FREE_APP_LOCK(app);
	XtFree((char *)app);
}

static XtAppContext* appDestroyList = NULL;
int _XtAppDestroyCount = 0;

void XtDestroyApplicationContext(app)
	XtAppContext app;
{
	LOCK_APP(app);
	if (app->being_destroyed) {
	    UNLOCK_APP(app);
	    return;
	}

	if (_XtSafeToDestroy(app)) {
	    LOCK_PROCESS;
	    DestroyAppContext(app);
	    UNLOCK_PROCESS;
	} else {
	    app->being_destroyed = TRUE;
	    LOCK_PROCESS;
	    _XtAppDestroyCount++;
	    appDestroyList =
		    (XtAppContext *) XtRealloc((char *) appDestroyList,
		    (unsigned) (_XtAppDestroyCount * sizeof(XtAppContext)));
	    appDestroyList[_XtAppDestroyCount-1] = app;
	    UNLOCK_PROCESS;
	    UNLOCK_APP(app);
	}
}

void _XtDestroyAppContexts()
{
	int i,ii;
	XtAppContext apps[8];
	XtAppContext* pApps;

	pApps = XtStackAlloc (sizeof (XtAppContext) * _XtAppDestroyCount, apps);

	for (i = ii = 0; i < _XtAppDestroyCount; i++) {
	    if (_XtSafeToDestroy(appDestroyList[i]))
		DestroyAppContext(appDestroyList[i]);
	    else
		pApps[ii++] = appDestroyList[i];
	}
	_XtAppDestroyCount = ii;
	if (_XtAppDestroyCount == 0) {
	    XtFree((char *) appDestroyList);
	    appDestroyList = NULL;
	} else {
	    for (i = 0; i < ii; i++)
		appDestroyList[i] = pApps[i];
	}
	XtStackFree ((XtPointer) pApps, apps);
}

XrmDatabase XtDatabase(dpy)
	Display *dpy;
{
    XrmDatabase retval;
    DPY_TO_APPCON(dpy);

    LOCK_APP(app);
    retval = XrmGetDatabase(dpy);
    UNLOCK_APP(app);
    return retval;
}

PerDisplayTablePtr _XtperDisplayList = NULL;

XtPerDisplay _XtSortPerDisplayList(dpy)
	Display *dpy;
{
	register PerDisplayTablePtr pd, opd;

#ifdef lint
	opd = NULL;
#endif
	LOCK_PROCESS;
	for (pd = _XtperDisplayList;
	     pd != NULL && pd->dpy != dpy;
	     pd = pd->next) {
	    opd = pd;
	}

	if (pd == NULL) {
	    XtErrorMsg(XtNnoPerDisplay, "getPerDisplay", XtCXtToolkitError,
		    "Couldn't find per display information",
		    (String *) NULL, (Cardinal *)NULL);
	}

	if (pd != _XtperDisplayList) {	/* move it to the front */
	    /* opd points to the previous one... */

	    opd->next = pd->next;
	    pd->next = _XtperDisplayList;
	    _XtperDisplayList = pd;
	}
	UNLOCK_PROCESS;
	return &(pd->perDpy);
}

XtAppContext XtDisplayToApplicationContext(dpy)
	Display *dpy;
{
	XtAppContext retval;

	retval = _XtGetPerDisplay(dpy)->appContext;
	return retval;
}

static void CloseDisplay(dpy)
	Display *dpy;
{
        register XtPerDisplay xtpd;
	register PerDisplayTablePtr pd, opd;
	XrmDatabase db;
	int i;
	
#ifdef lint
	opd = NULL;
#endif
	XtDestroyWidget(XtHooksOfDisplay(dpy));

	LOCK_PROCESS;
	for (pd = _XtperDisplayList;
	     pd != NULL && pd->dpy != dpy;
	     pd = pd->next){
	    opd = pd;
	}

	if (pd == NULL) {
	    XtErrorMsg(XtNnoPerDisplay, "closeDisplay", XtCXtToolkitError,
		    "Couldn't find per display information",
		    (String *) NULL, (Cardinal *)NULL);
	}

	if (pd == _XtperDisplayList) _XtperDisplayList = pd->next;
	else opd->next = pd->next;

	xtpd = &(pd->perDpy);

        if (xtpd != NULL) {
	    extern void _XtGClistFree();
	    if (xtpd->destroy_callbacks != NULL) {
		XtCallCallbackList((Widget) NULL,
				   (XtCallbackList)xtpd->destroy_callbacks,
				   (XtPointer)xtpd);
		_XtRemoveAllCallbacks(&xtpd->destroy_callbacks);
	    }
	    if (xtpd->mapping_callbacks != NULL)
		_XtRemoveAllCallbacks(&xtpd->mapping_callbacks);
	    XtDeleteFromAppContext(dpy, xtpd->appContext);
	    if (xtpd->keysyms)
		XFree((char *) xtpd->keysyms);
            XtFree((char *) xtpd->modKeysyms);
            XtFree((char *) xtpd->modsToKeysyms);
            xtpd->keysyms_per_keycode = 0;
            xtpd->being_destroyed = FALSE;
            xtpd->keysyms = NULL;
            xtpd->modKeysyms = NULL;
            xtpd->modsToKeysyms = NULL;
	    XDestroyRegion(xtpd->region);
	    _XtCacheFlushTag(xtpd->appContext, (XtPointer)&xtpd->heap);
	    _XtGClistFree(dpy, xtpd);
	    XtFree((char*)xtpd->pdi.trace);
	    _XtHeapFree(&xtpd->heap);
	    _XtFreeWWTable(xtpd);
	    xtpd->per_screen_db[DefaultScreen(dpy)] = (XrmDatabase)NULL;
	    for (i = ScreenCount(dpy); --i >= 0; ) {
		db = xtpd->per_screen_db[i];
		if (db)
		    XrmDestroyDatabase(db);
	    }
	    XtFree((char *)xtpd->per_screen_db);
	    if (db = XrmGetDatabase(dpy))
		XrmDestroyDatabase(db);
	    if (xtpd->cmd_db)
		XrmDestroyDatabase(xtpd->cmd_db);
	    if (xtpd->server_db)
		XrmDestroyDatabase(xtpd->server_db);
	    XtFree(xtpd->language);
	    if (xtpd->dispatcher_list != NULL)
		XtFree((char *) xtpd->dispatcher_list);
	    if (xtpd->ext_select_list != NULL)
		XtFree((char *) xtpd->ext_select_list);
        }
	XtFree((char*)pd);
	XrmSetDatabase(dpy, (XrmDatabase)NULL);
	XCloseDisplay(dpy);
	UNLOCK_PROCESS;
}

void XtCloseDisplay(dpy)
	Display *dpy;
{
	XtPerDisplay pd;
	XtAppContext app = XtDisplayToApplicationContext(dpy);

	LOCK_APP(app);
	pd = _XtGetPerDisplay(dpy);
	if (pd->being_destroyed) {
	    UNLOCK_APP(app);
	    return;
	}

	if (_XtSafeToDestroy(app)) CloseDisplay(dpy);
	else {
	    pd->being_destroyed = TRUE;
	    app->dpy_destroy_count++;
	    app->dpy_destroy_list = (Display **) 
		XtRealloc((char *) app->dpy_destroy_list,
		    (unsigned) (app->dpy_destroy_count * sizeof(Display *)));
	    app->dpy_destroy_list[app->dpy_destroy_count-1] = dpy;
	}
	UNLOCK_APP(app);
}

#if NeedFunctionPrototypes
void _XtCloseDisplays(
    XtAppContext app)
#else
void _XtCloseDisplays(app)
    XtAppContext app;
#endif
{
	int i;

	LOCK_APP(app);
	for (i = 0; i < app->dpy_destroy_count; i++) {
	    CloseDisplay(app->dpy_destroy_list[i]);
	}
	app->dpy_destroy_count = 0;
	XtFree((char *) app->dpy_destroy_list);
	app->dpy_destroy_list = NULL;
	UNLOCK_APP(app);
}

XtAppContext XtWidgetToApplicationContext(w)
	Widget w;
{
	XtAppContext retval;

	retval = _XtGetPerDisplay(XtDisplayOfObject(w))->appContext;
	return retval;
}


void XtGetApplicationNameAndClass(dpy, name_return, class_return)
    Display *dpy;
    String *name_return;
    String *class_return;
{
    XtPerDisplay pd;

    pd = _XtGetPerDisplay(dpy);
    *name_return = XrmQuarkToString(pd->name);
    *class_return = XrmQuarkToString(pd->class);
}

#if NeedFunctionPrototypes
XtPerDisplay _XtGetPerDisplay (
    Display* display)
#else
XtPerDisplay _XtGetPerDisplay (display)
    Display* display;
#endif
{
    XtPerDisplay retval;

    LOCK_PROCESS;
    retval = ((_XtperDisplayList != NULL &&
	      _XtperDisplayList->dpy == display)
	      ? &_XtperDisplayList->perDpy
	      : _XtSortPerDisplayList(display));
    UNLOCK_PROCESS;
    return retval;
}

#if NeedFunctionPrototypes
XtPerDisplayInputRec* _XtGetPerDisplayInput(
    Display* display)
#else
XtPerDisplayInputRec* _XtGetPerDisplayInput(display)
    Display* display;
#endif
{
    XtPerDisplayInputRec* retval;
    LOCK_PROCESS;
    retval = ((_XtperDisplayList != NULL &&
	      _XtperDisplayList->dpy == display)
	      ? &_XtperDisplayList->perDpy.pdi
	      : &_XtSortPerDisplayList(display)->pdi);
    UNLOCK_PROCESS;
    return retval;
}

#if NeedFunctionPrototypes
void XtGetDisplays(
    XtAppContext app_context,
    Display*** dpy_return,
    Cardinal* num_dpy_return)
#else
void XtGetDisplays(app_context, dpy_return, num_dpy_return)
    XtAppContext app_context;
    Display*** dpy_return;
    Cardinal* num_dpy_return;
#endif
{
    int ii;
    LOCK_APP(app_context);
    *num_dpy_return = app_context->count;
    *dpy_return = (Display**)__XtMalloc(app_context->count * sizeof(Display*));
    for (ii = 0; ii < app_context->count; ii++)
	*dpy_return[ii] = app_context->list[ii];
    UNLOCK_APP(app_context);
}
