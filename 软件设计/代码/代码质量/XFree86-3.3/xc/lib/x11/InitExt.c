/* $XConsortium: InitExt.c /main/22 1996/10/22 14:19:47 kaleb $ */
/*

Copyright (c) 1987  X Consortium

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
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

#include <X11/Xlibint.h>
#include <X11/Xos.h>
#include <stdio.h>

extern Bool _XUnknownWireEvent();
extern Status _XUnknownNativeEvent();
extern Bool _XDefaultWireError();

/*
 * This routine is used to link a extension in so it will be called
 * at appropriate times.
 */

#if NeedFunctionPrototypes
XExtCodes *XInitExtension (
	Display *dpy,
	_Xconst char *name)
#else
XExtCodes *XInitExtension (dpy, name)
	Display *dpy;
	char *name;
#endif
{
	XExtCodes codes;	/* temp. place for extension information. */
	register _XExtension *ext;/* need a place to build it all */
	if (!XQueryExtension(dpy, name, 
		&codes.major_opcode, &codes.first_event,
		&codes.first_error)) return (NULL);

	LockDisplay (dpy);
	if (! (ext = (_XExtension *) Xcalloc (1, sizeof (_XExtension))) ||
	    ! (ext->name = Xmalloc((unsigned) strlen(name) + 1))) {
	    if (ext) Xfree((char *) ext);
	    UnlockDisplay(dpy);
	    return (XExtCodes *) NULL;
	}
	codes.extension = dpy->ext_number++;
	ext->codes = codes;
	(void) strcpy(ext->name, name);

	/* chain it onto the display list */	
	ext->next = dpy->ext_procs;
	dpy->ext_procs = ext;
	UnlockDisplay (dpy);

	return (&ext->codes);		/* tell him which extension */
}

XExtCodes *XAddExtension (dpy)
    Display *dpy;
{
    register _XExtension *ext;

    LockDisplay (dpy);
    if (! (ext = (_XExtension *) Xcalloc (1, sizeof (_XExtension)))) {
	UnlockDisplay(dpy);
	return (XExtCodes *) NULL;
    }
    ext->codes.extension = dpy->ext_number++;

    /* chain it onto the display list */
    ext->next = dpy->ext_procs;
    dpy->ext_procs = ext;
    UnlockDisplay (dpy);

    return (&ext->codes);		/* tell him which extension */
}

static _XExtension *XLookupExtension (dpy, extension)
	register Display *dpy;	/* display */
	register int extension;	/* extension number */
{
	register _XExtension *ext;
	for (ext = dpy->ext_procs; ext; ext = ext->next)
	    if (ext->codes.extension == extension) return (ext);
	return (NULL);
}

XExtData **XEHeadOfExtensionList(object)
    XEDataObject object;
{
    return *(XExtData ***)&object;
}

XAddToExtensionList(structure, ext_data)
    XExtData **structure;
    XExtData *ext_data;
{
    ext_data->next = *structure;
    *structure = ext_data;
    return 1;
}

XExtData *XFindOnExtensionList(structure, number)
    XExtData **structure;
    int number;
{
    XExtData *ext;

    ext = *structure;
    while (ext && (ext->number != number))
	ext = ext->next;
    return ext;
}

typedef int (*CreateGCType) (
#if NeedFunctionPrototypes
    Display*	/* display */,
    GC		/* gc */,
    XExtCodes*	/* codes */
#endif
);

/*
 * Routines to hang procs on the extension structure.
 */
CreateGCType XESetCreateGC(dpy, extension, proc)
	Display *dpy;		/* display */
	int extension;		/* extension number */
	CreateGCType proc;	/* routine to call when GC created */
{
	register _XExtension *e;	/* for lookup of extension */
	register int (*oldproc)();
	if ((e = XLookupExtension (dpy, extension)) == NULL) return (NULL);
	LockDisplay(dpy);
	oldproc = e->create_GC;
	e->create_GC = proc;
	UnlockDisplay(dpy);
	return (CreateGCType)oldproc;
}

typedef int (*CopyGCType)(
#if NeedFunctionPrototypes
    Display*	/* display */,
    GC		/* gc */,
    XExtCodes*	/* codes */
#endif
);

CopyGCType XESetCopyGC(dpy, extension, proc)
	Display *dpy;		/* display */
	int extension;		/* extension number */
	CopyGCType proc;	/* routine to call when GC copied */
{
	register _XExtension *e;	/* for lookup of extension */
	register int (*oldproc)();
	if ((e = XLookupExtension (dpy, extension)) == NULL) return (NULL);
	LockDisplay(dpy);
	oldproc = e->copy_GC;
	e->copy_GC = proc;
	UnlockDisplay(dpy);
	return (CopyGCType)oldproc;
}

