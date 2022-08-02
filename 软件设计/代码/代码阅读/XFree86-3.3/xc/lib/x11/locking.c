/* $XConsortium: locking.c,v 1.36 94/04/17 20:22:13 rws Exp $ */
/*
 
Copyright (c) 1992  X Consortium

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

/*
 * Author: Stephen Gildea, MIT X Consortium
 *
 * locking.c - multi-thread locking routines implemented in C Threads
 */

#include "Xlibint.h"
#undef _XLockMutex
#undef _XUnlockMutex
#undef _XCreateMutex
#undef _XFreeMutex

#ifdef XTHREADS

#include "locking.h"
#ifdef XTHREADS_WARN
#include <stdio.h>		/* for warn/debug stuff */
#endif

#define NUM_FREE_CVLS 4

/* in XOpenDis.c */
extern int  (*_XInitDisplayLock_fn)();
extern void (*_XFreeDisplayLock_fn)();

/* in lcWrap.c */
extern LockInfoPtr _Xi18n_lock;

#ifdef WIN32
static DWORD _X_TlsIndex = (DWORD)-1;

_Xthread_init()
{
    if (_X_TlsIndex == (DWORD)-1)
	_X_TlsIndex = TlsAlloc();
}

struct _xthread_waiter *
_Xthread_waiter()
{
    struct _xthread_waiter *me;

    if (!(me = TlsGetValue(_X_TlsIndex))) {
	me = (struct _xthread_waiter *)xmalloc(sizeof(struct _xthread_waiter));
	me->sem = CreateSemaphore(NULL, 0, 1, NULL);
	me->next = NULL;
	TlsSetValue(_X_TlsIndex, me);
    }
    return me;
}
#endif /* WIN32 */

static xthread_t _Xthread_self()
{
    return xthread_self();
}

static LockInfoRec global_lock;
static LockInfoRec i18n_lock;

#if defined(XTHREADS_WARN) || defined(XTHREADS_FILE_LINE)
static void _XLockMutex(lip,file,line)
    LockInfoPtr lip;
    char* file;
    int line;
#else
static void _XLockMutex(lip)
    LockInfoPtr lip;
#endif
{
    xmutex_lock(lip->lock);
}

#if defined(XTHREADS_WARN) || defined(XTHREADS_FILE_LINE)
static void _XUnlockMutex(lip,file,line)
    LockInfoPtr lip;
    char* file;
    int line;
#else
static void _XUnlockMutex(lip)
    LockInfoPtr lip;
#endif
{
    xmutex_unlock(lip->lock);
}

static void _XCreateMutex(lip)
    LockInfoPtr lip;
{
    lip->lock = xmutex_malloc();
    if (lip->lock) {
	xmutex_init(lip->lock);
	xmutex_set_name(lip->lock, "Xlib");
    }
}

static void _XFreeMutex(lip)
    LockInfoPtr lip;
{
    xmutex_clear(lip->lock);
    xmutex_free(lip->lock);
}

#ifdef XTHREADS_WARN
static char *locking_file;
static int locking_line;
static xthread_t locking_thread;
static Bool xlibint_unlock = False; /* XlibInt.c may Unlock and re-Lock */

/* history that is useful to examine in a debugger */
#define LOCK_HIST_SIZE 21

static struct {
    Bool lockp;			/* True for lock, False for unlock */
    xthread_t thread;
    char *file;
    int line;
} locking_history[LOCK_HIST_SIZE];

int lock_hist_loc = 0;		/* next slot to fill */

