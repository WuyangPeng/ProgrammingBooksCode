/* $XConsortium: InitialI.h,v 1.85 95/06/16 19:25:22 kaleb Exp $ */

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

/****************************************************************
 *
 * Displays
 *
 ****************************************************************/

#ifndef X_NOT_POSIX
#ifdef _POSIX_SOURCE
#include <limits.h>
#else
#define _POSIX_SOURCE
#include <limits.h>
#undef _POSIX_SOURCE
#endif
#endif
#ifndef PATH_MAX
#ifdef WIN32
#define PATH_MAX 512
#else
#include <sys/param.h>
#endif
#ifndef PATH_MAX
#ifdef MAXPATHLEN
#define PATH_MAX MAXPATHLEN
#else
#define PATH_MAX 1024
#endif
#endif
#endif

#include <X11/Xpoll.h>

typedef struct _TimerEventRec {
        struct timeval        te_timer_value;
	struct _TimerEventRec *te_next;
	XtTimerCallbackProc   te_proc;
	XtAppContext	      app;
	XtPointer	      te_closure;
} TimerEventRec;

typedef struct _InputEvent {
	XtInputCallbackProc   ie_proc;
	XtPointer	      ie_closure;
	struct _InputEvent    *ie_next;
	struct _InputEvent    *ie_oq;
	XtAppContext	      app;
	int		      ie_source;
	XtInputMask	      ie_condition;
} InputEvent;

typedef struct _SignalEventRec {
	XtSignalCallbackProc  se_proc;
	XtPointer	      se_closure;
	struct _SignalEventRec *se_next;
	XtAppContext	      app;
	Boolean		      se_notice;
} SignalEventRec;

typedef struct _WorkProcRec {
	XtWorkProc proc;
	XtPointer closure;
	struct _WorkProcRec *next;
	XtAppContext app;
} WorkProcRec;


typedef struct 
{
#ifndef USE_POLL
  	fd_set rmask;
	fd_set wmask;
	fd_set emask;
#endif
	int	nfds;
} FdStruct;

typedef struct _LangProcRec {
    XtLanguageProc	proc;
    XtPointer		closure;
} LangProcRec;

typedef struct _ProcessContextRec {
    XtAppContext	defaultAppContext;
    XtAppContext	appContextList;
    ConverterTable	globalConverterTable;
    LangProcRec		globalLangProcRec;
} ProcessContextRec, *ProcessContext;

typedef struct {
    char*	start;
    char*	current;
    int		bytes_remaining;
} Heap;

typedef struct _DestroyRec DestroyRec;


typedef struct _XtAppStruct {
    XtAppContext next;		/* link to next app in process context */
    ProcessContext process;	/* back pointer to our process context */
    InternalCallbackList destroy_callbacks;
    Display **list;
    TimerEventRec *timerQueue;
    WorkProcRec *workQueue;
    InputEvent **input_list;
    InputEvent *outstandingQueue;
    SignalEventRec *signalQueue;
    XrmDatabase errorDB;
    XtErrorMsgHandler errorMsgHandler, warningMsgHandler;
    XtErrorHandler errorHandler, warningHandler;
    struct _ActionListRec *action_table;
    ConverterTable converterTable;
    unsigned long selectionTimeout;
    FdStruct fds;
    short count;			/* num of assigned entries in list */
    short max;				/* allocate size of list */
    short last;
    short input_count;
    short input_max;			/* elts input_list init'd with */
    Boolean sync, being_destroyed, error_inited;
#ifndef NO_IDENTIFY_WINDOWS
    Boolean identify_windows;		/* debugging hack */
#endif
    Heap heap;
    String * fallback_resources;	/* Set by XtAppSetFallbackResources. */
    struct _ActionHookRec* action_hook_list;
    struct _BlockHookRec* block_hook_list;
    int destroy_list_size;		/* state data for 2-phase destroy */
    int destroy_count;
    int dispatch_level;
    DestroyRec* destroy_list;
    Widget in_phase2_destroy;
    LangProcRec langProcRec;
    struct _TMBindCacheRec * free_bindings;
    String display_name_tried;
    Display **dpy_destroy_list;
    int dpy_destroy_count;
    Boolean exit_flag;
    Boolean rebuild_fdlist;
#ifdef XTHREADS
    LockPtr lock_info;
    ThreadAppProc lock;
    ThreadAppProc unlock;
    ThreadAppYieldLockProc yield_lock;
    ThreadAppRestoreLockProc restore_lock;
    ThreadAppProc free_lock;
#endif
} XtAppStruct;