typedef int (*FlushGCType) (
#if NeedFunctionPrototypes
    Display*	/* display */,
    GC		/* gc */,
    XExtCodes*	/* codes */
#endif
);

FlushGCType XESetFlushGC(dpy, extension, proc)
	Display *dpy;		/* display */
	int extension;		/* extension number */
	FlushGCType proc;	/* routine to call when GC copied */
{
	register _XExtension *e;	/* for lookup of extension */
	register int (*oldproc)();
	if ((e = XLookupExtension (dpy, extension)) == NULL) return (NULL);
	LockDisplay(dpy);
	oldproc = e->flush_GC;
	e->flush_GC = proc;
	UnlockDisplay(dpy);
	return (FlushGCType)oldproc;
}

typedef int (*FreeGCType) (
#if NeedFunctionPrototypes
    Display*	/* display */,
    GC		/* gc */,
    XExtCodes*	/* codes */
#endif
);

FreeGCType XESetFreeGC(dpy, extension, proc)
	Display *dpy;		/* display */
	int extension;		/* extension number */
	FreeGCType proc;	/* routine to call when GC freed */
{
	register _XExtension *e;	/* for lookup of extension */
	register int (*oldproc)();
	if ((e = XLookupExtension (dpy, extension)) == NULL) return (NULL);
	LockDisplay(dpy);
	oldproc = e->free_GC;
	e->free_GC = proc;
	UnlockDisplay(dpy);
	return (FreeGCType)oldproc;
}

typedef int (*CreateFontType) (
#if NeedFunctionPrototypes
    Display*	/* display */,
    XFontStruct* /* fs */,
    XExtCodes*	/* codes */
#endif
);

CreateFontType XESetCreateFont(dpy, extension, proc)
	Display *dpy;		/* display */
	int extension;		/* extension number */
	CreateFontType proc;	/* routine to call when font created */
{
	register _XExtension *e;	/* for lookup of extension */
	register int (*oldproc)();
	if ((e = XLookupExtension (dpy, extension)) == NULL) return (NULL);
	LockDisplay(dpy);
	oldproc = e->create_Font;
	e->create_Font = proc;
	UnlockDisplay(dpy);
	return (CreateFontType)oldproc;
}

typedef int (*FreeFontType) (
#if NeedFunctionPrototypes
    Display*	/* display */,
    XFontStruct* /* fs */,
    XExtCodes*	/* codes */
#endif
);

FreeFontType XESetFreeFont(dpy, extension, proc)
	Display *dpy;		/* display */
	int extension;		/* extension number */
	FreeFontType proc;	/* routine to call when font freed */
{
	register _XExtension *e;	/* for lookup of extension */
	register int (*oldproc)();
	if ((e = XLookupExtension (dpy, extension)) == NULL) return (NULL);
	LockDisplay(dpy);
	oldproc = e->free_Font;
	e->free_Font = proc;
	UnlockDisplay(dpy);
	return (FreeFontType)oldproc;
}

typedef int (*CloseDisplayType) (
#if NeedFunctionPrototypes
    Display*	/* display */,
    XExtCodes*	/* codes */
#endif
);

CloseDisplayType XESetCloseDisplay(dpy, extension, proc)
	Display *dpy;		/* display */
	int extension;		/* extension number */
	CloseDisplayType proc;	/* routine to call when display closed */
{
	register _XExtension *e;	/* for lookup of extension */
	register int (*oldproc)();
	if ((e = XLookupExtension (dpy, extension)) == NULL) return (NULL);
	LockDisplay(dpy);
	oldproc = e->close_display;
	e->close_display = proc;
	UnlockDisplay(dpy);
	return (CloseDisplayType)oldproc;
}

typedef Bool (*WireToEventType) (
#if NeedFunctionPrototypes
    Display*	/* display */,
    XEvent*	/* re */,
    xEvent*	/* event */
#endif
);

WireToEventType XESetWireToEvent(dpy, event_number, proc)
	Display *dpy;		/* display */
	WireToEventType proc;	/* routine to call when converting event */
	int event_number;	/* event routine to replace */
{
	register Bool (*oldproc)();
	if (proc == NULL) proc = (WireToEventType)_XUnknownWireEvent;
	LockDisplay (dpy);
	oldproc = dpy->event_vec[event_number];
	dpy->event_vec[event_number] = proc;
	UnlockDisplay (dpy);
	return (WireToEventType)oldproc;
}

typedef Status (*EventToWireType) (
#if NeedFunctionPrototypes
    Display*	/* display */,
    XEvent*	/* re */,
    xEvent*	/* event */
#endif
);