static void _XLockDisplayWarn(dpy,file,line)
    Display *dpy;
    char *file;			/* source file, from macro */
    int line;
{
    xthread_t self;
    xthread_t old_locker;

    self = xthread_self();
    old_locker = locking_thread;
    if (xthread_have_id(old_locker)) {
	if (xthread_equal(old_locker, self))
	    printf("Xlib ERROR: %s line %d thread %x: locking display already locked at %s line %d\n",
		   file, line, self, locking_file, locking_line);
#ifdef XTHREADS_DEBUG
	else
	    printf("%s line %d: thread %x waiting on lock held by %s line %d thread %x\n",
		   file, line, self,
		   locking_file, locking_line, old_locker);
#endif /* XTHREADS_DEBUG */
    }

    xmutex_lock(dpy->lock->mutex);

    if (strcmp(file, "XlibInt.c") == 0) {
	if (!xlibint_unlock)
	    printf("Xlib ERROR: XlibInt.c line %d thread %x locking display it did not unlock\n",
		   line, self);
	xlibint_unlock = False;
    }

#ifdef XTHREADS_DEBUG
    /* if (old_locker  &&  old_locker != self) */
    if (strcmp("XClearArea.c", file) && strcmp("XDrSegs.c", file)) /* ico */
	printf("%s line %d: thread %x got display lock\n", file, line, self);
#endif /* XTHREADS_DEBUG */

    locking_thread = self;
    if (strcmp(file, "XlibInt.c") != 0) {
	locking_file = file;
	locking_line = line;
    }
    locking_history[lock_hist_loc].file = file;
    locking_history[lock_hist_loc].line = line;
    locking_history[lock_hist_loc].thread = self;
    locking_history[lock_hist_loc].lockp = True;
    lock_hist_loc++;
    if (lock_hist_loc >= LOCK_HIST_SIZE)
	lock_hist_loc = 0;
}
#endif /* XTHREADS_WARN */

#if defined(XTHREADS_WARN) || defined(XTHREADS_FILE_LINE)
static void _XUnlockDisplay(dpy,file,line)
    Display *dpy;
    char *file;
    int line;
#else
static void _XUnlockDisplay(dpy)
    Display *dpy;
#endif
{
#ifdef XTHREADS_WARN
    xthread_t self = xthread_self();

#ifdef XTHREADS_DEBUG
    if (strcmp("XClearArea.c", file) && strcmp("XDrSegs.c", file)) /* ico */
	printf("%s line %d: thread %x unlocking display\n", file, line, self);
#endif /* XTHREADS_DEBUG */

    if (!xthread_have_id(locking_thread))
	printf("Xlib ERROR: %s line %d thread %x: unlocking display that is not locked\n",
	       file, line, self);
    else if (strcmp(file, "XlibInt.c") == 0)
	xlibint_unlock = True;
#ifdef XTHREADS_DEBUG
    else if (strcmp(file, locking_file) != 0)
	/* not always an error because locking_file is not per-thread */
	printf("%s line %d: unlocking display locked from %s line %d (probably okay)\n",
	       file, line, locking_file, locking_line);
#endif /* XTHREADS_DEBUG */
    xthread_clear_id(locking_thread);

    locking_history[lock_hist_loc].file = file;
    locking_history[lock_hist_loc].line = line;
    locking_history[lock_hist_loc].thread = self;
    locking_history[lock_hist_loc].lockp = False;
    lock_hist_loc++;
    if (lock_hist_loc >= LOCK_HIST_SIZE)
	lock_hist_loc = 0;
#endif /* XTHREADS_WARN */
    xmutex_unlock(dpy->lock->mutex);
}


static struct _XCVList *_XCreateCVL(dpy)
    Display *dpy;
{
    struct _XCVList *cvl;

    if ((cvl = dpy->lock->free_cvls) != NULL) {
	dpy->lock->free_cvls = cvl->next;
	dpy->lock->num_free_cvls--;
    } else {
	cvl = (struct _XCVList *)Xmalloc(sizeof(struct _XCVList));
	if (!cvl)
	    return NULL;
	cvl->cv = xcondition_malloc();
	if (!cvl->cv) {
	    Xfree(cvl);
	    return NULL;
	}
	xcondition_init(cvl->cv);
	xcondition_set_name(cvl->cv, "Xlib read queue");
    }
    cvl->next = NULL;
    return cvl;
}

/* Put ourselves on the queue to read the connection.
   Allocates and returns a queue element. */

static struct _XCVList *
_XPushReader(dpy, tail)
    Display *dpy;
    struct _XCVList ***tail;
{
    struct _XCVList *cvl;

