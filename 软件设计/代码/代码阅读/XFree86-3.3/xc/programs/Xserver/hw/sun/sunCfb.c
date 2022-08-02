
/* $XConsortium: sunCfb.c /main/20 1996/10/31 14:24:08 kaleb $ */
/* $XFree86: xc/programs/Xserver/hw/sun/sunCfb.c,v 3.5 1996/12/23 06:30:14 dawes Exp $ */

/*
Copyright (c) 1990  X Consortium

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

/************************************************************
Copyright 1987 by Sun Microsystems, Inc. Mountain View, CA.

                    All Rights Reserved

Permission  to  use,  copy,  modify,  and  distribute   this
software  and  its documentation for any purpose and without
fee is hereby granted, provided that the above copyright no-
tice  appear  in all copies and that both that copyright no-
tice and this permission notice appear in  supporting  docu-
mentation,  and  that the names of Sun or X Consortium
not be used in advertising or publicity pertaining to 
distribution  of  the software  without specific prior 
written permission. Sun and X Consortium make no 
representations about the suitability of this software for 
any purpose. It is provided "as is" without any express or 
implied warranty.

SUN DISCLAIMS ALL WARRANTIES WITH REGARD TO  THIS  SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FIT-
NESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL SUN BE  LI-
ABLE  FOR  ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,  DATA  OR
PROFITS,  WHETHER  IN  AN  ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
THE USE OR PERFORMANCE OF THIS SOFTWARE.

********************************************************/

/*
 * Copyright (c) 1987 by the Regents of the University of California
 * Copyright (c) 1987 by Adam de Boor, UC Berkeley
 *
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any purpose and without
 * fee is hereby granted, provided that the above copyright
 * notice appear in all copies.  The University of California
 * makes no representations about the suitability of this
 * software for any purpose.  It is provided "as is" without
 * express or implied warranty.
 */

/****************************************************************/
/* Modified from  sunCG4C.c for X11R3 by Tom Jarmolowski	*/
/****************************************************************/

/* 
 * Copyright 1991, 1992, 1993 Kaleb S. Keithley
 *
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any purpose and without
 * fee is hereby granted, provided that the above copyright
 * notice appear in all copies.  Kaleb S. Keithley makes no 
 * representations about the suitability of this software for 
 * any purpose.  It is provided "as is" without express or 
 * implied warranty.
 */

#include "sun.h"
#include "cfb/cfb.h"
#include "mi/miline.h"

#define GXZEROLINEBIAS	(OCTANT1 | OCTANT3 | OCTANT4 | OCTANT6)

static void CGUpdateColormap(pScreen, dex, count, rmap, gmap, bmap)
    ScreenPtr	pScreen;
    int		dex, count;
    u_char	*rmap, *gmap, *bmap;
{
    struct fbcmap sunCmap;

    sunCmap.index = dex;
    sunCmap.count = count;
    sunCmap.red = &rmap[dex];
    sunCmap.green = &gmap[dex];
    sunCmap.blue = &bmap[dex];

    if (ioctl(sunFbs[pScreen->myNum].fd, FBIOPUTCMAP, &sunCmap) < 0) {
	Error("CGUpdateColormap");
	FatalError( "CGUpdateColormap: FBIOPUTCMAP failed\n" );
    }
}

