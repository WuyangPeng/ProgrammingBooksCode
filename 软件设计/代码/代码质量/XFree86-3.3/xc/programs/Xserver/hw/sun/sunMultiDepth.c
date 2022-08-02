/* $XConsortium: sunMultiDepth.c,v 1.2 94/04/17 20:29:48 dpw Exp $ */
/*

Copyright (c) 1992  X Consortium

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

#include "X.h"
#include "Xmd.h"
#include "servermd.h"
#include "scrnintstr.h"
#include "pixmapstr.h"
#include "resource.h"
#include "colormap.h"
#include "colormapst.h"
#include "mi.h"
#include "mistruct.h"
#include "dix.h"
#include "gcstruct.h"
#include "mibstore.h"

#ifndef SINGLEDEPTH

static Bool
sunCfbCreateGC(pGC)
    GCPtr   pGC;
{
    if (pGC->depth == 1)
    {
	return mfbCreateGC (pGC);
    }
    else if (pGC->depth <= 8)
    {
	return cfbCreateGC (pGC);
    }
    else if (pGC->depth <= 16)
    {
	return cfb16CreateGC (pGC);
    }
    else if (pGC->depth <= 32)
    {
	return cfb32CreateGC (pGC);
    }
    return FALSE;
}

static void
sunCfbGetSpans(pDrawable, wMax, ppt, pwidth, nspans, pdstStart)
    DrawablePtr		pDrawable;	/* drawable from which to get bits */
    int			wMax;		/* largest value of all *pwidths */
    register DDXPointPtr ppt;		/* points to start copying from */
    int			*pwidth;	/* list of number of bits to copy */
    int			nspans;		/* number of scanlines to copy */
    char		*pdstStart;	/* where to put the bits */
{
    switch (pDrawable->bitsPerPixel) {
    case 1:
	mfbGetSpans(pDrawable, wMax, ppt, pwidth, nspans, pdstStart);
	break;
    case 8:
	cfbGetSpans(pDrawable, wMax, ppt, pwidth, nspans, pdstStart);
	break;
    case 16:
	cfb16GetSpans(pDrawable, wMax, ppt, pwidth, nspans, pdstStart);
	break;
    case 32:
	cfb32GetSpans(pDrawable, wMax, ppt, pwidth, nspans, pdstStart);
	break;
    }
    return;
}

static void
sunCfbGetImage(pDrawable, sx, sy, w, h, format, planeMask, pdstLine)
    DrawablePtr pDrawable;
    int		sx, sy, w, h;
    unsigned int format;
    unsigned long planeMask;
    char	*pdstLine;
{
    switch (pDrawable->bitsPerPixel)
    {
    case 1:
	mfbGetImage(pDrawable, sx, sy, w, h, format, planeMask, pdstLine);
	break;
    case 8:
	cfbGetImage(pDrawable, sx, sy, w, h, format, planeMask, pdstLine);
	break;
    case 16:
	cfb16GetImage(pDrawable, sx, sy, w, h, format, planeMask, pdstLine);
	break;
    case 32:
	cfb32GetImage(pDrawable, sx, sy, w, h, format, planeMask, pdstLine);
	break;
    }
}

Bool
sunCfbSetupScreen(pScreen, pbits, xsize, ysize, dpix, dpiy, width, bpp)
    register ScreenPtr pScreen;
    pointer pbits;		/* pointer to screen bitmap */
    int xsize, ysize;		/* in pixels */
    int dpix, dpiy;		/* dots per inch */
    int width;			/* pixel width of frame buffer */
    int	bpp;			/* bits per pixel of root */
{
    extern int		cfbWindowPrivateIndex;
    extern int		cfbGCPrivateIndex;
    int ret;

    sunRegisterPixmapFormat( /* depth */ 1,  /* bits per pixel */ 1);
    sunRegisterPixmapFormat( /* depth */ 8,  /* bits per pixel */ 8);
    sunRegisterPixmapFormat( /* depth */ 12,  /* bits per pixel */ 16);
    sunRegisterPixmapFormat( /* depth */ 24,  /* bits per pixel */ 32);

    switch (bpp) {
    case 8:
	ret = cfbSetupScreen(pScreen, pbits, xsize, ysize, dpix, dpiy, width);
	break;
    case 16:
	ret = cfb16SetupScreen(pScreen, pbits, xsize, ysize, dpix, dpiy, width);
	break;
    case 32:
	ret = cfb32SetupScreen(pScreen, pbits, xsize, ysize, dpix, dpiy, width);
	break;
    default:
	return FALSE;
    }
    pScreen->CreateGC = sunCfbCreateGC;
    pScreen->GetImage = sunCfbGetImage;
    pScreen->GetSpans = sunCfbGetSpans;
    return ret;
}

extern miBSFuncRec	cfbBSFuncRec, cfb16BSFuncRec, cfb32BSFuncRec;
extern int  cfb16ScreenPrivateIndex, cfb32ScreenPrivateIndex;
extern Bool cfbCloseScreen(), cfb16CloseScreen(), cfb32CloseScreen();