    cvl = _XCreateCVL(dpy);
#ifdef XTHREADS_DEBUG
    printf("_XPushReader called in thread %x, pushing %x\n",
	   xthread_self(), cvl);
#endif
    **tail = cvl;
    *tail = &cvl->next;
    return cvl;
}

/* signal the next thread waiting to read the connection */

static void _XPopReader(dpy, list, tail)
    Display *dpy;
    struct _XCVList **list;
    struct _XCVList ***tail;
{
    register struct _XCVList *front = *list;

#ifdef XTHREADS_DEBUG
    printf("_XPopReader called in thread %x, popping %x\n",
	   xthread_self(), front);
#endif

    if (dpy->flags & XlibDisplayProcConni)
	/* we never added ourself in the first place */
	return;

    if (front) {		/* check "front" for paranoia */
	*list = front->next;
	if (*tail == &front->next)	/* did we free the last elt? */
	    *tail = list;
	if (dpy->lock->num_free_cvls < NUM_FREE_CVLS) {
	    front->next = dpy->lock->free_cvls;
	    dpy->lock->free_cvls = front;
	    dpy->lock->num_free_cvls++;
	} else {
	    xcondition_clear(front->cv);
	    Xfree((char *)front->cv);
	    Xfree((char *)front);
	}
    }

    /* signal new front after it is in place */
    if (dpy->lock->reply_first = (dpy->lock->reply_awaiters != NULL)) {
	ConditionSignal(dpy, dpy->lock->reply_awaiters->cv);
    } else if (dpy->lock->event_awaiters) {
	ConditionSignal(dpy, dpy->lock->event_awaiters->cv);
    }
}

#if defined(XTHREADS_WARN) || defined(XTHREADS_FILE_LINE)
static void _XConditionWait(cv, mutex,file,line)
    xcondition_t cv;
    xmutex_t mutex;
    char *file;
    int line;
#else
static void _XConditionWait(cv, mutex)
    xcondition_t cv;
    xmutex_t mutex;
#endif
{
#ifdef XTHREADS_WARN
    xthread_t self = xthread_self();
    char *old_file = locking_file;
    int old_line = locking_line;
    
#ifdef XTHREADS_DEBUG
    printf("line %d thread %x in condition wait\n", line, self);
#endif
    xthread_clear_id(locking_thread);

    locking_history[lock_hist_loc].file = file;
    locking_history[lock_hist_loc].line = line;
    locking_history[lock_hist_loc].thread = self;
    locking_history[lock_hist_loc].lockp = False;
    lock_hist_loc++;
    if (lock_hist_loc >= LOCK_HIST_SIZE)
	lock_hist_loc = 0;
#endif /* XTHREADS_WARN */

    xcondition_wait(cv, mutex);

#ifdef XTHREADS_WARN
    locking_thread = self;
    locking_file = old_file;
    locking_line = old_line;

    locking_history[lock_hist_loc].file = file;
    locking_history[lock_hist_loc].line = line;
    locking_history[lock_hist_loc].thread = self;
    locking_history[lock_hist_loc].lockp = True;
    lock_hist_loc++;
    if (lock_hist_loc >= LOCK_HIST_SIZE)
	lock_hist_loc = 0;
#ifdef XTHREADS_DEBUG
    printf("line %d thread %x was signaled\n", line, self);
#endif /* XTHREADS_DEBUG */
#endif /* XTHREADS_WARN */
}

#if defined(XTHREADS_WARN) || defined(XTHREADS_FILE_LINE)
static void _XConditionSignal(cv,file,line)
    xcondition_t cv;
    char *file;
    int line;
#else
static void _XConditionSignal(cv)
    xcondition_t cv;
#endif
{
#ifdef XTHREADS_WARN
#ifdef XTHREADS_DEBUG
    printf("line %d thread %x is signalling\n", line, xthread_self());
#endif
#endif
    xcondition_signal(cv);
}
    

#if defined(XTHREADS_WARN) || defined(XTHREADS_FILE_LINE)
static void _XConditionBroadcast(cv,file,line)
    xcondition_t cv;
    char *file;
    int line;
#else
static void _XConditionBroadcast(cv)
    xcondition_t cv;
