/* $XConsortium: Ps.h /main/3 1996/11/16 15:24:28 rws $ */
/*
 * (c) Copyright 1996 Hewlett-Packard Company
 * (c) Copyright 1996 International Business Machines Corp.
 * (c) Copyright 1996 Sun Microsystems, Inc.
 * (c) Copyright 1996 Novell, Inc.
 * (c) Copyright 1996 Digital Equipment Corp.
 * (c) Copyright 1996 Fujitsu Limited
 * (c) Copyright 1996 Hitachi, Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the names of the copyright holders
 * shall not be used in advertising or otherwise to promote the sale, use
 * or other dealings in this Software without prior written authorization
 * from said copyright holders.
 */

/*******************************************************************
**
**    *********************************************************
**    *
**    *  File:		Ps.h
**    *
**    *  Contents:  defines and includes for the Ps driver
**    *             for a printing X server.
**    *
**    *  Created By:	Roger Helmendach (Liberty Systems)
**    *
**    *  Copyright:	Copyright 1996 X Consortium, Inc.
**    *
**    *********************************************************
** 
********************************************************************/
/* $XFree86: xc/programs/Xserver/Xprint/ps/Ps.h,v 1.2 1997/01/14 22:16:17 dawes Exp $ */

#ifndef _PS_H_
#define _PS_H_

#include <stdio.h>

#ifdef abs
#undef abs   /* this is because of a non-Spec1170ness in misc.h */
#endif
#include <stdlib.h>
#include "scrnintstr.h"
#include "dix.h"

/*
#include "X.h" 
#include "Xproto.h"
#include "Xatom.h"
#include "misc.h"
#include "screenint.h"
#include "colormapst.h"
#include "windowstr.h"
#include "propertyst.h"
#include "servermd.h"*/    /* needed for IMAGE_BUFSIZE */

#include "PsDef.h"
#include "psout.h"

#define _XP_PRINT_SERVER_
#include "Print.h"
#include "extensions/Printstr.h"
#undef _XP_PRINT_SERVER_

#include "miscstruct.h"
#include "fontstruct.h"
#include "dixfontstr.h"
#include "gcstruct.h"

/*
 *  Some sleazes to force the XrmDB stuff into the server
 */
typedef char *XPointer;
#define Status int
#define True 1
#define False 0
#include "misc.h"
#include <Xfuncproto.h>
#include "../Xresource.h"

/*
 *  Public index variables from PsInit.c
 */

extern int PsScreenPrivateIndex;
extern int PsWindowPrivateIndex;
extern int PsContextPrivateIndex;
extern int PsPixmapPrivateIndex;
extern int PsGCPrivateIndex;

/*
 *  Display list structures
 */

#define DPY_BLOCKSIZE 4096

typedef struct
{
  int      mode;
  int      nPoints;
  xPoint  *pPoints;
} PsPolyPointsRec;

typedef struct
{
  int        nSegments;
  xSegment  *pSegments;
} PsSegmentsRec;

typedef struct
{
  int          nRects;
  xRectangle  *pRects;
} PsRectanglesRec;

typedef struct
{
  int     nArcs;
  xArc   *pArcs;
} PsArcsRec;

typedef struct
{
  int     x;
  int     y;
  int     count;
  char   *string;
} PsText8Rec;

typedef struct
{
  int             x;
  int             y;
  int             count;
  unsigned short *string;
} PsText16Rec;

typedef struct
{
  int     depth;
  int     x;
  int     y;
  int     w;
  int     h;
  int     leftPad;
  int     format;
  int     res;		/* image resolution */
  char   *pData;
} PsImageRec;

typedef struct
{
  int   x;
  int   y;
  int   w;
  int   h;
} PsFrameRec;

typedef enum
{
  PolyPointCmd,
  PolyLineCmd,
  PolySegmentCmd,
  PolyRectangleCmd,
  FillPolygonCmd,
  PolyFillRectCmd,
  PolyArcCmd,
  PolyFillArcCmd,
  Text8Cmd,
  Text16Cmd,
  TextI8Cmd,
  TextI16Cmd,
  PutImageCmd,
  BeginFrameCmd,
  EndFrameCmd
} DisplayElmType;