Bool
sunCfbFinishScreenInit(pScreen, pbits, xsize, ysize, dpix, dpiy, width, bpp)
    register ScreenPtr pScreen;
    pointer pbits;		/* pointer to screen bitmap */
    int xsize, ysize;		/* in pixels */
    int dpix, dpiy;		/* dots per inch */
    int width;			/* pixel width of frame buffer */
    int bpp;
{
    int		i;
    pointer	oldDevPrivate;
    VisualPtr	visuals;
    int		nvisuals;
    DepthPtr	depths;
    int		ndepths;
    VisualID	defaultVisual;
    int		rootdepth;
    miBSFuncPtr	bsFuncs;

    if (!cfbInitVisuals(&visuals, &depths, &nvisuals, &ndepths,
			&rootdepth, &defaultVisual, 1 << (bpp - 1), 8))
	return FALSE;
    oldDevPrivate = pScreen->devPrivate;
    if (! miScreenInit(pScreen, pbits, xsize, ysize, dpix, dpiy, width,
			rootdepth, ndepths, depths,
			defaultVisual, nvisuals, visuals,
			(miBSFuncPtr) 0))
	return FALSE;
    switch (bpp)
    {
    case 8:
	pScreen->CloseScreen = cfbCloseScreen;
	bsFuncs = &cfbBSFuncRec;
	break;
    case 16:
	pScreen->CloseScreen = cfb16CloseScreen;
	pScreen->devPrivates[cfb16ScreenPrivateIndex].ptr =
	    pScreen->devPrivate;
	pScreen->devPrivate = oldDevPrivate;
	bsFuncs = &cfb16BSFuncRec;
	break;
    case 32:
	pScreen->CloseScreen = cfb32CloseScreen;
	pScreen->devPrivates[cfb32ScreenPrivateIndex].ptr =
	    pScreen->devPrivate;
	pScreen->devPrivate = oldDevPrivate;
	bsFuncs = &cfb32BSFuncRec;
	break;
    }
    miInitializeBackingStore (pScreen, bsFuncs);
    return TRUE;
}


Bool
sunCfbScreenInit(pScreen, pbits, xsize, ysize, dpix, dpiy, width, bpp)
    register ScreenPtr pScreen;
    pointer pbits;		/* pointer to screen bitmap */
    int xsize, ysize;		/* in pixels */
    int dpix, dpiy;		/* dots per inch */
    int width;			/* pixel width of frame buffer */
    int bpp;
{
    if (!sunCfbSetupScreen(pScreen, pbits, xsize, ysize, dpix, dpiy,
			   width, bpp))
	return FALSE;
    return sunCfbFinishScreenInit(pScreen, pbits, xsize, ysize, dpix,
				  dpiy, width, bpp);
}


#else /* SINGLEDEPTH */

/* stuff for 8-bit only server */

Bool
sunCfbSetupScreen(pScreen, pbits, xsize, ysize, dpix, dpiy, width, bpp)
    register ScreenPtr pScreen;
    pointer pbits;		/* pointer to screen bitmap */
    int xsize, ysize;		/* in pixels */
    int dpix, dpiy;		/* dots per inch */
    int width;			/* pixel width of frame buffer */
    int	bpp;			/* bits per pixel of root */
{
    sunRegisterPixmapFormat( /* depth */ 1, /* bits per pixel */ 1);
    sunRegisterPixmapFormat( /* depth */ 8,  /* bits per pixel */ 8);
    return cfbSetupScreen(pScreen, pbits, xsize, ysize, dpix, dpiy,
			  width);
}

Bool
sunCfbFinishScreenInit(pScreen, pbits, xsize, ysize, dpix, dpiy, width, bpp)
    register ScreenPtr pScreen;
    pointer pbits;		/* pointer to screen bitmap */
    int xsize, ysize;		/* in pixels */
    int dpix, dpiy;		/* dots per inch */
    int width;			/* pixel width of frame buffer */
    int bpp;
{
    return cfbFinishScreenInit(pScreen, pbits, xsize, ysize, dpix, dpiy,
			       width);
}

Bool
sunCfbScreenInit(pScreen, pbits, xsize, ysize, dpix, dpiy, width, bpp)
    register ScreenPtr pScreen;
    pointer pbits;		/* pointer to screen bitmap */
    int xsize, ysize;		/* in pixels */
    int dpix, dpiy;		/* dots per inch */
    int width;			/* pixel width of frame buffer */
    int bpp;
{
    sunRegisterPixmapFormat( /* depth */ 1, /* bits per pixel */ 1);
    sunRegisterPixmapFormat( /* depth */ 8,  /* bits per pixel */ 8);
    return cfbScreenInit(pScreen, pbits, xsize, ysize, dpix, dpiy, width);
}

#endif /* SINGLEDEPTH */
