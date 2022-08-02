/* $TOG: Composite.c /main/24 1997/05/15 17:28:24 kaleb $ */

/***********************************************************
Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts
Copyright 1993 by Sun Microsystems, Inc. Mountain View, CA.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Digital, or Sun not be
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

#define COMPOSITE
#include "IntrinsicI.h"
#include "StringDefs.h"

static XtResource resources[] = {
    {XtNchildren, XtCReadOnly, XtRWidgetList, sizeof(WidgetList),
     XtOffsetOf(CompositeRec, composite.children), XtRImmediate, NULL},
    {XtNnumChildren, XtCReadOnly, XtRCardinal, sizeof(Cardinal),
     XtOffsetOf(CompositeRec, composite.num_children), XtRImmediate, 0},
    {XtNinsertPosition, XtCInsertPosition, XtRFunction, sizeof(XtOrderProc),
     XtOffsetOf(CompositeRec, composite.insert_position), XtRImmediate, NULL},
};

static void CompositeClassPartInitialize();
static void CompositeInitialize();
static void CompositeInsertChild();
static void CompositeDeleteChild();
static void CompositeDestroy();

externaldef(compositeclassrec) CompositeClassRec compositeClassRec = {
  { /******* CorePart *******/
    /* superclass	    */	&widgetClassRec,
    /* class_name	    */	"Composite",
    /* widget_size	    */	sizeof(CompositeRec),
    /* class_initialize     */  NULL,
    /* class_part_initialize*/	CompositeClassPartInitialize,
    /* class_inited	    */	FALSE,
    /* initialize	    */	CompositeInitialize,
    /* initialize_hook      */	NULL,		
    /* realize		    */	XtInheritRealize,
    /* actions		    */	NULL,
    /* num_actions	    */	0,
    /* resources	    */	resources,
    /* num_resources	    */	XtNumber(resources),
    /* xrm_class	    */	NULLQUARK,
    /* compress_motion      */	FALSE,
    /* compress_exposure    */	TRUE,
    /* compress_enterleave  */  FALSE,
    /* visible_interest     */	FALSE,
    /* destroy		    */	CompositeDestroy,
    /* resize		    */	NULL,
    /* expose		    */	NULL,
    /* set_values	    */	NULL,
    /* set_values_hook      */	NULL,			
    /* set_values_almost    */	XtInheritSetValuesAlmost,  
    /* get_values_hook      */	NULL,			
    /* accept_focus	    */	NULL,
    /* version		    */	XtVersion,
    /* callback_offsets     */  NULL,
    /* tm_table		    */  NULL,
    /* query_geometry	    */  NULL,
    /* display_accelerator  */	NULL,
    /* extension	    */  NULL
  },
  { /**** CompositePart *****/
    /* geometry_handler     */  NULL,
    /* change_managed       */  NULL,
    /* insert_child	    */  CompositeInsertChild,
    /* delete_child	    */  CompositeDeleteChild,
    /* extension	    */  NULL
    }
};

externaldef(compositewidgetclass) WidgetClass compositeWidgetClass = (WidgetClass) &compositeClassRec;

static void InheritAllowsChangeManagedSet(widget_class)
    WidgetClass widget_class;
{
    CompositeWidgetClass cc = (CompositeWidgetClass) widget_class;
    CompositeClassExtension ext, super_ext, new_ext;

    ext = (CompositeClassExtension)
	XtGetClassExtension(widget_class,
		    XtOffsetOf(CompositeClassRec, composite_class.extension),
			    NULLQUARK, 1L, 0);

    if (ext && ext->version == XtCompositeExtensionVersion)
	return;

    super_ext = (CompositeClassExtension)
	XtGetClassExtension(cc->core_class.superclass,
		    XtOffsetOf(CompositeClassRec, composite_class.extension),
			    NULLQUARK, 1L, 0);

    LOCK_PROCESS;
    if (super_ext && super_ext->version == XtCompositeExtensionVersion &&
	super_ext->record_size == sizeof(CompositeClassExtensionRec) &&
	super_ext->allows_change_managed_set) {

	new_ext = (CompositeClassExtension) 
	    __XtCalloc(1, sizeof(CompositeClassExtensionRec));

	/* Be careful to inherit only what is appropriate */
	new_ext->next_extension = cc->composite_class.extension;
	new_ext->record_type = NULLQUARK;
	new_ext->version = XtCompositeExtensionVersion;
	new_ext->record_size = sizeof(CompositeClassExtensionRec);
	new_ext->accepts_objects = (ext ? ext->accepts_objects : False);
	new_ext->allows_change_managed_set = True;
	cc->composite_class.extension = (XtPointer) new_ext;
    }
    UNLOCK_PROCESS;
}

