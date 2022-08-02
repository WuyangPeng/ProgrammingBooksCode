/* $XConsortium: PeekIfEv.c,v 11.16 94/04/17 20:20:24 kaleb Exp $ */
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

#define NEED_EVENTS
#include "Xlibint.h"

/*
 * return the next event in the queue that satisfies the predicate.
 * BUT do not remove it from the queue.
 * If none found, flush, and then wait until one satisfies the predicate.
 */

XPeekIfEvent (dpy, event, predicate, arg)
	register Display *dpy;
	register XEvent *event;
	Bool (*predicate)(
#if NeedNestedPrototypes
			  Display*			/* display */,
			  XEvent*			/* event */,
			  char*				/* arg */
#endif
			  );
	char *arg;
{
	register _XQEvent *prev, *qelt;
	unsigned long qe_serial = 0;

	LockDisplay(dpy);
	prev = NULL;
	while (1) {
	    for (qelt = prev ? prev->next : dpy->head;
		 qelt;
		 prev = qelt, qelt = qelt->next) {
		if(qelt->qserial_num > qe_serial
		   && (*predicate)(dpy, &qelt->event, arg)) {
		    *event = qelt->event;
		    UnlockDisplay(dpy);
		    return 0;
		}
	    }
	    if (prev)
		qe_serial = prev->qserial_num;
	    _XReadEvents(dpy);
	    if (prev && prev->qserial_num != qe_serial)
		/* another thread has snatched this event */
		prev = NULL;
	}
}