#endif
{
#ifdef XTHREADS_WARN
#ifdef XTHREADS_DEBUG
    printf("line %d thread %x is broadcasting\n", line, xthread_self());
#endif
#endif
    xcondition_broadcast(cv);
}
    

static void _XFreeDisplayLock(dpy)
    Display *dpy;
{
    struct _XCVList *cvl;

    if (dpy->lock != NULL) {
	if (dpy->lock->mutex != NULL) {
	    xmutex_clear(dpy->lock->mutex);
	    xmutex_free(dpy->lock->mutex);
	}
	if (dpy->lock->cv != NULL) {
	    xcondition_clear(dpy->lock->cv);
	    xcondition_free(dpy->lock->cv);
	}
	if (dpy->lock->writers != NULL) {
	    xcondition_clear(dpy->lock->writers);
	    xcondition_free(dpy->lock->writers);
	}
	while (cvl = dpy->lock->free_cvls) {
	    dpy->lock->free_cvls = cvl->next;
	    xcondition_clear(cvl->cv);
	    Xfree((char *)cvl->cv);
	    Xfree((char *)cvl);
	}
	Xfree((char *)dpy->lock);
	dpy->lock = NULL;
    }
    if (dpy->lock_fns != NULL) {
	Xfree((char *)dpy->lock_fns);
	dpy->lock_fns = NULL;
    }
}

/*
 * wait for thread with user-level display lock to release it.
 */

static void _XDisplayLockWait(dpy)
    Display *dpy;
{
    xthread_t self;

    while (dpy->lock->locking_level > 0) {
	self = xthread_self();
	if (xthread_equal(dpy->lock->locking_thread, self))
	    break;
	ConditionWait(dpy, dpy->lock->cv);
    }
}

#if defined(XTHREADS_WARN) || defined(XTHREADS_FILE_LINE)
static void _XLockDisplay(dpy, file, line)
    Display *dpy;
    char *file;			/* source file, from macro */
    int line;
#else
static void _XLockDisplay(dpy)
    Display *dpy;
#endif
{
#ifdef XTHREADS_WARN
    _XLockDisplayWarn(dpy, file, line);
#else
    xmutex_lock(dpy->lock->mutex);
#endif
    if (dpy->lock->locking_level > 0)
	_XDisplayLockWait(dpy);
}

/*
 * _XReply is allowed to exit from select/poll and clean up even if a
 * user-level lock is in force, so it uses this instead of _XFancyLockDisplay.
 */
#if defined(XTHREADS_WARN) || defined(XTHREADS_FILE_LINE)
static void _XInternalLockDisplay(dpy, wskip, file, line)
    Display *dpy;
    Bool wskip;
    char *file;			/* source file, from macro */
    int line;
#else
static void _XInternalLockDisplay(dpy, wskip)
    Display *dpy;
    Bool wskip;
#endif
{
#ifdef XTHREADS_WARN
    _XLockDisplayWarn(dpy, file, line);
#else
    xmutex_lock(dpy->lock->mutex);
#endif
    if (!wskip && dpy->lock->locking_level > 0)
	_XDisplayLockWait(dpy);
}

#if NeedFunctionPrototypes
static void _XUserLockDisplay(
    register Display* dpy)
#else
static void _XUserLockDisplay(dpy)
    register Display* dpy;
#endif
{
    if (++dpy->lock->locking_level == 1) {
	dpy->lock->lock_wait = _XDisplayLockWait;
	dpy->lock->locking_thread = xthread_self();
    }
}

#if NeedFunctionPrototypes
void _XUserUnlockDisplay(
    register Display* dpy)
#else
void _XUserUnlockDisplay(dpy)
    register Display* dpy;
#endif
{
    if (dpy->lock->locking_level > 0 && --dpy->lock->locking_level == 0) {
	/* signal other threads that might be waiting in XLockDisplay */
	ConditionBroadcast(dpy, dpy->lock->cv);
	dpy->lock->lock_wait = NULL;
	xthread_clear_id(dpy->lock->locking_thread);
    }
}

/* returns 0 if initialized ok, -1 if unable to allocate
   a mutex or other memory */

