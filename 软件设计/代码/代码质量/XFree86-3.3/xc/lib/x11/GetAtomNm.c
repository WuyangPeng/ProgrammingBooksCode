/* $XConsortium: GetAtomNm.c,v 11.23 95/05/02 15:07:06 converse Exp $ */
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

extern void _XFreeAtomTable();

/* XXX this table def is duplicated in IntAtom.c, keep them consistent! */

#define TABLESIZE 64

typedef struct _Entry {
    unsigned long sig;
    Atom atom;
} EntryRec, *Entry;

#define EntryName(e) ((char *)(e+1))

typedef struct _XDisplayAtoms {
    Entry table[TABLESIZE];
} AtomTable;

static
char *_XGetAtomName(dpy, atom)
    Display *dpy;
    Atom atom;
{
    xResourceReq *req;
    char *name;
    register Entry *table;
    register int idx;
    register Entry e;

    if (dpy->atoms) {
	table = dpy->atoms->table;
	for (idx = TABLESIZE; --idx >= 0; ) {
	    if ((e = *table++) && (e->atom == atom)) {
		idx = strlen(EntryName(e)) + 1;
		if (name = (char *)Xmalloc(idx))
		    strcpy(name, EntryName(e));
		return name;
	    }		
	}
    }
    GetResReq(GetAtomName, atom, req);
    return (char *)NULL;
}

char *XGetAtomName(dpy, atom)
    register Display *dpy;
    Atom atom;
{
    xGetAtomNameReply rep;
    char *name;

    LockDisplay(dpy);
    if (name = _XGetAtomName(dpy, atom)) {
	UnlockDisplay(dpy);
	return name;
    }	
    if (_XReply(dpy, (xReply *)&rep, 0, xFalse) == 0) {
	UnlockDisplay(dpy);
	SyncHandle();
	return(NULL);
    }
    if (name = (char *) Xmalloc(rep.nameLength+1)) {
	_XReadPad(dpy, name, (long)rep.nameLength);
	name[rep.nameLength] = '\0';
	_XUpdateAtomCache(dpy, name, atom, 0, -1, 0);
    } else {
	_XEatData(dpy, (unsigned long) (rep.nameLength + 3) & ~3);
	name = (char *) NULL;
    }
    UnlockDisplay(dpy);
    SyncHandle();
    return(name);
}

typedef struct {
    unsigned long start_seq;
    unsigned long stop_seq;
    Atom *atoms;
    char **names;
    int idx;
    int count;
    Status status;
} _XGetAtomNameState;

static
Bool _XGetAtomNameHandler(dpy, rep, buf, len, data)
    register Display *dpy;
    register xReply *rep;
    char *buf;
    int len;
    XPointer data;
{
    register _XGetAtomNameState *state;
    xGetAtomNameReply replbuf;
    register xGetAtomNameReply *repl;

    state = (_XGetAtomNameState *)data;
    if (dpy->last_request_read < state->start_seq ||
	dpy->last_request_read > state->stop_seq)
	return False;
    while (state->idx < state->count && state->names[state->idx])
	state->idx++;
    if (state->idx >= state->count)
	return False;
    if (rep->generic.type == X_Error) {
	state->status = 0;
	return False;
    }
    repl = (xGetAtomNameReply *)
	_XGetAsyncReply(dpy, (char *)&replbuf, rep, buf, len,
			(SIZEOF(xGetAtomNameReply) - SIZEOF(xReply)) >> 2,
			False);
    state->names[state->idx] = (char *) Xmalloc(repl->nameLength+1);
    _XGetAsyncData(dpy, state->names[state->idx], buf, len,
		   SIZEOF(xGetAtomNameReply), repl->nameLength,
		   repl->length << 2);
    if (state->names[state->idx]) {
	state->names[state->idx][repl->nameLength] = '\0';
	_XUpdateAtomCache(dpy, state->names[state->idx],
			  state->atoms[state->idx], 0, -1, 0);
    } else {
	state->status = 0;
    }
    return True;
}

Status
XGetAtomNames (dpy, atoms, count, names_return)
    Display *dpy;
    Atom *atoms;
    int count;
    char **names_return;
{
    _XAsyncHandler async;
    _XGetAtomNameState async_state;
    xGetAtomNameReply rep;
    int i;
    int missed = -1;

    LockDisplay(dpy);
    async_state.start_seq = dpy->request + 1;
    async_state.atoms = atoms;
    async_state.names = names_return;
    async_state.idx = 0;
    async_state.count = count - 1;
    async_state.status = 1;
    async.next = dpy->async_handlers;
    async.handler = _XGetAtomNameHandler;
    async.data = (XPointer)&async_state;
    dpy->async_handlers = &async;
    for (i = 0; i < count; i++) {
	if (!(names_return[i] = _XGetAtomName(dpy, atoms[i]))) {
	    missed = i;
	    async_state.stop_seq = dpy->request;
	}
    }
    if (missed >= 0) {
	if (_XReply(dpy, (xReply *)&rep, 0, xFalse)) {
	    if (names_return[missed] = (char *) Xmalloc(rep.nameLength+1)) {
		_XReadPad(dpy, names_return[missed], (long)rep.nameLength);
		names_return[missed][rep.nameLength] = '\0';
		_XUpdateAtomCache(dpy, names_return[missed], atoms[missed],
				  0, -1, 0);
	    } else {
		_XEatData(dpy, (unsigned long) (rep.nameLength + 3) & ~3);
		async_state.status = 0;
	    }
	}
    }
    DeqAsyncHandler(dpy, &async);
    UnlockDisplay(dpy);
    if (missed >= 0)
	SyncHandle();
    return async_state.status;
}
