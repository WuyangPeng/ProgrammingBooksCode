/* $XConsortium: xkbatom.c /main/3 1996/08/31 12:45:22 kaleb $ */
/* $XFree86: xc/lib/xkbfile/xkbatom.c,v 3.3 1996/12/23 06:04:03 dawes Exp $ */
/***********************************************************

Copyright (c) 1987  X Consortium

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


Copyright 1987 by Digital Equipment Corporation, Maynard, Massachusetts.

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

/************************************************************
 Copyright (c) 1994 by Silicon Graphics Computer Systems, Inc.

 Permission to use, copy, modify, and distribute this
 software and its documentation for any purpose and without
 fee is hereby granted, provided that the above copyright
 notice appear in all copies and that both that copyright
 notice and this permission notice appear in supporting
 documentation, and that the name of Silicon Graphics not be 
 used in advertising or publicity pertaining to distribution 
 of the software without specific prior written permission.
 Silicon Graphics makes no representation about the suitability 
 of this software for any purpose. It is provided "as is"
 without any express or implied warranty.
 
 SILICON GRAPHICS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS 
 SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY 
 AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL SILICON
 GRAPHICS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
 DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, 
 DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE 
 OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
 THE USE OR PERFORMANCE OF THIS SOFTWARE.

 ********************************************************/

#include <stdio.h>
#include <ctype.h>
#ifndef X_NOT_STDC_ENV
#include <stdlib.h>
#endif
#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>

#include "XKMformat.h"
#include "XKBfileInt.h"

/***====================================================================***/

#define InitialTableSize 100

typedef struct _Node {
    struct _Node   *left,   *right;
    Atom a;
    unsigned int fingerPrint;
    char   *string;
} NodeRec, *NodePtr;

#define BAD_RESOURCE 0xe0000000

static Atom lastAtom = None;
static NodePtr atomRoot = (NodePtr)NULL;
static unsigned long tableLength;
static NodePtr *nodeTable;

static Atom 
#if NeedFunctionPrototypes
_XkbMakeAtom(char *string,unsigned len,Bool makeit)
#else
_XkbMakeAtom(string, len, makeit)
    char *string;
    unsigned len;
    Bool makeit;
#endif
{
    register    NodePtr * np;
    unsigned i;
    int     comp;
    register unsigned int   fp = 0;

    np = &atomRoot;
    for (i = 0; i < (len+1)/2; i++)
    {
	fp = fp * 27 + string[i];
	fp = fp * 27 + string[len - 1 - i];
    }
    while (*np != (NodePtr) NULL)
    {
	if (fp < (*np)->fingerPrint)
	    np = &((*np)->left);
	else if (fp > (*np)->fingerPrint)
	    np = &((*np)->right);
	else
	{			       /* now start testing the strings */
	    comp = strncmp(string, (*np)->string, (int)len);
	    if ((comp < 0) || ((comp == 0) && (len < strlen((*np)->string))))
		np = &((*np)->left);
	    else if (comp > 0)
		np = &((*np)->right);
	    else
		return(*np)->a;
	    }
    }
    if (makeit)
    {
	register NodePtr nd;

	nd = (NodePtr) _XkbAlloc(sizeof(NodeRec));
	if (!nd)
	    return BAD_RESOURCE;
	nd->string = (char *) _XkbAlloc(len + 1);
	if (!nd->string) {
	    _XkbFree(nd);
	    return BAD_RESOURCE;
	}
	strncpy(nd->string, string, (int)len);
	nd->string[len] = 0;
	if ((lastAtom + 1) >= tableLength) {
	    NodePtr *table;

	    table = (NodePtr *) _XkbRealloc(nodeTable,
					 tableLength * (2 * sizeof(NodePtr)));
	    if (!table) {
		if (nd->string != string)
		    _XkbFree(nd->string);
		_XkbFree(nd);
		return BAD_RESOURCE;
	    }
	    tableLength <<= 1;
	    nodeTable = table;
	}
	*np = nd;
	nd->left = nd->right = (NodePtr) NULL;
	nd->fingerPrint = fp;
	nd->a = (++lastAtom);
	*(nodeTable+lastAtom) = nd;
	return nd->a;
    }
    else
	return None;
}

static char *
#if NeedFunctionPrototypes
_XkbNameForAtom(Atom atom)
#else
_XkbNameForAtom(atom)
    Atom atom;
#endif
{
    NodePtr node;
    if (atom > lastAtom) return 0;
    if ((node = nodeTable[atom]) == (NodePtr)NULL) return 0;
    return node->string;
}

static void
#if NeedFunctionPrototypes
_XkbInitAtoms(void)
#else
_XkbInitAtoms()
#endif
{
    tableLength = InitialTableSize;
    nodeTable = (NodePtr *)_XkbAlloc(InitialTableSize*sizeof(NodePtr));
    nodeTable[None] = (NodePtr)NULL;
}
    
/***====================================================================***/

char *
#if NeedFunctionPrototypes
XkbAtomGetString(Display *dpy,Atom atm)
#else
XkbAtomGetString(dpy,atm)
    Display *	dpy;
    Atom 	atm;
#endif
{
    if (atm==None)
	return NULL;
    if (dpy==NULL)
	return _XkbNameForAtom(atm);
    return XGetAtomName(dpy,atm);
}

/***====================================================================***/

Atom
#if NeedFunctionPrototypes
XkbInternAtom(Display *dpy,char *name,Bool onlyIfExists)
#else
XkbInternAtom(dpy,name,onlyIfExists)
    Display *	dpy;
    char *	name;
    Bool	onlyIfExists;
#endif
{
    if (name==NULL)
	return None;
    if (dpy==NULL) {
	return _XkbMakeAtom(name, strlen(name), (!onlyIfExists));
    }
    return XInternAtom(dpy,name,onlyIfExists);
}

/***====================================================================***/

Atom
#if NeedFunctionPrototypes
XkbChangeAtomDisplay(Display *oldDpy,Display *newDpy,Atom atm)
#else
XkbChangeAtomDisplay(oldDpy,newDpy,atm)
    Display *	oldDpy;
    Display *	newDpy;
    Atom	atm;
#endif
{
char *tmp;

    if (atm!=None) {
	tmp= XkbAtomGetString(oldDpy,atm);
	if (tmp!=NULL)
	    return XkbInternAtom(newDpy,tmp,False);
    }
    return None;
}

/***====================================================================***/

void
#if NeedFunctionPrototypes
XkbInitAtoms(Display *dpy)
#else
XkbInitAtoms(dpy)
    Display *dpy;
#endif
{
static int been_here= 0;
    if ((dpy==NULL)&&(!been_here)) {
	_XkbInitAtoms();
	been_here= 1;
    }
    return;
}
