/* $XConsortium: Init.c /main/7 1996/12/02 10:21:37 lehors $ */
/* $XFree86: xc/programs/Xserver/hw/xnest/Init.c,v 3.10 1997/01/12 10:48:33 dawes Exp $ */
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
#include "scrnintstr.h"
#include "windowstr.h"
#include "servermd.h"

#include "Xnest.h"

#include "Display.h"
#include "Screen.h"
#include "Pointer.h"
#include "Keyboard.h"
#include "Handlers.h"
#include "Init.h"
#include "Args.h"
#include "Drawable.h"
#include "XNGC.h"
#include "XNFont.h"

Bool xnestDoFullGeneration = True;

void InitOutput(screenInfo, argc, argv)
     ScreenInfo *screenInfo;
     int argc;
     char *argv[];
{
  int i, j;

  xnestOpenDisplay(argc, argv);
  
  screenInfo->imageByteOrder = ImageByteOrder(xnestDisplay);
  screenInfo->bitmapScanlineUnit = BitmapUnit(xnestDisplay);
  screenInfo->bitmapScanlinePad = BitmapPad(xnestDisplay);
  screenInfo->bitmapBitOrder = BitmapBitOrder(xnestDisplay);
  
  screenInfo->numPixmapFormats = 0;
  for (i = 0; i < xnestNumPixmapFormats; i++) 
    for (j = 0; j < xnestNumDepths; j++)
      if (xnestPixmapFormats[i].depth == xnestDepths[j]) {
	screenInfo->formats[screenInfo->numPixmapFormats].depth = 
	  xnestPixmapFormats[i].depth;
	screenInfo->formats[screenInfo->numPixmapFormats].bitsPerPixel = 
	  xnestPixmapFormats[i].bits_per_pixel;
	screenInfo->formats[screenInfo->numPixmapFormats].scanlinePad = 
	  xnestPixmapFormats[i].scanline_pad;
	screenInfo->numPixmapFormats++;
      }
  
  xnestWindowPrivateIndex = AllocateWindowPrivateIndex();
  xnestGCPrivateIndex = AllocateGCPrivateIndex();
  xnestFontPrivateIndex = AllocateFontPrivateIndex();
  
  if (!xnestNumScreens) xnestNumScreens = 1;

  for (i = 0; i < xnestNumScreens; i++)
    AddScreen(xnestOpenScreen, argc, argv);

  xnestNumScreens = screenInfo->numScreens;

  xnestDoFullGeneration = xnestFullGeneration;
}

void InitInput(argc, argv)
     int argc;
     char *argv[];
{
  DeviceIntPtr ptr, kbd;

  ptr = AddInputDevice(xnestPointerProc, TRUE);
  kbd = AddInputDevice(xnestKeyboardProc, TRUE);

  RegisterPointerDevice(ptr);
  RegisterKeyboardDevice(kbd);

  mieqInit(kbd, ptr);

  AddEnabledDevice(XConnectionNumber(xnestDisplay));

  RegisterBlockAndWakeupHandlers(xnestBlockHandler, xnestWakeupHandler, NULL);
}

/*
 * DDX - specific abort routine.  Called by AbortServer().
 */
void AbortDDX()
{
  xnestDoFullGeneration = True;
  xnestCloseDisplay();
}

/* Called by GiveUp(). */
void ddxGiveUp()
{
  AbortDDX();
}

void OsVendorInit()
{
    return;
}

void OsVendorFatalError()
{
    return;
}

#ifdef DPMSExtension
#if NeedFunctionPrototypes
void DPMSSet(CARD16 level)
#else
void DPMSSet(level)
     CARD16 level;
#endif
{
    return;
}

Bool DPMSSupported()
{
    return FALSE;
}
#endif

/* this is just to get the server to link on AIX */
#ifdef AIXV3
int SelectWaitTime = 10000; /* usec */
#endif