void sunInstallColormap(cmap)
    ColormapPtr	cmap;
{
    SetupScreen(cmap->pScreen);
    register int i;
    register Entry *pent;
    register VisualPtr pVisual = cmap->pVisual;
    u_char	  rmap[256], gmap[256], bmap[256];
    unsigned long rMask, gMask, bMask;
    int	oRed, oGreen, oBlue;

    if (cmap == pPrivate->installedMap)
	return;
    if (pPrivate->installedMap)
	WalkTree(pPrivate->installedMap->pScreen, TellLostMap,
		 (pointer) &(pPrivate->installedMap->mid));
    if ((pVisual->class | DynamicClass) == DirectColor) {
	if (pVisual->ColormapEntries < 256) {
	    rMask = pVisual->redMask;
	    gMask = pVisual->greenMask;
	    bMask = pVisual->blueMask;
	    oRed = pVisual->offsetRed;
	    oGreen = pVisual->offsetGreen;
	    oBlue = pVisual->offsetBlue;
	} else {
	    rMask = gMask = bMask = 255;
	    oRed = oGreen = oBlue = 0;
	}
	for (i = 0; i < 256; i++) {
	    rmap[i] = cmap->red[(i & rMask) >> oRed].co.local.red >> 8;
	    gmap[i] = cmap->green[(i & gMask) >> oGreen].co.local.green >> 8;
	    bmap[i] = cmap->blue[(i & bMask) >> oBlue].co.local.blue >> 8;
	}
    } else {
	for (i = 0, pent = cmap->red;
	     i < pVisual->ColormapEntries;
	     i++, pent++) {
	    if (pent->fShared) {
		rmap[i] = pent->co.shco.red->color >> 8;
		gmap[i] = pent->co.shco.green->color >> 8;
		bmap[i] = pent->co.shco.blue->color >> 8;
	    }
	    else {
		rmap[i] = pent->co.local.red >> 8;
		gmap[i] = pent->co.local.green >> 8;
		bmap[i] = pent->co.local.blue >> 8;
	    }
	}
    }
    pPrivate->installedMap = cmap;
    (*pPrivate->UpdateColormap) (cmap->pScreen, 0, 256, rmap, gmap, bmap);
    WalkTree(cmap->pScreen, TellGainedMap, (pointer) &(cmap->mid));
}

void sunUninstallColormap(cmap)
    ColormapPtr	cmap;
{
    SetupScreen(cmap->pScreen);
    if (cmap == pPrivate->installedMap) {
	Colormap defMapID = cmap->pScreen->defColormap;

	if (cmap->mid != defMapID) {
	    ColormapPtr defMap = (ColormapPtr) LookupIDByType(defMapID,
							      RT_COLORMAP);

	    if (defMap)
		(*cmap->pScreen->InstallColormap)(defMap);
	    else
	        ErrorF("sunFbs: Can't find default colormap\n");
	}
    }
}

int sunListInstalledColormaps(pScreen, pCmapList)
    ScreenPtr	pScreen;
    Colormap	*pCmapList;
{
    SetupScreen(pScreen);
    *pCmapList = pPrivate->installedMap->mid;
    return (1);
}

static void CGStoreColors(pmap, ndef, pdefs)
    ColormapPtr	pmap;
    int		ndef;
    xColorItem	*pdefs;
{
    SetupScreen(pmap->pScreen);
    u_char	rmap[256], gmap[256], bmap[256];
    xColorItem	expanddefs[256];
    register int i;

    if (pPrivate->installedMap != NULL && pPrivate->installedMap != pmap)
	return;
    if ((pmap->pVisual->class | DynamicClass) == DirectColor) {
	ndef = cfbExpandDirectColors(pmap, ndef, pdefs, expanddefs);
	pdefs = expanddefs;
    }
    while (ndef--) {
	i = pdefs->pixel;
	rmap[i] = pdefs->red >> 8;
	gmap[i] = pdefs->green >> 8;
	bmap[i] = pdefs->blue >> 8;
	(*pPrivate->UpdateColormap) (pmap->pScreen, i, 1, rmap, gmap, bmap);
	pdefs++;
    }
}

static void CGScreenInit (pScreen)
    ScreenPtr	pScreen;
{
#ifndef STATIC_COLOR /* { */
    SetupScreen (pScreen);
    pScreen->InstallColormap = sunInstallColormap;
    pScreen->UninstallColormap = sunUninstallColormap;
    pScreen->ListInstalledColormaps = sunListInstalledColormaps;
    pScreen->StoreColors = CGStoreColors;
    pPrivate->UpdateColormap = CGUpdateColormap;
    if (sunFlipPixels) {
	Pixel pixel = pScreen->whitePixel;
	pScreen->whitePixel = pScreen->blackPixel;
	pScreen->blackPixel = pixel;
    }
#endif /* } */
}

static void checkMono (argc, argv)
    int argc;
    char** argv;
{
    int i;

    for (i = 1; i < argc; i++)
	if (strcmp (argv[i], "-mono") == 0)
	    ErrorF ("-mono not appropriate for CG3/CG4/CG6\n");
}

/*
 * CG3_MMAP_OFFSET is #defined in <pixrect/cg3var.h> or <sys/cg3var.h>
 * on  SunOS and Solaris respectively.  Under Solaris, cg3var.h 
 * #includes a non-existent file, and causes the make to abort.  Other
 * systems may not have cg3var.h at all.  Since all cg3var.h is needed
 * for is this one #define, we'll just #define it here and let it go at that.
 */