EventToWireType XESetEventToWire(dpy, event_number, proc)
	Display *dpy;		/* display */
	EventToWireType proc;	/* routine to call when converting event */
	int event_number;	/* event routine to replace */
{
	register Status (*oldproc)();
	if (proc == NULL) proc = (EventToWireType) _XUnknownNativeEvent;
	LockDisplay (dpy);
	oldproc = dpy->wire_vec[event_number];
	dpy->wire_vec[event_number] = proc;
	UnlockDisplay(dpy);
	return (EventToWireType)oldproc;
}

typedef Bool (*WireToErrorType) (
#if NeedFunctionPrototypes
    Display*	/* display */,
    XErrorEvent* /* he */,
    xError*	/* we */
#endif
);

WireToErrorType XESetWireToError(dpy, error_number, proc)
	Display *dpy;		/* display */
	WireToErrorType proc;	/* routine to call when converting error */
	int error_number;	/* error routine to replace */
{
	register Bool (*oldproc)();
	if (proc == NULL) proc = (WireToErrorType)_XDefaultWireError;
	LockDisplay (dpy);
	if (!dpy->error_vec) {
	    int i;
	    dpy->error_vec = (Bool (**)())Xmalloc(256 * sizeof(oldproc));
	    for (i = 1; i < 256; i++)
		dpy->error_vec[i] = _XDefaultWireError;
	}
	if (dpy->error_vec) {
	    oldproc = dpy->error_vec[error_number];
	    dpy->error_vec[error_number] = proc;
	}
	UnlockDisplay (dpy);
	return (WireToErrorType)oldproc;
}

typedef int (*ErrorType) (
#if NeedFunctionPrototypes
    Display*	/* display */,
    xError*	/* err */,
    XExtCodes*	/* codes */,
    int*	/* ret_code */
#endif
);

ErrorType XESetError(dpy, extension, proc)
	Display *dpy;		/* display */
	int extension;		/* extension number */
	ErrorType proc;		/* routine to call when X error happens */
{
	register _XExtension *e;	/* for lookup of extension */
	register int (*oldproc)();
	if ((e = XLookupExtension (dpy, extension)) == NULL) return (NULL);
	LockDisplay(dpy);
	oldproc = e->error;
	e->error = proc;
	UnlockDisplay(dpy);
	return (ErrorType)oldproc;
}

typedef char* (*ErrorStringType) (
#if NeedFunctionPrototypes
    Display*	/* display */,
    int		/* code */,
    XExtCodes*	/* codes */,
    char*	/* buffer */,
    int		/* nbytes */
#endif
);

ErrorStringType XESetErrorString(dpy, extension, proc)
	Display *dpy;		/* display */
	int extension;		/* extension number */
	ErrorStringType proc;	/* routine to call when I/O error happens */
{
	register _XExtension *e;	/* for lookup of extension */
	register char *(*oldproc)();
	if ((e = XLookupExtension (dpy, extension)) == NULL) return (NULL);
	LockDisplay(dpy);
	oldproc = e->error_string;
	e->error_string = proc;
	UnlockDisplay(dpy);
	return (ErrorStringType)oldproc;
}

typedef void (*PrintErrorType)(
#if NeedFunctionPrototypes
    Display*	/* display */,
    XErrorEvent* /* ev */,
    void*	/* fp */
#endif
);

PrintErrorType XESetPrintErrorValues(dpy, extension, proc)
	Display *dpy;		/* display */
	int extension;		/* extension number */
	PrintErrorType proc;	/* routine to call to print */
{
	register _XExtension *e;	/* for lookup of extension */
	register void (*oldproc)();
	if ((e = XLookupExtension (dpy, extension)) == NULL) return (NULL);
	LockDisplay(dpy);
	oldproc = e->error_values;
	e->error_values = proc;
	UnlockDisplay(dpy);
	return (PrintErrorType)oldproc;
}

typedef void (*BeforeFlushType)(
#if NeedFunctionPrototypes
    Display*	/* display */,
    XExtCodes*	/* codes */,
    char*	/* data */,
    long	/* len */
#endif
);

BeforeFlushType XESetBeforeFlush(dpy, extension, proc)
	Display *dpy;		/* display */
	int extension;		/* extension number */
	BeforeFlushType proc;	/* routine to call on flush */
{
	register _XExtension *e;	/* for lookup of extension */
	register void (*oldproc)();
	register _XExtension *ext;
	if ((e = XLookupExtension (dpy, extension)) == NULL) return (NULL);
	LockDisplay(dpy);
	oldproc = e->before_flush;
	e->before_flush = proc;
	for (ext = dpy->flushes; ext && ext != e; ext = ext->next)
	    ;
	if (!ext) {
	    e->next_flush = dpy->flushes;
	    dpy->flushes = e;
	}	    
	UnlockDisplay(dpy);
	return (BeforeFlushType)oldproc;
}