typedef struct _DisplayElmRec
{
  DisplayElmType  type;
  GCPtr           gc;
  union
  {
    PsPolyPointsRec  polyPts;
    PsSegmentsRec    segments;
    PsRectanglesRec  rects;
    PsArcsRec        arcs;
    PsText8Rec       text8;
    PsText16Rec      text16;
    PsImageRec       image;
    PsFrameRec       frame;
  } c;
} DisplayElmRec;

typedef DisplayElmRec *DisplayElmPtr;

typedef struct _DisplayListRec
{
  struct _DisplayListRec *next;
  int                     nelms;
  DisplayElmRec           elms[DPY_BLOCKSIZE];
} DisplayListRec;

typedef DisplayListRec *DisplayListPtr;

/*
 *  Private structures
 */

typedef struct
{
  XrmDatabase   resDB;
  ColormapPtr   CMap;
  Bool        (*DestroyWindow)();
} PsScreenPrivRec, *PsScreenPrivPtr;

typedef struct
{
  char              *jobFileName;
  FILE              *pJobFile;
  GC                 lastGC;
  unsigned char     *dash;
  int                validGC;
  ClientPtr          getDocClient;
  int                getDocBufSize;
  PsOutPtr           pPsOut;
} PsContextPrivRec, *PsContextPrivPtr;

typedef struct
{
  int          validContext;
  XpContextPtr context;
} PsWindowPrivRec, *PsWindowPrivPtr;

typedef struct
{
  unsigned  freeCompClip;
  RegionPtr pCompositeClip;
} PsGCPrivRec, *PsGCPrivPtr;

typedef struct
{
  XpContextPtr    context;
  GC              lastGC;
  int             validGC;
  DisplayListPtr  dispList;
} PsPixmapPrivRec, *PsPixmapPrivPtr;

/*
 *  Macro functions
 */

#define SEND_PS(f,c) fwrite( c, sizeof( char ), strlen( c ), f )
#define MIN(a,b) (((a)<(b))?(a):(b))
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

/*
 *  Functions in PsInit.c
 */

extern Bool InitializePsDriver(int ndx, ScreenPtr pScreen, int argc,
    char **argv);
static Bool         PsDestroyContext(XpContextPtr pCon);
extern XpContextPtr PsGetContextFromWindow(WindowPtr win);

/*
 *  Functions in PsPrint.c
 */

extern int PsStartJob(XpContextPtr pCon, Bool sendClientData, ClientPtr client);
extern int PsEndJob(XpContextPtr pCon, Bool cancel);
extern int PsStartPage(XpContextPtr pCon, WindowPtr pWin);
extern int PsEndPage(XpContextPtr pCon, WindowPtr pWin);
extern int PsStartDoc(XpContextPtr pCon);
extern int PsEndDoc(XpContextPtr pCon, Bool cancel);
extern int PsDocumentData(XpContextPtr pCon, DrawablePtr pDraw, char *pData,
    int len_data, char *pFmt, int len_fmt, char *pOpt, int len_opt,
    ClientPtr client);
extern int PsGetDocumentData(XpContextPtr pCon, ClientPtr client,
    int maxBufferSize);

/*
 *  Functions in PsGC.c
 */

extern Bool PsCreateGC(GCPtr pGC);
static int  PsGetDrawablePrivateStuff(DrawablePtr pDrawable, GC *gc,
                                      unsigned long *valid, PsOutPtr *psOut,
                                      ColormapPtr *cMap);
extern int  PsUpdateDrawableGC(GCPtr pGC, DrawablePtr pDrawable,
                               PsOutPtr *psOut, ColormapPtr *cMap);
extern void PsValidateGC(GCPtr pGC, unsigned long changes, DrawablePtr pDrawable);
extern void PsChangeGC(GCPtr pGC, unsigned long changes);
extern void PsCopyGC(GCPtr pGCSrc, unsigned long mask, GCPtr pGCDst);
extern void PsDestroyGC(GCPtr pGC);
extern void PsChangeClip(GCPtr pGC, int type, pointer pValue, int nrects);
extern void PsDestroyClip(GCPtr pGC);
extern void PsCopyClip(GCPtr pgcDst, GCPtr pgcSrc);