#define CG3_MMAP_OFFSET 0x04000000

Bool sunCG3Init (screen, pScreen, argc, argv)
    int	    	  screen;    	/* what screen am I going to be */
    ScreenPtr	  pScreen;  	/* The Screen to initialize */
    int	    	  argc;	    	/* The number of the Server's arguments. */
    char    	  **argv;   	/* The arguments themselves. Don't change! */
{
    checkMono (argc, argv);
    sunFbs[screen].EnterLeave = (void (*)())NoopDDA;
    return sunInitCommon (screen, pScreen, (off_t) CG3_MMAP_OFFSET,
	sunCfbScreenInit, CGScreenInit,
	cfbCreateDefColormap, sunSaveScreen, 0);
}

Bool sunTCXInit (screen, pScreen, argc, argv)
    int	    	  screen;    	/* what screen am I going to be */
    ScreenPtr	  pScreen;  	/* The Screen to initialize */
    int	    	  argc;	    	/* The number of the Server's arguments. */
    char    	  **argv;   	/* The arguments themselves. Don't change! */
{
    checkMono (argc, argv);
    sunFbs[screen].EnterLeave = (void (*)())NoopDDA;
    return sunInitCommon (screen, pScreen, (off_t) 0,
	sunCfbScreenInit, CGScreenInit,
	cfbCreateDefColormap, sunSaveScreen, 0);
}

#if !defined(i386) && !defined(__bsdi__) /* { */

#ifdef SVR4
#include <sys/cg2reg.h>
#else
#ifndef CSRG_BASED
#include <pixrect/cg2reg.h>
#else
#include <machine/cgtworeg.h>
#endif
#endif

typedef struct {
    struct cg2memfb	mem;
    struct cg2fb 	regs;
} *CG2Ptr;

static void CG2UpdateColormap(pScreen, index, count, rmap, gmap,bmap)
    ScreenPtr	pScreen;
    int		  index, count;
    u_char	  *rmap, *gmap, *bmap;
{
    CG2Ptr	fb = (CG2Ptr) sunFbs[pScreen->myNum].fb;
#if __STDC__
    volatile
#endif
    struct cg2statusreg *regp = &fb->regs.status.reg;

    regp->update_cmap = 0;
    while (count--) {
	fb->regs.redmap[index] = rmap[index];
	fb->regs.greenmap[index] = gmap[index];
	fb->regs.bluemap[index] = bmap[index];
	index++;
    }
    regp->update_cmap = 1;
}

static Bool CG2SaveScreen (pScreen, on)
    ScreenPtr	  pScreen;
    int    	  on;
{
    CG2Ptr	fb = (CG2Ptr) sunFbs[pScreen->myNum].fb;
#if __STDC__
    volatile
#endif
    struct cg2statusreg *regp = &fb->regs.status.reg;

    if (on != SCREEN_SAVER_FORCER)
	regp->video_enab = (on == SCREEN_SAVER_ON) ? 0 : 1;
}

static void CG2ScreenInit (pScreen)
    ScreenPtr	pScreen;
{
    SetupScreen (pScreen);
    CGScreenInit (pScreen);
    pPrivate->UpdateColormap = CG2UpdateColormap;
}

Bool sunCG2Init (screen, pScreen, argc, argv)
    int		screen;    	/* what screen am I going to be */
    ScreenPtr	pScreen;  	/* The Screen to initialize */
    int		argc;	    	/* The number of the Server's arguments. */
    char**	argv;   	/* The arguments themselves. Don't change! */
{
    sunScreenPtr    pPrivate;
    int		i;
    Bool	ret;
    Bool	mono = FALSE;

    for (i = 1; i < argc; i++)
	if (strcmp (argv[i], "-mono") == 0)
	    mono = TRUE;

    sunFbs[screen].EnterLeave = (void (*)())NoopDDA;
    pScreen->SaveScreen = CG2SaveScreen;
    if (mono) {
	pScreen->whitePixel = 0;
	pScreen->blackPixel = 1;
	ret = sunInitCommon (screen, pScreen, (off_t) 0,
			mfbScreenInit, NULL,
			mfbCreateDefColormap, CG2SaveScreen, 0);
	((CG2Ptr) sunFbs[screen].fb)->regs.ppmask.reg = 1;
    } else {
	ret = sunInitCommon (screen, pScreen, (off_t) 0,
			sunCfbScreenInit, CG2ScreenInit,
			cfbCreateDefColormap, CG2SaveScreen,
			(int) &((struct cg2memfb *) 0)->pixplane);
	((CG2Ptr) sunFbs[screen].fb)->regs.ppmask.reg = 0xFF;
    }
    return ret;
}

