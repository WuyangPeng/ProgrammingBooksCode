/* $XFree86: xc/programs/Xserver/hw/xfree86/vga256/drivers/sis/sis_FillSt.c,v 1.2.2.1 1997/05/21 15:02:52 dawes Exp $ */

/*
 *
 * Copyright 1993 by H. Hanemaayer, Utrecht, The Netherlands
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of H. Hanemaayer not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  H. Hanemaayer makes no representations
 * about the suitability of this software for any purpose.  It is provided
 * "as is" without express or implied warranty.
 *
 * H. HANEMAAYER DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL H. HANEMAAYER BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * Author:  H. Hanemaayer, <hhanemaa@cs.ruu.nl>
 *
 * Modified for use with Chips, David Bateman <dbateman@ee.uts.edu.au>
 * Modified for Sis by Xavier Ducoin (xavier@rd.lectra.fr)
 *
 */

/*
 * These are the functions for tiles, which call low-level functions.
 */

#include "vga256.h"
#include "cfbrrop.h"
#include "mergerop.h"
#include "vgaBank.h"
#include "xf86.h"
#include "vga.h"		       /* For vga256InfoRec */

#include "compiler.h"
#include "sis_driver.h"

extern void cfb16FillRectTile32Copy();
extern void cfb16FillRectTile32General();
extern void cfb24FillRectTile32Copy();
extern void cfb24FillRectTile32General();

/*
 * This function uses the color expand fill for opaque stipples.
 * I'm not entirely sure about the origin of the stipple; I assume
 * it should be (0, 0).
 */
void siscfbFillRectOpaqueStippled32(pDrawable, pGC, nBox, pBox)
	DrawablePtr pDrawable;
	GCPtr pGC;
	int nBox;		/* number of boxes to fill */
	register BoxPtr pBox;	/* pointer to list of boxes to fill */
{
	unsigned long *src;
	int stippleHeight;
	cfbPrivGCPtr devPriv;
	PixmapPtr stipple;
	int destPitch;

	devPriv = ((cfbPrivGCPtr) pGC->devPrivates[cfbGCPrivateIndex].ptr);
	stipple = devPriv->pRotatedPixmap;

	destPitch = (int)
		(((PixmapPtr)(pDrawable->pScreen->devPrivate))->devKind);

	cfb8CheckOpaqueStipple(pGC->alu, pGC->fgPixel, pGC->bgPixel,
		pGC->planemask);

	stippleHeight = stipple->drawable.height;
	src = (unsigned long *)stipple->devPrivate.ptr;

	for (;nBox; nBox--, pBox++) {
		int w = pBox->x2 - pBox->x1;
		int h = pBox->y2 - pBox->y1;
		if (cfb8StippleRRop == GXcopy && w >= 10 && h >= 10 &&
		    (32*stippleHeight <= sisBLTPatternOffscreenSize) ) {
			sisMMIOColorExpandStippleFill(pBox->x1, pBox->y1,
				w, h, src, stippleHeight, 0, 0,
				pGC->bgPixel, pGC->fgPixel, destPitch, 0);
		} else {
			/* Special raster op. */
			/* Let cfb do this one. */
			speedupvga2568FillRectOpaqueStippled32(
				pDrawable, pGC, 1, pBox);
		}
	}
}

/*
 * This function uses the color expand fill for transparent stipples.
 */

void siscfbFillRectTransparentStippled32(pDrawable, pGC, nBox, pBox)
	DrawablePtr pDrawable;
	GCPtr pGC;
	int nBox;		/* number of boxes to fill */
	register BoxPtr pBox;	/* pointer to list of boxes to fill */
{
	unsigned long *src;
	int stippleHeight;
	cfbPrivGCPtr devPriv;
	PixmapPtr stipple;
	int destPitch;

	devPriv = ((cfbPrivGCPtr) pGC->devPrivates[cfbGCPrivateIndex].ptr);
	stipple = devPriv->pRotatedPixmap;

	destPitch = (int)
		(((PixmapPtr)(pDrawable->pScreen->devPrivate))->devKind);

	cfb8CheckStipple(pGC->alu, pGC->fgPixel, pGC->planemask);

	stippleHeight = stipple->drawable.height;
	src = (unsigned long *)stipple->devPrivate.ptr;

	for (;nBox; nBox--, pBox++) {
		int w = pBox->x2 - pBox->x1;
		int h = pBox->y2 - pBox->y1;
		if (cfb8StippleRRop == GXcopy && w >= 10 && h >= 10 && 
		    (32*stippleHeight <= sisBLTPatternOffscreenSize) ) {
		         sisMMIOColorExpandStippleFill(pBox->x1, pBox->y1,
				w, h, src, stippleHeight, 0, 0, 0,
				pGC->fgPixel, destPitch, 1);
		} else {
			/* Special raster op. */
			/* Let cfb do this one. */
			speedupvga2568FillRectTransparentStippled32(
				pDrawable, pGC, 1, pBox);
		}
	}
}

