/* $XConsortium: ddxFakeMtn.c /main/2 1996/01/01 10:55:18 kaleb $ */
/************************************************************
Copyright (c) 1993 by Silicon Graphics Computer Systems, Inc.

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
#define	NEED_EVENTS 1
#include <X11/X.h>
#include <X11/Xproto.h>
#include <X11/keysym.h>
#include "inputstr.h"
#include "scrnintstr.h"
#include "windowstr.h"
#include "XKBsrv.h"
#include "XI.h"

extern	WindowPtr GetSpriteWindow(
#if NeedFunctionPrototypes
	void
#endif
);

void
#if NeedFunctionPrototypes
XkbDDXFakePointerMotion(unsigned flags,int x,int y)
#else
XkbDDXFakePointerMotion(flags,x,y)
    unsigned	flags;
    int 	x;
    int 	y;
#endif
{
ScreenPtr	   pScreen;
int 		   oldX,oldY;

    pScreen= GetSpriteWindow()->drawable.pScreen;
    GetSpritePosition(&oldX,&oldY);
    if (flags&XkbSA_MoveAbsoluteX)
	 oldX=  x;
    else oldX+= x;
    if (flags&XkbSA_MoveAbsoluteY)
	 oldY=  y;
    else oldY+= y;

    if (oldX<0)				oldX= 0;
    else if (oldX>=pScreen->width)	oldX= pScreen->width-1;
    if (oldY<0)				oldY= 0;
    else if (oldY>=pScreen->height)	oldY= pScreen->height-1;

    if (pScreen->SetCursorPosition)
	(*pScreen->SetCursorPosition)(pScreen, oldX, oldY, TRUE);
    return;
}