extern GCPtr PsCreateAndCopyGC(DrawablePtr pDrawable, GCPtr pSrc);

/*
 *  Functions in PsMisc.c
 */

extern void PsQueryBestSize(int type, short *pwidth, short *pheight,
                            ScreenPtr pScreen);
extern Bool PsCloseScreen(int index, ScreenPtr pScreen);
extern void PsLineAttrs(PsOutPtr psOut, GCPtr pGC, ColormapPtr cMap);
extern int PsGetMediumDimensions(
    XpContextPtr pCon,
    CARD16 *pWidth,
    CARD16 *pHeight);
extern int PsGetReproducibleArea(
    XpContextPtr pCon,
    xRectangle *pRect);
extern int PsSetImageResolution(
    XpContextPtr pCon,
    int imageRes,
    Bool *status);

/*
 *  Functions in PsSpans.c
 */

extern void PsFillSpans(DrawablePtr pDrawable, GCPtr pGC, int nSpans,
                        DDXPointPtr pPoints, int *pWidths, int fSorted);
extern void PsSetSpans(DrawablePtr pDrawable, GCPtr pGC, char *pSrc,
                       DDXPointPtr pPoints, int *pWidths, int nSpans,
                       int fSorted);

/*
 *  Functions in PsArea.c
 */

extern void PsPutScaledImage(DrawablePtr pDrawable, GCPtr pGC, int depth,
                       int x, int y, int w, int h, int leftPad, int format,
                       int imageRes, char *pImage);
extern void PsPutImage(DrawablePtr pDrawable, GCPtr pGC, int depth,
                       int x, int y, int w, int h, int leftPad, int format,
                       char *pImage);
extern RegionPtr PsCopyArea(DrawablePtr pSrc, DrawablePtr pDst, GCPtr pGC,
                            int srcx, int srcy, int width, int height,
                            int dstx, int dsty);
extern RegionPtr PsCopyPlane(DrawablePtr pSrc, DrawablePtr pDst, GCPtr pGC,
                             int srcx, int srcy, int width, int height,
                             int dstx, int dsty, unsigned long plane);

/*
 *  Functions in PsPixel.c
 */

extern void PsPolyPoint(DrawablePtr pDrawable, GCPtr pGC, int mode,
                       int nPoints, xPoint *pPoints);
extern void PsPushPixels(GCPtr pGC, PixmapPtr pBitmap, DrawablePtr pDrawable,
                         int width, int height, int x, int y);

/*
 *  Functions in PsLine.c
 */

extern void PsPolyLine(DrawablePtr pDrawable, GCPtr pGC, int mode,
                       int nPoints, xPoint *pPoints);
extern void PsPolySegment(DrawablePtr pDrawable, GCPtr pGC, int nSegments,
                          xSegment *pSegments);

/*
 *  Functions in PsPolygon.c
 */

extern void PsPolyRectangle(DrawablePtr pDrawable, GCPtr pGC, int nRects,
                            xRectangle *pRects);
extern void PsFillPolygon(DrawablePtr pDrawable, GCPtr pGC, int shape,
                          int mode, int nPoints, DDXPointPtr pPoints);
extern void PsPolyFillRect(DrawablePtr pDrawable, GCPtr pGC, int nRects,
                          xRectangle *pRects);

/*
 *  Functions in PsPolygon.c
 */

extern void PsPolyArc(DrawablePtr pDrawable, GCPtr pGC, int nArcs,
                            xArc *pArcs);
extern void PsPolyFillArc(DrawablePtr pDrawable, GCPtr pGC, int nArcs,
                            xArc *pArcs);

/*
 *  Functions in PsText.c
 */

extern int  PsPolyText8(DrawablePtr pDrawable, GCPtr pGC, int x, int y,
                        int count, char *string);
extern int  PsPolyText16(DrawablePtr pDrawable, GCPtr pGC, int x, int y,
                         int count, unsigned short *string);
extern void PsImageText8(DrawablePtr pDrawable, GCPtr pGC, int x, int y,
                         int count, char *string);