static void CompositeClassPartInitialize(widgetClass)
	WidgetClass widgetClass;
{
    register CompositePartPtr wcPtr;
    register CompositePartPtr superPtr;

    wcPtr = (CompositePartPtr)
	&(((CompositeWidgetClass)widgetClass)->composite_class);

    if (widgetClass != compositeWidgetClass)
	/* don't compute possible bogus pointer */
	superPtr = (CompositePartPtr)&(((CompositeWidgetClass)widgetClass
			->core_class.superclass)->composite_class);
#ifdef lint
    else
	superPtr = NULL;
#endif

    /* We don't need to check for null super since we'll get to composite
       eventually, and it had better define them!  */

    LOCK_PROCESS;
    if (wcPtr->geometry_manager == XtInheritGeometryManager) {
	wcPtr->geometry_manager =
		superPtr->geometry_manager;
    }

    if (wcPtr->change_managed == XtInheritChangeManaged) {
	wcPtr->change_managed =
		superPtr->change_managed;
	InheritAllowsChangeManagedSet(widgetClass);
    }

    if (wcPtr->insert_child == XtInheritInsertChild) {
	wcPtr->insert_child = superPtr->insert_child;
    }

    if (wcPtr->delete_child == XtInheritDeleteChild) {
	wcPtr->delete_child = superPtr->delete_child;
    }
    UNLOCK_PROCESS;
}

static void CompositeDestroy(w)
    Widget	w;
{
    register CompositeWidget cw = (CompositeWidget) w;

    XtFree((char *) cw->composite.children);
}

static void CompositeInsertChild(w)
    Widget	w;
{
    register Cardinal	     position;
    register Cardinal        i;
    register CompositeWidget cw;
    register WidgetList      children;

    cw = (CompositeWidget) w->core.parent;
    children = cw->composite.children;

    if (cw->composite.insert_position != NULL)
	position = (*(cw->composite.insert_position))(w);
    else
	position = cw->composite.num_children;

    if (cw->composite.num_children == cw->composite.num_slots) {
	/* Allocate more space */
	cw->composite.num_slots +=  (cw->composite.num_slots / 2) + 2;
	cw->composite.children = children = 
	    (WidgetList) XtRealloc((XtPointer) children,
	    (unsigned) (cw->composite.num_slots) * sizeof(Widget));
    }
    /* Ripple children up one space from "position" */
    for (i = cw->composite.num_children; i > position; i--) {
	children[i] = children[i-1];
    }
    children[position] = w;
    cw->composite.num_children++;
}

static void CompositeDeleteChild(w)
    Widget	w;
{
    register Cardinal	     position;
    register Cardinal	     i;
    register CompositeWidget cw;

    cw = (CompositeWidget) w->core.parent;

    for (position = 0; position < cw->composite.num_children; position++) {
        if (cw->composite.children[position] == w) {
	    break;
	}
    }
    if (position == cw->composite.num_children) return;

    /* Ripple children down one space from "position" */
    cw->composite.num_children--;
    for (i = position; i < cw->composite.num_children; i++) {
        cw->composite.children[i] = cw->composite.children[i+1];
    }
}

/* ARGSUSED */
static void CompositeInitialize(requested_widget, new_widget, args, num_args)
    Widget   new_widget, requested_widget;
    ArgList args;
    Cardinal *num_args;
{
    register CompositeWidget cw;

    cw = (CompositeWidget) new_widget;
    cw->composite.num_children = 0;
    cw->composite.children = NULL;
    cw->composite.num_slots = 0;
}