#ifdef XTTRACEMEMORY


extern char *_XtHeapMalloc(
#if NeedFunctionPrototypes
    Heap*	/* heap */,
    Cardinal	/* size */,
    char *	/* file */,
    int		/* line */
#endif
);

#define _XtHeapAlloc(heap,bytes) _XtHeapMalloc(heap, bytes, __FILE__, __LINE__)

#else /* XTTRACEMEMORY */

extern char* _XtHeapAlloc(
#if NeedFunctionPrototypes
    Heap*	/* heap */,
    Cardinal	/* size */
#endif
);

#endif /* XTTRACEMEMORY */

extern void _XtSetDefaultErrorHandlers(
#if NeedFunctionPrototypes
    XtErrorMsgHandler*	/* errMsg */,
    XtErrorMsgHandler*	/* warnMsg */,
    XtErrorHandler*	/* err */,
    XtErrorHandler*	/* warn */
#endif
);

extern void _XtSetDefaultSelectionTimeout(
#if NeedFunctionPrototypes
    unsigned long* /* timeout */
#endif
);

extern XtAppContext _XtDefaultAppContext(
#if NeedFunctionPrototypes
    void
#endif
);

extern ProcessContext _XtGetProcessContext(
#if NeedFunctionPrototypes
    void
#endif
);

Display *
_XtAppInit(
#if NeedFunctionPrototypes
    XtAppContext*	/* app_context_return */,
    String		/* application_class */,
    XrmOptionDescRec*	/* options */,
    Cardinal		/* num_options */,
    int*		/* argc_in_out */,
    String**		/* argv_in_out */,
    String*		/* fallback_resources */
#endif
);

extern void _XtDestroyAppContexts(
#if NeedFunctionPrototypes
    void
#endif
);

extern void _XtCloseDisplays(
#if NeedFunctionPrototypes
    XtAppContext	/* app */
#endif
);

extern int _XtAppDestroyCount;

extern int _XtWaitForSomething(
#if NeedFunctionPrototypes
    XtAppContext	/* app */,
    _XtBoolean 		/* ignoreEvents */,
    _XtBoolean 		/* ignoreTimers */,
    _XtBoolean 		/* ignoreInputs */,
    _XtBoolean		/* ignoreSignals */,
    _XtBoolean 		/* block */,
#ifdef XTHREADS
    _XtBoolean		/* drop_lock */,
#endif
    unsigned long*	/* howlong */
#endif
);

typedef struct _CaseConverterRec *CaseConverterPtr;
typedef struct _CaseConverterRec {
    KeySym		start;		/* first KeySym valid in converter */
    KeySym		stop;		/* last KeySym valid in converter */
    XtCaseProc		proc;		/* case converter function */
    CaseConverterPtr	next;		/* next converter record */
} CaseConverterRec;

typedef struct _ExtensionSelectorRec {
    XtExtensionSelectProc proc;
    int min, max;
    XtPointer client_data;
} ExtSelectRec;