extern void PsImageText16(DrawablePtr pDrawable, GCPtr pGC, int x, int y,
                          int count, unsigned short *string);
extern void PsImageGlyphBlt(DrawablePtr pDrawable, GCPtr pGC, int x, int y,
                            unsigned int nGlyphs, CharInfoPtr *pCharInfo,
                            pointer pGlyphBase);
extern void PsPolyGlyphBlt(DrawablePtr pDrawable, GCPtr pGC, int x, int y,
                           unsigned int nGlyphs, CharInfoPtr *pCharInfo,
                           pointer pGlyphBase);

/*
 *  Functions in PsWindow.c
 */

extern Bool PsCreateWindow(WindowPtr pWin);
extern Bool PsMapWindow(WindowPtr pWin);
extern Bool PsPositionWindow(WindowPtr pWin, int x, int y);
extern Bool PsUnmapWindow(WindowPtr pWin);
extern void PsCopyWindow(WindowPtr pWin, DDXPointRec ptOldOrg,
                         RegionPtr prgnSrc);
extern Bool PsChangeWindowAttributes(WindowPtr pWin, unsigned long mask);
extern void PsPaintWindow(WindowPtr pWin, RegionPtr pRegion, int what);
extern Bool PsDestroyWindow(WindowPtr pWin);

/*
 *  Functions in PsFonts.c
 */

extern Bool PsRealizeFont(ScreenPtr pscr, FontPtr pFont);
extern Bool PsUnrealizeFont(ScreenPtr pscr, FontPtr pFont);
extern char *PsGetFontName(FontPtr pFont);
extern int PsGetFontSize(FontPtr pFont, float *mtx);
extern char *PsGetPSFontName(FontPtr pFont);
extern int PsIsISOLatin1Encoding(FontPtr pFont);

/*
 *  Functions in PsAttr.c
 */

extern char *PsGetAttributes(XpContextPtr pCon, XPAttributes pool);
extern char *PsGetOneAttribute(XpContextPtr pCon, XPAttributes pool,
                               char *attr);
extern int PsAugmentAttributes(XpContextPtr pCon, XPAttributes pool,
                               char *attrs);
extern int PsSetAttributes(XpContextPtr pCon, XPAttributes pool, char *attrs);

/*
 *  Functions in PsColor.c
 */

extern Bool PsCreateColormap(ColormapPtr pColor);
extern void PsDestroyColormap(ColormapPtr pColor);
extern void PsInstallColormap(ColormapPtr pColor);
extern void PsUninstallColormap(ColormapPtr pColor);
extern int  PsListInstalledColormaps(ScreenPtr pScreen, XID *pCmapList);
extern void PsStoreColors(ColormapPtr pColor, int ndef, xColorItem *pdefs);
extern void PsResolveColor(unsigned short *pRed, unsigned short *pGreen,
                           unsigned short *pBlue, VisualPtr pVisual);
extern int  PsGetPixelColor(ColormapPtr cMap, int pixval);
extern void PsSetFillColor(DrawablePtr pDrawable, GCPtr pGC, PsOutPtr psOut,
                           ColormapPtr cMap);

/*
 *  Functions in PsPixmap.c
 */

extern PixmapPtr PsCreatePixmap(ScreenPtr pScreen, int width, int height,
                                int depth);
extern Bool PsDestroyPixmap(PixmapPtr pPixmap);
extern DisplayListPtr PsGetFreeDisplayBlock(PsPixmapPrivPtr priv);
extern void PsReplayPixmap(PixmapPtr pix, DrawablePtr pDrawable);
extern int PsCloneDisplayElm(PixmapPtr dst,
			     DisplayElmPtr elm, DisplayElmPtr newElm,
                             int xoff, int yoff);
extern void PsCopyDisplayList(PixmapPtr src, PixmapPtr dst, int xoff,
                              int yoff, int x, int y, int w, int h);
extern PsElmPtr PsCreateFillElementList(PixmapPtr pix, int *nElms);
extern PsElmPtr PsCloneFillElementList(int nElms, PsElmPtr elms);
extern void PsDestroyFillElementList(int nElms, PsElmPtr elms);

#endif  /* _PS_H_ */