#define	CG4_HEIGHT	900
#define	CG4_WIDTH	1152

#define	CG4_MELEN	    (128*1024)

typedef struct {
    u_char mpixel[CG4_MELEN];		/* bit-per-pixel memory */
    u_char epixel[CG4_MELEN];		/* enable plane */
    u_char cpixel[CG4_HEIGHT][CG4_WIDTH];	/* byte-per-pixel memory */
} *CG4Ptr;

static void CG4Switch (pScreen, select)
    ScreenPtr	pScreen;
    int		select;
{
    CG4Ptr	fb = (CG4Ptr) sunFbs[pScreen->myNum].fb;

    (void) memset ((char *)fb->epixel, select ? ~0 : 0, CG4_MELEN);
}

Bool sunCG4Init (screen, pScreen, argc, argv)
    int		screen;    	/* what screen am I going to be */
    ScreenPtr	pScreen;  	/* The Screen to initialize */
    int		argc;	    	/* The number of the Server's arguments. */
    char**	argv;   	/* The arguments themselves. Don't change! */
{
    checkMono (argc, argv);
    if (sunCG4Frob)
	sunFbs[screen].EnterLeave = (void (*)())NoopDDA;
    else
	sunFbs[screen].EnterLeave = CG4Switch;
    return sunInitCommon (screen, pScreen, (off_t) 0,
	sunCfbScreenInit, CGScreenInit,
	cfbCreateDefColormap, sunSaveScreen, (int) ((CG4Ptr) 0)->cpixel);
}

#ifdef FBTYPE_SUNFAST_COLOR /* { */

#define CG6_MMAP_OFFSET 0x70000000
#define CG6_IMAGE_OFFSET 0x16000

Bool sunCG6Init (screen, pScreen, argc, argv)
    int		screen;    	/* The index of pScreen in the ScreenInfo */
    ScreenPtr	pScreen;  	/* The Screen to initialize */
    int		argc;	    	/* The number of the Server's arguments. */
    char**	argv;   	/* The arguments themselves. Don't change! */
{
    pointer	fb;

    checkMono (argc, argv);
    if (!sunScreenAllocate (pScreen))
	return FALSE;
    if (!sunFbs[screen].fb) {
/* Sun's VME, Sbus, and SVR4 drivers all return different values */
#define FBSIZE (size_t) sunFbs[screen].info.fb_width * \
			sunFbs[screen].info.fb_height + CG6_IMAGE_OFFSET
	if ((fb = sunMemoryMap (FBSIZE,
			     (off_t) CG6_MMAP_OFFSET, 
			     sunFbs[screen].fd)) == NULL)
	    return FALSE;
	sunFbs[screen].fb = fb;
#undef FBSIZE
    }
    sunFbs[screen].EnterLeave = (void (*)())NoopDDA;
    if (!sunCfbSetupScreen (pScreen, 
	    sunFbs[screen].fb + CG6_IMAGE_OFFSET,
	    sunFbs[screen].info.fb_width, 
	    sunFbs[screen].info.fb_height,
	    monitorResolution, monitorResolution, 
	    sunFbs[screen].info.fb_width,
	    sunFbs[screen].info.fb_depth))
	return FALSE;
    if (sunNoGX == FALSE) {
	if (!sunGXInit (pScreen, &sunFbs[screen]))
	    return FALSE;
    }
    if (!sunCfbFinishScreenInit(pScreen,
	    sunFbs[screen].fb + CG6_IMAGE_OFFSET,
	    sunFbs[screen].info.fb_width, 
	    sunFbs[screen].info.fb_height,
	    monitorResolution, monitorResolution, 
	    sunFbs[screen].info.fb_width,
	    sunFbs[screen].info.fb_depth))
	return FALSE;
    if (sunNoGX == FALSE) {
	miSetZeroLineBias(pScreen, GXZEROLINEBIAS);
    }
    CGScreenInit (pScreen);
    if (!sunScreenInit (pScreen))
	return FALSE;
    sunSaveScreen (pScreen, SCREEN_SAVER_OFF);
    return cfbCreateDefColormap(pScreen);
}
#endif /* } */
#endif /* } */