/*
 * SIS Tile fill.
 * There's no clear way to do tiling efficiently. There are lots of
 * different ways.
 * Uses a specific latched-write function for multiple-of-8 pixels wide tiles.
 * For 8x8 and 16x16 tiles, the BitBLT engine fill is used. For larger
 * tiles, we use repeated BitBlt.
 *
 * see the cirrus_FillSt.c and ct_FillSt.c
 * On the sis 6205 handle only 8x8 tile in 8 bpp .
 *
 * Currently the accel routine is very restrictive.
 * I think for the sis, the cfb routine (which does a very good
 * job) may be more efficient than a 32xH latched write fill (h != 32)
 * because of the 32-bit host interface.
 *
 *
 *
 */

void
siscfbFillRectTile(pDrawable, pGC, nBox, pBox)
    DrawablePtr pDrawable;
    GCPtr pGC;
    int nBox;			       /* number of boxes to fill */
    register BoxPtr pBox;	       /* pointer to list of boxes to fill */
{
    unsigned long *src;
    int stippleHeight;
    PixmapPtr pPix;
    int destPitch;
    int width, height;
    int pixWidth;
    int xrot, yrot;
    unsigned char *pattern;
    unsigned int mask;
    int vidpattern;

#ifdef DEBUG
    ErrorF("CHIPS: siscfbFillRectTile: Called ");
#endif

    pPix = pGC->tile.pixmap;
    width = pPix->drawable.width;
    height = pPix->drawable.height;
    pixWidth = PixmapBytePad(width, pPix->drawable.bitsPerPixel);

    destPitch = (int)
	(((PixmapPtr) (pDrawable->pScreen->devPrivate))->devKind);
    xrot = pDrawable->x + pGC->patOrg.x;
    yrot = pDrawable->y + pGC->patOrg.y;

    src = (unsigned long *)pPix->devPrivate.ptr;

    /* Handle only 8/16bpp tiles. 24bpp tiles are only
     * available on the 65550/4 and interleaving becomes
     * more difficult at higher depths
     */
    switch (vgaBitsPerPixel) {
    case 8:
	mask = 0xFF;
#if 0		/* disable tiling using blit 8x8 */
	if (width == 8 && height == 8)
	    goto tile8x8;
#endif
	break;
    case 16:
	mask = 0xFFFF;
	break;
    case 24:
	mask = 0xFFFFFF;
	break;
    }

#if 1				       /* disable tiling using blit engine */
    /* For largish tiles, use the blit engine repeatly to do the fill */
    if (width * height >= 500)
	goto tileblit;
#endif

#ifdef DEBUG
    ErrorF(" unaccelerated tile width = %d, Height = %d \n", width, height);
#endif
    switch (vgaBitsPerPixel) {
    case 8:
	if (!((cfbPrivGCPtr) pGC->devPrivates[cfbGCPrivateIndex].ptr)->
	    pRotatedPixmap) {
	    vga256FillRectTileOdd(pDrawable, pGC, nBox, pBox);
	} else {
	    if (pGC->alu == GXcopy && (pGC->planemask & 0xFF)
		== 0xFF) {
		vga256FillRectTile32Copy(pDrawable, pGC, nBox, pBox);
	    } else {
		vga256FillRectTile32General(pDrawable, pGC, nBox, pBox);
	    }
	}
	break;
    case 16:
	if (!((cfbPrivGCPtr) pGC->devPrivates[cfbGCPrivateIndex].ptr)->
	    pRotatedPixmap) {
	    cfb16FillRectTileOdd(pDrawable, pGC, nBox, pBox);
	} else {
	    if (pGC->alu == GXcopy && (pGC->planemask & 0xFFFF)
		== 0xFFFF) {
		cfb16FillRectTile32Copy(pDrawable, pGC, nBox, pBox);
	    } else {
		cfb16FillRectTile32General(pDrawable, pGC, nBox, pBox);
	    }
	}
	break;
    case 24:
	if (!((cfbPrivGCPtr) pGC->devPrivates[cfbGCPrivateIndex].ptr)->
	    pRotatedPixmap) {
	    cfb24FillRectTileOdd(pDrawable, pGC, nBox, pBox);
	} else {
	    if (pGC->alu == GXcopy && (pGC->planemask & 0xFFFFFF)
		== 0xFFFFFF) {
		cfb24FillRectTile32Copy(pDrawable, pGC, nBox, pBox);
	    } else {
		cfb24FillRectTile32General(pDrawable, pGC, nBox, pBox);
	    }
	}
	break;
    }
    return;

  tile8x8:
    /*
     * This function does 8x8 tile fills with the BitBLT engine.
     */
#ifdef DEBUG
    ErrorF("8x8 accelerated tile, xrot: %d, yrot: %d \n", xrot, yrot);
    ErrorF("x: %d, y: %d, Xorg: %d, Yorg: %d \n", pDrawable->x,
	pDrawable->y, pGC->patOrg.x, pGC->patOrg.y);
#endif
    pattern = NULL;
    xrot &= 7;
    for (; nBox; nBox--, pBox++) {
	int w, h;

	w = pBox->x2 - pBox->x1;
	h = pBox->y2 - pBox->y1;
	if (w * h < 5000) {
	    switch (vgaBitsPerPixel) {
	    case 8:
		vga256FillRectTileOdd(pDrawable, pGC, 1, pBox);
		break;
	    case 16:
		cfb16FillRectTileOdd(pDrawable, pGC, 1, pBox);
		break;
	    }
	    continue;
	}
	if (pattern == NULL) {
	    int i, j;

	    /*
	     * Generate a copy of the tile in system memory
	     * to handle rotation in the x-direction. Rotation
	     * in the y-direction is handled by the blitter
	     */
	    pattern = (unsigned char *)ALLOCATE_LOCAL(8 * 8 *
		vgaBytesPerPixel);
	    for (i = 0; i < 8; i++) {
		for (j = 8 - xrot; j < 8; j++)
		    memcpy(pattern + i * 8 * vgaBytesPerPixel,
			(unsigned char *)src + i * pixWidth *
			vgaBytesPerPixel + 8 - xrot, xrot *
			vgaBytesPerPixel);
		for (j = 0; j < 8 - xrot; j++)
		    memcpy(pattern + i * 8 * vgaBytesPerPixel + xrot,
			(unsigned char *)src + i * pixWidth *
			vgaBytesPerPixel, (8 - xrot) * vgaBytesPerPixel);
	    }
	}
	sisMMIOBLT8x8PatternFill(pBox->y1 * destPitch + pBox->x1,
				 w, h, pattern, ((pBox->y1 - yrot) & 7), 8,
				 destPitch);
    }
    if (pattern != NULL)
	DEALLOCATE_LOCAL(pattern);
    return;


#if 1
  tileblit:
    /* Tile with repeated BitBLT. For largish tiles. */

#ifdef DEBUG
    ErrorF(" BitBLT accelerated tile width = %d, Height = %d \n",
	width, height);
#endif
    for (; nBox; nBox--, pBox++) {
	int w, h, x, y;
	int blitx, blith, blity;
	BoxRec box;

	x = pBox->x1;
	y = pBox->y1;
	w = pBox->x2 - x;
	h = pBox->y2 - y;
	/* Don't use the blitter for small tile fills. */
	if (w * h < 250) {
	    switch (vgaBitsPerPixel) {
	    case 8:
		vga256FillRectTileOdd(pDrawable, pGC, 1, pBox);
		break;
	    case 16:
		cfb16FillRectTileOdd(pDrawable, pGC, 1, pBox);
		break;
	    case 24:
		cfb24FillRectTileOdd(pDrawable, pGC, 1, pBox);
		break;
	    }
	    continue;
	}
	box.x1 = x;
	box.y1 = y;
	box.x2 = x + min(width, w);
	box.y2 = y + min(height, h);
	/* Draw first tile. */
	switch (vgaBitsPerPixel) {
	case 8:
	    vga256FillRectTileOdd(pDrawable, pGC, 1, &box);
	    break;
	case 16:
	    cfb16FillRectTileOdd(pDrawable, pGC, 1, &box);
	    break;
	case 24:
	    cfb24FillRectTileOdd(pDrawable, pGC, 1, &box);
	    break;
	}

	/* Repeat tile horizontally. Note that the source and 
	 * destination address is hacked to force a screen to 
	 * screen blit.
	 */
	blitx = x + width;	       /* Will skip if width > w. */
	blith = min(height, h);

	while (blitx <= x + w - width) {
	    sisMMIOBitBlt(VGABASE, VGABASE, destPitch, destPitch, x,
			  y, blitx, y, width, blith, 1, 1, GXcopy,
			  mask);
	    blitx += width;
	}
	/* Right edge. Note that the source and destination address
	 * is hacked to force a screen to screen blit.
	 */
	if (blitx < x + w)
	    sisMMIOBitBlt(VGABASE, VGABASE, destPitch, destPitch, x,
			  y, blitx, y, x + w - blitx, blith, 1, 1,
			  GXcopy, mask);

	/* Repeat row of tiles vertically. */
	blity = y + height;	       /* Will skip if height > h. */
	while (blity < y + h - height) {
		sisMMIOBitBlt(VGABASE, VGABASE, destPitch, destPitch, x,
			y, x, blity, w, height, 1, 1, GXcopy,
			mask);
	    blity += height;
	}
	/* Bottom edge. */
	if (blity < y + h)
	    sisMMIOBitBlt(VGABASE, VGABASE, destPitch, destPitch, x,
			y, x, blity, w, y + h - blity, 1, 1, GXcopy,
			mask);
    }
    return;
#endif

}
