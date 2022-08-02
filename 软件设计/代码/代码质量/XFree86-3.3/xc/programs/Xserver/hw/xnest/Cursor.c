/* $XConsortium: Cursor.c /main/5 1996/09/28 17:13:30 rws $ */
/*

Copyright 1993 by Davor Matic

Permission to use, copy, modify, distribute, and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation.  Davor Matic makes no representations about
the suitability of this software for any purpose.  It is provided "as
is" without express or implied warranty.

*/
#include "X.h"
#include "Xproto.h"
#include "screenint.h"
#include "input.h"
#include "misc.h"
#include "cursor.h"
#include "cursorstr.h"
#include "scrnintstr.h"
#include "servermd.h"

#include "Xnest.h"

#include "Display.h"
#include "Screen.h"
#include "Cursor.h"
#include "Visual.h"
#include "Keyboard.h"
#include "Args.h"

void xnestConstrainCursor(pScreen, pBox)
     ScreenPtr pScreen;
     BoxPtr pBox;
{
#ifdef _XSERVER64
  Window64 wroot;
#else
  Window wroot;
#endif

  int wx, wy;
  unsigned int wwidth, wheight;
  unsigned int wborderwidth;
  unsigned int wdepth;
  
  XGetGeometry(xnestDisplay, xnestDefaultWindows[pScreen->myNum], &wroot,
	       &wx, &wy, &wwidth, &wheight, &wborderwidth, &wdepth);
  
  if (pBox->x1 <= 0 && pBox->y1 <= 0 &&
      pBox->x2 >= wwidth && pBox->y2 >= wheight)
    XUngrabPointer(xnestDisplay, CurrentTime);
  else {
    XReparentWindow(xnestDisplay, xnestConfineWindow, 
		    xnestDefaultWindows[pScreen->myNum],
		    pBox->x1, pBox->y1);
    XResizeWindow(xnestDisplay, xnestConfineWindow,
		  pBox->x2 - pBox->x1, pBox->y2 - pBox->y1);
    
    XGrabPointer(xnestDisplay, 
		 xnestDefaultWindows[pScreen->myNum], 
		 True,
		 xnestEventMask & (~XNEST_KEYBOARD_EVENT_MASK|KeymapStateMask),
		 GrabModeAsync, GrabModeAsync, 
		 xnestConfineWindow,
		 None, CurrentTime);
  }
}

void xnestCursorLimits(pScreen, pCursor, pHotBox, pTopLeftBox)
     ScreenPtr pScreen;
     CursorPtr pCursor;
     BoxPtr pHotBox;
     BoxPtr pTopLeftBox;
{
  *pTopLeftBox = *pHotBox;		   
}

Bool xnestDisplayCursor(pScreen, pCursor)
     ScreenPtr pScreen;
     CursorPtr pCursor;
{
  XDefineCursor(xnestDisplay, 
		xnestDefaultWindows[pScreen->myNum], 
		xnestCursor(pCursor, pScreen));
  return True;
}

Bool xnestRealizeCursor(pScreen, pCursor)
     ScreenPtr pScreen;
     CursorPtr pCursor;
{
  XImage *ximage;
  Pixmap source, mask;
  XColor fg_color, bg_color;
  unsigned long valuemask;
  XGCValues values;

  valuemask = GCFunction | 
              GCPlaneMask | 
	      GCForeground |
	      GCBackground |
	      GCClipMask;

  values.function = GXcopy;
  values.plane_mask = AllPlanes;
  values.foreground = 1L;
  values.background = 0L;
  values.clip_mask = None;

  XChangeGC(xnestDisplay, xnestBitmapGC, valuemask, &values);

  source = XCreatePixmap(xnestDisplay, 
			 xnestDefaultWindows[pScreen->myNum],
			 pCursor->bits->width,
			 pCursor->bits->height,
			 1);
  
  mask   = XCreatePixmap(xnestDisplay, 
			 xnestDefaultWindows[pScreen->myNum],
			 pCursor->bits->width,
			 pCursor->bits->height,
			 1);
  
  ximage = XCreateImage(xnestDisplay, 
			xnestDefaultVisual(pScreen),
			1, XYBitmap, 0, 
			(char *)pCursor->bits->source,
			pCursor->bits->width,
			pCursor->bits->height,
			BitmapPad(xnestDisplay), 0);
  
  XPutImage(xnestDisplay, source, xnestBitmapGC, ximage,
	    0, 0, 0, 0, pCursor->bits->width, pCursor->bits->height);
  
  XFree(ximage);
  
  ximage = XCreateImage(xnestDisplay, 
			xnestDefaultVisual(pScreen),
			1, XYBitmap, 0, 
			(char *)pCursor->bits->mask,
			pCursor->bits->width,
			pCursor->bits->height,
			BitmapPad(xnestDisplay), 0);
  
  XPutImage(xnestDisplay, mask, xnestBitmapGC, ximage,
	    0, 0, 0, 0, pCursor->bits->width, pCursor->bits->height);
  
  XFree(ximage);
  
  fg_color.red = pCursor->foreRed;
  fg_color.green = pCursor->foreGreen;
  fg_color.blue = pCursor->foreBlue;
  
  bg_color.red = pCursor->backRed;
  bg_color.green = pCursor->backGreen;
  bg_color.blue = pCursor->backBlue;

  pCursor->devPriv[pScreen->myNum] = (pointer)xalloc(sizeof(xnestPrivCursor));
  xnestCursorPriv(pCursor, pScreen)->cursor = 
    XCreatePixmapCursor(xnestDisplay, source, mask, &fg_color, &bg_color,
			pCursor->bits->xhot, pCursor->bits->yhot);
  
  XFreePixmap(xnestDisplay, source);
  XFreePixmap(xnestDisplay, mask);
  
  return True;
}

Bool xnestUnrealizeCursor(pScreen, pCursor)
     ScreenPtr pScreen;
     CursorPtr pCursor;
{
  XFreeCursor(xnestDisplay, xnestCursor(pCursor, pScreen));
  xfree(xnestCursorPriv(pCursor, pScreen));
  return True;
}

void xnestRecolorCursor(pScreen,  pCursor, displayed)
     ScreenPtr pScreen;
     CursorPtr pCursor;
     Bool displayed;
{
  XColor fg_color, bg_color;
  
  fg_color.red = pCursor->foreRed;
  fg_color.green = pCursor->foreGreen;
  fg_color.blue = pCursor->foreBlue;
  
  bg_color.red = pCursor->backRed;
  bg_color.green = pCursor->backGreen;
  bg_color.blue = pCursor->backBlue;
  
  XRecolorCursor(xnestDisplay, 
		 xnestCursor(pCursor, pScreen),
		 &fg_color, &bg_color);
}

Bool xnestSetCursorPosition(pScreen, x, y, generateEvent)
     ScreenPtr pScreen;
     int x, y;
     Bool generateEvent;
{
  int i;

  for (i = 0; i < xnestNumScreens; i++)
    XWarpPointer(xnestDisplay, xnestDefaultWindows[i],
		 xnestDefaultWindows[pScreen->myNum],
		 0, 0, 0, 0, x, y);
  
  return True;
}