static int _XInitDisplayLock(dpy)
    Display *dpy;
{
    dpy->lock_fns = (struct _XLockPtrs*)Xmalloc(sizeof(struct _XLockPtrs));
    if (dpy->lock_fns == NULL)
	return -1;
    dpy->lock = (struct _XLockInfo *)Xmalloc(sizeof(struct _XLockInfo));
    if (dpy->lock == NULL) {
	_XFreeDisplayLock(dpy);
	return -1;
    }
    dpy->lock->cv = xcondition_malloc();
    dpy->lock->mutex = xmutex_malloc();
    dpy->lock->writers = xcondition_malloc();
    if (!dpy->lock->cv || !dpy->lock->mutex || !dpy->lock->writers) {
	_XFreeDisplayLock(dpy);
	return -1;
    }

    dpy->lock->reply_bytes_left = 0;
    dpy->lock->reply_was_read = False;
    dpy->lock->reply_awaiters = NULL;
    dpy->lock->reply_awaiters_tail = &dpy->lock->reply_awaiters;
    dpy->lock->event_awaiters = NULL;
    dpy->lock->event_awaiters_tail = &dpy->lock->event_awaiters;
    dpy->lock->reply_first = False;
    dpy->lock->locking_level = 0;
    dpy->lock->num_free_cvls = 0;
    dpy->lock->free_cvls = NULL;
    xthread_clear_id(dpy->lock->locking_thread);
    xthread_clear_id(dpy->lock->reading_thread);
    xthread_clear_id(dpy->lock->conni_thread);
    xmutex_init(dpy->lock->mutex);
    xmutex_set_name(dpy->lock->mutex, "Xlib Display");
    xcondition_init(dpy->lock->cv);
    xcondition_set_name(dpy->lock->cv, "XLockDisplay");
    xcondition_init(dpy->lock->writers);
    xcondition_set_name(dpy->lock->writers, "Xlib wait for writable");
    dpy->lock_fns->lock_display = _XLockDisplay;
    dpy->lock->internal_lock_display = _XInternalLockDisplay;
    dpy->lock_fns->unlock_display = _XUnlockDisplay;
    dpy->lock->user_lock_display = _XUserLockDisplay;
    dpy->lock->user_unlock_display = _XUserUnlockDisplay;
    dpy->lock->pop_reader = _XPopReader;
    dpy->lock->push_reader = _XPushReader;
    dpy->lock->condition_wait = _XConditionWait;
    dpy->lock->condition_signal = _XConditionSignal;
    dpy->lock->condition_broadcast = _XConditionBroadcast;
    dpy->lock->create_cvl = _XCreateCVL;
    dpy->lock->lock_wait = NULL; /* filled in by XLockDisplay() */

    return 0;
}


Status XInitThreads()
{
    if (_Xglobal_lock)
	return 1;
#ifdef xthread_init
    xthread_init();		/* return value? */
#endif
    if (!(global_lock.lock = xmutex_malloc()))
	return 0;
    if (!(i18n_lock.lock = xmutex_malloc())) {
	xmutex_free(global_lock.lock);
	global_lock.lock = NULL;
	return 0;
    }
    _Xglobal_lock = &global_lock;
    xmutex_init(_Xglobal_lock->lock);
    xmutex_set_name(_Xglobal_lock->lock, "Xlib global");
    _Xi18n_lock = &i18n_lock;
    xmutex_init(_Xi18n_lock->lock);
    xmutex_set_name(_Xi18n_lock->lock, "Xlib i18n");
    _XLockMutex_fn = _XLockMutex;
    _XUnlockMutex_fn = _XUnlockMutex;
    _XCreateMutex_fn = _XCreateMutex;
    _XFreeMutex_fn = _XFreeMutex;
    _XInitDisplayLock_fn = _XInitDisplayLock;
    _XFreeDisplayLock_fn = _XFreeDisplayLock;
    _Xthread_self_fn = _Xthread_self;

#ifdef XTHREADS_WARN
#ifdef XTHREADS_DEBUG
    setlinebuf(stdout);		/* for debugging messages */
#endif
#endif

    return 1;
}

#else /* XTHREADS */
Status XInitThreads()
{
    return 0;
}
#endif /* XTHREADS */
