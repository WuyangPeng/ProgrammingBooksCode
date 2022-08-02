/* $XFree86: xc/programs/Xserver/afb/afbscrinit.c,v 3.0 1996/08/18 01:45:53 dawes Exp $ */
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
/* $XConsortium: afbscrinit.c,v 5.17 94/04/17 20:28:34 dpw Exp $ */

#include "X.h"
#include "Xproto.h"		/* for xColorItem */
#include "Xmd.h"
#include "scrnintstr.h"
#include "pixmapstr.h"
#include "resource.h"
#include "colormap.h"
#include "afb.h"
#include "mistruct.h"
#include "dix.h"
#include "mi.h"
#include "mibstore.h"
#include "migc.h"
#include "servermd.h"

#ifdef PIXMAP_PER_WINDOW
int frameWindowPrivateIndex;
#endif
int afbWindowPrivateIndex;
int afbGCPrivateIndex;
int afbScreenPrivateIndex;

static unsigned long afbGeneration = 0;

miBSFuncRec afbBSFuncRec = {
	afbSaveAreas,
	afbRestoreAreas,
	(void (*)()) 0,
	(PixmapPtr (*)()) 0,
	(PixmapPtr (*)()) 0,
};

Bool
afbCloseScreen(index, pScreen)
	int index;
	ScreenPtr pScreen;
{
	int d;
	DepthPtr depths = pScreen->allowedDepths;

	for (d = 0; d < pScreen->numDepths; d++)
		xfree(depths[d].vids);
	xfree(depths);
	xfree(pScreen->visuals);
	xfree(pScreen->devPrivates[afbScreenPrivateIndex].ptr);
	return(TRUE);
}

Bool
afbCreateScreenResources(pScreen)
	ScreenPtr pScreen;
{
	Bool retval;

	pointer oldDevPrivate = pScreen->devPrivate;

	pScreen->devPrivate = pScreen->devPrivates[afbScreenPrivateIndex].ptr;
	retval = miCreateScreenResources(pScreen);

	/* Modify screen's pixmap devKind value stored off devPrivate to
	 * be the width of a single plane in longs rather than the width
	 * of a chunky screen in longs as incorrectly setup by the mi routine.
	 */
	((PixmapPtr)pScreen->devPrivate)->devKind = BitmapBytePad(pScreen->width);
	pScreen->devPrivates[afbScreenPrivateIndex].ptr = pScreen->devPrivate;
	pScreen->devPrivate = oldDevPrivate;
	return(retval);
}

Bool
afbAllocatePrivates(pScreen, pWinIndex, pGCIndex)
	ScreenPtr pScreen;
	int *pWinIndex, *pGCIndex;
{
	if (afbGeneration != serverGeneration) {
#ifdef PIXMAP_PER_WINDOW
		frameWindowPrivateIndex = AllocateWindowPrivateIndex();
#endif
		afbWindowPrivateIndex = AllocateWindowPrivateIndex();
		afbGCPrivateIndex = AllocateGCPrivateIndex();
		miRegisterGCPrivateIndex(afbGCPrivateIndex);
		afbGeneration = serverGeneration;
	}
	if (pWinIndex)
		*pWinIndex = afbWindowPrivateIndex;
	if (pGCIndex)
		*pGCIndex = afbGCPrivateIndex;

	afbScreenPrivateIndex = AllocateScreenPrivateIndex();
	return(AllocateWindowPrivate(pScreen, afbWindowPrivateIndex,
										  sizeof(afbPrivWin)) &&
			 AllocateGCPrivate(pScreen, afbGCPrivateIndex, sizeof(afbPrivGC)));
}

/* dts * (inch/dot) * (25.4 mm / inch) = mm */
Bool
afbScreenInit(pScreen, pbits, xsize, ysize, dpix, dpiy, width)
	register ScreenPtr pScreen;
	pointer pbits;					/* pointer to screen bitmap */
	int xsize, ysize;				/* in pixels */
	int dpix, dpiy;				/* dots per inch */
	int width;						/* pixel width of frame buffer */
{
	VisualPtr visuals;
	DepthPtr depths;
	int nvisuals;
	int ndepths;
	int rootdepth;
	VisualID defaultVisual;
	pointer oldDevPrivate;

	rootdepth = 0;
	if (!afbInitVisuals(&visuals, &depths, &nvisuals, &ndepths, &rootdepth,
								&defaultVisual, 256, 8)) {
		ErrorF("afbInitVisuals: FALSE\n");
		return FALSE;
	}
	if (!afbAllocatePrivates(pScreen,(int *)NULL, (int *)NULL)) {
		ErrorF("afbAllocatePrivates: FALSE\n");
		return FALSE;
	}

	pScreen->defColormap = (Colormap)FakeClientID(0);
	/* whitePixel, blackPixel */
	pScreen->blackPixel = 0;
	pScreen->whitePixel = 0;
	pScreen->QueryBestSize = afbQueryBestSize;
	/* SaveScreen */
	pScreen->GetImage = afbGetImage;
	pScreen->GetSpans = afbGetSpans;
	pScreen->CreateWindow = afbCreateWindow;
	pScreen->DestroyWindow = afbDestroyWindow;
	pScreen->PositionWindow = afbPositionWindow;
	pScreen->ChangeWindowAttributes = afbChangeWindowAttributes;
	pScreen->RealizeWindow = afbMapWindow;
	pScreen->UnrealizeWindow = afbUnmapWindow;
	pScreen->PaintWindowBackground = afbPaintWindow;
	pScreen->PaintWindowBorder = afbPaintWindow;
	pScreen->CopyWindow = afbCopyWindow;
	pScreen->CreatePixmap = afbCreatePixmap;
	pScreen->DestroyPixmap = afbDestroyPixmap;
	pScreen->RealizeFont = afbRealizeFont;
	pScreen->UnrealizeFont = afbUnrealizeFont;
	pScreen->CreateGC = afbCreateGC;
	pScreen->CreateColormap = afbInitializeColormap;
	pScreen->DestroyColormap = (void (*)())NoopDDA;
	pScreen->InstallColormap = (void (*)())NoopDDA;
	pScreen->UninstallColormap = (void (*)())NoopDDA;
	pScreen->ListInstalledColormaps = (int (*)())NoopDDA;
	pScreen->StoreColors = (void (*)())NoopDDA;
	pScreen->ResolveColor = afbResolveColor;
	pScreen->BitmapToRegion = afbPixmapToRegion;
	oldDevPrivate = pScreen->devPrivate;
	if (!miScreenInit(pScreen, pbits, xsize, ysize, dpix, dpiy, width, rootdepth,
							ndepths, depths, defaultVisual, nvisuals, visuals, NULL)) {
		ErrorF("miScreenInit: FALSE\n");
		return FALSE;
	}

	pScreen->CloseScreen = afbCloseScreen;
	pScreen->CreateScreenResources = afbCreateScreenResources;
	miInitializeBackingStore(pScreen, &afbBSFuncRec);

	pScreen->devPrivates[afbScreenPrivateIndex].ptr = pScreen->devPrivate;
	pScreen->devPrivate = oldDevPrivate;

	return TRUE;
}