typedef struct _XtPerDisplayStruct {
    InternalCallbackList destroy_callbacks;
    Region region;
    CaseConverterPtr case_cvt;		/* user-registered case converters */
    XtKeyProc defaultKeycodeTranslator;
    XtAppContext appContext;
    unsigned long keysyms_serial;      /* for tracking MappingNotify events */
    KeySym *keysyms;                   /* keycode to keysym table */
    int keysyms_per_keycode;           /* number of keysyms for each keycode*/
    int min_keycode, max_keycode;      /* range of keycodes */
    KeySym *modKeysyms;                /* keysym values for modToKeysysm */
    ModToKeysymTable *modsToKeysyms;   /* modifiers to Keysysms index table*/
    unsigned char isModifier[32];      /* key-is-modifier-p bit table */
    KeySym lock_meaning;	       /* Lock modifier meaning */
    Modifiers mode_switch;	       /* keyboard group modifiers */
    Modifiers num_lock;		       /* keyboard numlock modifiers */
    Boolean being_destroyed;
    Boolean rv;			       /* reverse_video resource */
    XrmName name;		       /* resolved app name */
    XrmClass class;		       /* application class */
    Heap heap;
    struct _GCrec *GClist;	       /* support for XtGetGC */
    Drawable **pixmap_tab;             /* ditto for XtGetGC */
    String language;		       /* XPG language string */
    XEvent last_event;		       /* last event dispatched */
    Time last_timestamp;	       /* from last event dispatched */
    int multi_click_time;	       /* for XtSetMultiClickTime */
    struct _TMKeyContextRec* tm_context;     /* for XtGetActionKeysym */
    InternalCallbackList mapping_callbacks;  /* special case for TM */
    XtPerDisplayInputRec pdi;	       /* state for modal grabs & kbd focus */
    struct _WWTable *WWtable;	       /* window to widget table */
    XrmDatabase *per_screen_db;        /* per screen resource databases */
    XrmDatabase cmd_db;		       /* db from command line, if needed */
    XrmDatabase server_db;	       /* resource property else .Xdefaults */
    XtEventDispatchProc* dispatcher_list;
    ExtSelectRec* ext_select_list;
    int ext_select_count;
    Widget hook_object;
} XtPerDisplayStruct, *XtPerDisplay;

typedef struct _PerDisplayTable {
	Display *dpy;
	XtPerDisplayStruct perDpy;
	struct _PerDisplayTable *next;
} PerDisplayTable, *PerDisplayTablePtr;

extern PerDisplayTablePtr _XtperDisplayList;

extern XtPerDisplay _XtSortPerDisplayList(
#if NeedFunctionPrototypes
    Display* /* dpy */
#endif
);

extern XtPerDisplay _XtGetPerDisplay(
#if NeedFunctionPrototypes
    Display*		/* dpy */
#endif
);

extern XtPerDisplayInputRec* _XtGetPerDisplayInput(
#if NeedFunctionPrototypes
    Display* 		/* dpy */
#endif
);

#if 0
#ifdef DEBUG
#define _XtGetPerDisplay(display) \
    ((_XtperDisplayList != NULL && (_XtperDisplayList->dpy == (display))) \
     ? &_XtperDisplayList->perDpy \
     : _XtSortPerDisplayList(display))
#define _XtGetPerDisplayInput(display) \
    ((_XtperDisplayList != NULL && (_XtperDisplayList->dpy == (display))) \
     ? &_XtperDisplayList->perDpy.pdi \
     : &_XtSortPerDisplayList(display)->pdi)
#else
#define _XtGetPerDisplay(display) \
    ((_XtperDisplayList->dpy == (display)) \
     ? &_XtperDisplayList->perDpy \
     : _XtSortPerDisplayList(display))
#define _XtGetPerDisplayInput(display) \
    ((_XtperDisplayList->dpy == (display)) \
     ? &_XtperDisplayList->perDpy.pdi \
     : &_XtSortPerDisplayList(display)->pdi)
#endif /*DEBUG*/
#endif

extern void _XtDisplayInitialize(
#if NeedFunctionPrototypes
    Display*		/* dpy */,
    XtPerDisplay	/* pd */,
    _Xconst char*	/* name */,
    XrmOptionDescRec*	/* urlist */,
    Cardinal 		/* num_urs */,
    int*		/* argc */,
    char** 		/* argv */
#endif
);

extern void _XtCacheFlushTag(
#if NeedFunctionPrototypes
    XtAppContext /* app */,
    XtPointer	 /* tag */
#endif
);

extern void _XtFreeActions(
#if NeedFunctionPrototypes
    struct _ActionListRec* /* action_table */
#endif
);

extern void _XtDoPhase2Destroy(
#if NeedFunctionPrototypes
    XtAppContext /* app */,
    int		 /* dispatch_level */
#endif
);

extern void _XtDoFreeBindings(
#if NeedFunctionPrototypes
    XtAppContext /* app */
#endif
);

extern void _XtExtensionSelect(
#if NeedFunctionPrototypes
    Widget /* widget */
#endif
);

#define _XtSafeToDestroy(app) ((app)->dispatch_level == 0)

extern void _XtAllocWWTable(
#if NeedFunctionPrototypes
    XtPerDisplay pd
#endif
);

extern void _XtFreeWWTable(
#if NeedFunctionPrototypes
    XtPerDisplay pd
#endif
);
