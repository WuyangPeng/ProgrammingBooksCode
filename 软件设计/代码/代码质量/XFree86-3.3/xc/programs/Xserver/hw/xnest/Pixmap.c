/* $XConsortium: Pixmap.c,v 1.3 95/07/10 17:42:22 ray Exp $ */
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
#include "miscstruct.h"
#include "pixmapstr.h"
#include "scrnintstr.h"
#include "regionstr.h"
#include "gc.h"
#include "servermd.h"
#include "mi.h"

#include "Xnest.h"

#include "Display.h"
#include "Screen.h"
#include "Pixmap.h"

PixmapPtr xnestCreatePixmap(pScreen, width, height, depth)
    ScreenPtr   pScreen;
    int         width;
    int         height;
    int         depth;
{
  PixmapPtr pPixmap;

  pPixmap = (PixmapPtr)xalloc(sizeof(PixmapRec) + sizeof(xnestPrivPixmap));
  if (!pPixmap)
    return NullPixmap;
  pPixmap->drawable.type = DRAWABLE_PIXMAP;
  pPixmap->drawable.class = 0;
  pPixmap->drawable.depth = depth;
  pPixmap->drawable.bitsPerPixel = depth;
  pPixmap->drawable.id = 0;
  pPixmap->drawable.x = 0;
  pPixmap->drawable.y = 0;
  pPixmap->drawable.width = width;
  pPixmap->drawable.height = height;
  pPixmap->drawable.pScreen = pScreen;
  pPixmap->drawable.serialNumber = NEXT_SERIAL_NUMBER;
  pPixmap->refcnt = 1;
  pPixmap->devKind = PixmapBytePad(width, depth);
  pPixmap->devPrivate.ptr = (pointer)(pPixmap + 1);
  if (width && height)
      xnestPixmapPriv(pPixmap)->pixmap = 
	  XCreatePixmap(xnestDisplay, 
			xnestDefaultWindows[pScreen->myNum],
			width, height, depth);
  else
      xnestPixmapPriv(pPixmap)->pixmap = 0;
  
  return pPixmap;
}

Bool xnestDestroyPixmap(pPixmap)
     PixmapPtr pPixmap;
{
  if(--pPixmap->refcnt)
    return TRUE;
  XFreePixmap(xnestDisplay, xnestPixmap(pPixmap));
  xfree(pPixmap);
  return TRUE;
}

RegionPtr xnestPixmapToRegion(pPixmap)
     PixmapPtr pPixmap;
{
  XImage *ximage;
  register RegionPtr pReg, pTmpReg;
  register int x, y;
  unsigned long previousPixel, currentPixel;
  BoxRec Box;
  int nWidth;
  Bool overlap;
  
  ximage = XGetImage(xnestDisplay, xnestPixmap(pPixmap), 0, 0,
		     pPixmap->drawable.width, pPixmap->drawable.height,
		     1, XYPixmap);
  
  pReg = REGION_CREATE(pPixmap->drawable.pScreen, NULL, 1);
  pTmpReg = REGION_CREATE(pPixmap->drawable.pScreen, NULL, 1);
  if(!pReg || !pTmpReg) return NullRegion;
  
  for (y = 0; y < pPixmap->drawable.height; y++) {
    Box.y1 = y;
    Box.y2 = y + 1;
    previousPixel = 0L;
    for (x = 0; x < pPixmap->drawable.width; x++) {
      currentPixel = XGetPixel(ximage, x, y);
      if (previousPixel != currentPixel) {
	if (previousPixel == 0L) { 
	  /* left edge */
	  Box.x1 = x;
	}
	else if (currentPixel == 0L) {
	  /* right edge */
	  Box.x2 = x;
	  REGION_RESET(pPixmap->drawable.pScreen, pTmpReg, &Box);
	  REGION_APPEND(pPixmap->drawable.pScreen, pReg, pTmpReg);
	}
	previousPixel = currentPixel;
      }
    }
    if (previousPixel != 0L) {
      /* right edge because of the end of pixmap */
      Box.x2 = pPixmap->drawable.width;
      REGION_RESET(pPixmap->drawable.pScreen, pTmpReg, &Box);
      REGION_APPEND(pPixmap->drawable.pScreen, pReg, pTmpReg);
    }
  }
  
  REGION_DESTROY(pPixmap->drawable.pScreen, pTmpReg);
  XDestroyImage(ximage);

  REGION_VALIDATE(pPixmap->drawable.pScreen, pReg, &overlap);

  return(pReg);
}
