/* $XConsortium: PsInit.c /main/5 1996/12/30 16:38:33 kaleb $ */
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
**    *  File:		PsInit.c
**    *
**    *  Contents:      Initialization code of Ps driver for the print server.
**    *
**    *  Created By:	Roger Helmendach (Liberty Systems)
**    *
**    *  Copyright:	Copyright 1996 X Consortium, Inc.
**    *
**    *********************************************************
** 
********************************************************************/
/* $XFree86: xc/programs/Xserver/Xprint/ps/PsInit.c,v 1.4 1996/12/31 07:06:27 dawes Exp $ */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "Ps.h"
#include "AttrValid.h"
#include "../../mfb/mfb.h"

#include "windowstr.h"

static void AllocatePsPrivates(ScreenPtr pScreen);
static int PsInitContext(XpContextPtr pCon);

extern Bool _XpBoolNoop();
extern void _XpVoidNoop();
extern Bool cfbCreateDefColormap(ScreenPtr pScreen);

int PsScreenPrivateIndex;
int PsContextPrivateIndex;
int PsPixmapPrivateIndex;
int PsWindowPrivateIndex;
int PsGCPrivateIndex;

Bool
InitializePsDriver(ndx, pScreen, argc, argv)
  int         ndx;
  ScreenPtr   pScreen;
  int         argc;
  char      **argv;
{
  int               maxXres, maxYres, maxWidth, maxHeight;
  int               maxRes, maxDim, numBytes;
  PsScreenPrivPtr   pPriv;
  char            **printerNames;
  int               numPrinters;
  int               nVisuals;
  int               nDepths;
  VisualPtr         visuals;
  DepthPtr          depths;

/*
 * Register this driver's InitContext function with the print
 * extension.
 */
  XpRegisterInitFunc(pScreen, "XP-POSTSCRIPT", PsInitContext);

/*
 * Create and fill in the devPrivate for the PS driver.
 */
  AllocatePsPrivates(pScreen);

  pPriv = (PsScreenPrivPtr)pScreen->devPrivates[PsScreenPrivateIndex].ptr;
/*pPriv->resDB = rmdb;*/

  pScreen->defColormap            = (Colormap) FakeClientID(0);
  pScreen->blackPixel             = 1;
  pScreen->whitePixel             = 0;
  pScreen->QueryBestSize          = (QueryBestSizeProcPtr)PsQueryBestSize;
  pScreen->SaveScreen             = _XpBoolNoop;
  pScreen->GetImage               = _XpVoidNoop;
  pScreen->GetSpans               = _XpVoidNoop;
  pScreen->CreateWindow           = PsCreateWindow;
  pScreen->DestroyWindow          = PsDestroyWindow;
  pScreen->PositionWindow         = PsPositionWindow;
  pScreen->ChangeWindowAttributes = PsChangeWindowAttributes;
  pScreen->RealizeWindow          = PsMapWindow;
  pScreen->UnrealizeWindow        = PsUnmapWindow;
  pScreen->PaintWindowBackground  = PsPaintWindow;
  pScreen->PaintWindowBorder      = PsPaintWindow;
  pScreen->CloseScreen            = PsCloseScreen;
  pScreen->CopyWindow             = PsCopyWindow;
       /* XXX Hard routine to write! */

/*
 * These two are going to be VERY different...
 */
  pScreen->CreatePixmap           = PsCreatePixmap;
  pScreen->DestroyPixmap          = PsDestroyPixmap;
  pScreen->RealizeFont            = PsRealizeFont;
  pScreen->UnrealizeFont          = PsUnrealizeFont;
  pScreen->CreateGC               = PsCreateGC;
  pScreen->CreateColormap         = PsCreateColormap;
  pScreen->DestroyColormap        = PsDestroyColormap;
  pScreen->InstallColormap        = PsInstallColormap;
  pScreen->UninstallColormap      = PsUninstallColormap;
  pScreen->ListInstalledColormaps = PsListInstalledColormaps;
  pScreen->StoreColors            = PsStoreColors;
  pScreen->ResolveColor           = PsResolveColor;
    /* Will BitmapToRegion make any difference at all? */
  pScreen->BitmapToRegion         = mfbPixmapToRegion;

  nVisuals = 2;
  nDepths  = 2;
  visuals  = (VisualPtr)xalloc(nVisuals*sizeof(VisualRec));
  depths   = (DepthPtr) xalloc(nDepths*sizeof(DepthRec));

  visuals[0].vid             = FakeClientID(0);
  visuals[0].class           = TrueColor;
  visuals[0].bitsPerRGBValue = 8;
  visuals[0].ColormapEntries = 256;
  visuals[0].nplanes         = 24;
  visuals[0].redMask         = 0x00FF0000;
  visuals[0].greenMask       = 0x0000FF00;
  visuals[0].blueMask        = 0x000000FF;
  visuals[0].offsetRed       = 16;
  visuals[0].offsetGreen     = 8;
  visuals[0].offsetBlue      = 0;

  visuals[1].vid             = FakeClientID(0);
  visuals[1].class           = PseudoColor;
  visuals[1].bitsPerRGBValue = 0;
  visuals[1].ColormapEntries = 256;
  visuals[1].nplanes         = 8;
  visuals[1].redMask         = 0x0;
  visuals[1].greenMask       = 0x0;
  visuals[1].blueMask        = 0x0;
  visuals[1].offsetRed       = 0x0;
  visuals[1].offsetGreen     = 0x0;
  visuals[1].offsetBlue      = 0x0;

  depths[0].depth   = 24;
  depths[0].numVids = 1;
  depths[0].vids    = &visuals[0].vid;

  depths[1].depth   = 8;
  depths[1].numVids = 1;
  depths[1].vids    = &visuals[1].vid;

/*  THE FOLLOWING CAUSES SERVER DEFAULT VISUAL TO BE 24 BIT  */
/*  miScreenInit(pScreen, (pointer)0,
	       pScreen->width, pScreen->height,
	       pScreen->width / (pScreen->mmWidth / 25.40), 
	       pScreen->height / (pScreen->mmHeight / 25.40),
	       0, 24, nDepths,
               depths, visuals[1].vid, nVisuals, visuals, (miBSFuncPtr)0); */

/*  THE FOLLOWING CAUSES SERVER DEFAULT VISUAL TO BE 8 BIT  */
  miScreenInit(pScreen, (pointer)0,
	       pScreen->width, pScreen->height,
	       (int) (pScreen->width / (pScreen->mmWidth / 25.40)), 
	       (int) (pScreen->height / (pScreen->mmHeight / 25.40)),
	       0, 8, nDepths,
               depths, visuals[1].vid, nVisuals, visuals, (miBSFuncPtr)0);

  if( cfbCreateDefColormap(pScreen)==FALSE ) return FALSE;

/*scalingScreenInit(pScreen);*/

  return TRUE;
}

static void
AllocatePsPrivates(ScreenPtr pScreen)
{
  static int PsGeneration = -1;

  if(PsGeneration != serverGeneration)
  {
    PsScreenPrivateIndex = AllocateScreenPrivateIndex();

    PsWindowPrivateIndex = AllocateWindowPrivateIndex();
    AllocateWindowPrivate(pScreen, PsWindowPrivateIndex,
                          sizeof(PsWindowPrivRec));

    PsContextPrivateIndex = XpAllocateContextPrivateIndex();
    XpAllocateContextPrivate(PsContextPrivateIndex, 
                             sizeof(PsContextPrivRec));

    PsGCPrivateIndex = AllocateGCPrivateIndex();
    AllocateGCPrivate(pScreen, PsGCPrivateIndex,
                      sizeof(PsGCPrivRec));

    PsPixmapPrivateIndex = AllocatePixmapPrivateIndex();
    AllocatePixmapPrivate(pScreen, PsPixmapPrivateIndex,
                          sizeof(PsPixmapPrivRec));

    PsGeneration = serverGeneration;
  }
  pScreen->devPrivates[PsScreenPrivateIndex].ptr =
           (pointer)xalloc(sizeof(PsScreenPrivRec));
}

/*
 * PsInitContext
 *
 * Establish the appropriate values for a PrintContext used with the PS
 * driver.
 */

static char DOC_ATT_SUPP[]="document-attributes-supported";
static char DOC_ATT_VAL[]="document-format";
static char JOB_ATT_SUPP[]="job-attributes-supported";
static char JOB_ATT_VAL[]="";
static char PAGE_ATT_SUPP[]="xp-page-attributes-supported";
static char PAGE_ATT_VAL[]="content-orientation default-printer-resolution \
default-input-tray default-medium plex";

static int
PsInitContext(pCon)
  XpContextPtr pCon;
{
  XpDriverFuncsPtr pFuncs;
  PsContextPrivPtr pConPriv;
  char *server, *attrStr;
  extern XpValidatePoolsRec PsValidatePoolsRec;
    
  /*
   * Initialize the attribute store for this printer.
   */
  XpInitAttributes(pCon);

  /*
   * Initialize the function pointers
   */
  pFuncs = &(pCon->funcs);
  pFuncs->StartJob          = PsStartJob;
  pFuncs->EndJob            = PsEndJob;
  pFuncs->StartDoc          = PsStartDoc;
  pFuncs->EndDoc            = PsEndDoc;
  pFuncs->StartPage         = PsStartPage;
  pFuncs->EndPage           = PsEndPage;
  pFuncs->PutDocumentData   = PsDocumentData;
  pFuncs->GetDocumentData   = PsGetDocumentData;
  pFuncs->GetAttributes     = (char *(*)())PsGetAttributes;
  pFuncs->SetAttributes     = (int   (*)())PsSetAttributes;
  pFuncs->AugmentAttributes = (int   (*)())PsAugmentAttributes;
  pFuncs->GetOneAttribute   = (char *(*)())PsGetOneAttribute;
  pFuncs->DestroyContext    = PsDestroyContext;
  pFuncs->GetMediumDimensions = PsGetMediumDimensions;
  pFuncs->GetReproducibleArea = PsGetReproducibleArea;
  pFuncs->SetImageResolution = PsSetImageResolution;
    
  /*
   * Set up the context privates
   */
  pConPriv =
      (PsContextPrivPtr)pCon->devPrivates[PsContextPrivateIndex].ptr;

  pConPriv->jobFileName  = (char *)NULL;
  pConPriv->pJobFile     = (FILE *)NULL;

  pConPriv->getDocClient = (ClientPtr)NULL;
  pConPriv->getDocBufSize = 0;

  /*
   * document-attributes-supported
   */
  server = XpGetOneAttribute( pCon, XPServerAttr, DOC_ATT_SUPP );
  if ((attrStr = (char *) xalloc(strlen(server) +
				strlen(DOC_ATT_SUPP) + strlen(DOC_ATT_VAL)
				+ strlen(PAGE_ATT_VAL) + 6)) == NULL) 
  {
      return BadAlloc;
  }
  sprintf(attrStr, "*%s:\t%s %s %s", 
	  DOC_ATT_SUPP, server, DOC_ATT_VAL, PAGE_ATT_VAL);
  XpAugmentAttributes( pCon, XPPrinterAttr, attrStr);
  xfree(attrStr);
    
  /*
   * job-attributes-supported
   */
  server = XpGetOneAttribute( pCon, XPServerAttr, JOB_ATT_SUPP );
  if ((attrStr = (char *) xalloc(strlen(server) + strlen(JOB_ATT_SUPP) +
				 strlen(JOB_ATT_VAL) + 4)) == NULL)
  {
      return BadAlloc;
  }
  sprintf(attrStr, "*%s:\t%s %s", JOB_ATT_SUPP, server, JOB_ATT_VAL);
  XpAugmentAttributes(pCon, XPPrinterAttr, attrStr);
  xfree(attrStr);
    
  /*
   * xp-page-attributes-supported
   */
  server = XpGetOneAttribute( pCon, XPServerAttr, PAGE_ATT_SUPP );
  if ((attrStr = (char *) xalloc(strlen(server) + strlen(PAGE_ATT_SUPP) +
				 strlen(PAGE_ATT_VAL) + 4)) == NULL)
  {
      return BadAlloc;
  }
  sprintf(attrStr, "*%s:\t%s %s", PAGE_ATT_SUPP, server, PAGE_ATT_VAL);
  XpAugmentAttributes(pCon, XPPrinterAttr, attrStr);
  xfree(attrStr);

  /*
   * Validate the attribute pools
   */
  XpValidateAttributePool(pCon, XPPrinterAttr, &PsValidatePoolsRec);
  XpValidateAttributePool(pCon, XPDocAttr, &PsValidatePoolsRec);
  XpValidateAttributePool(pCon, XPJobAttr, &PsValidatePoolsRec);
  XpValidateAttributePool(pCon, XPPageAttr, &PsValidatePoolsRec);

  return Success;
}

static Bool
PsDestroyContext(pCon)
  XpContextPtr pCon;
{
  PsContextPrivPtr pConPriv =
      (PsContextPrivPtr)pCon->devPrivates[PsContextPrivateIndex].ptr;
    
  if( pConPriv->pJobFile!=(FILE *)NULL )
  {
    fclose(pConPriv->pJobFile);
    pConPriv->pJobFile = NULL;
  }
  if( pConPriv->jobFileName!=(char *)NULL )
  {
    unlink(pConPriv->jobFileName);
    xfree(pConPriv->jobFileName);
    pConPriv->jobFileName = (char *)NULL;
  }

/*### free up visuals/depths ###*/

  return Success;
}

XpContextPtr
PsGetContextFromWindow(win)
  WindowPtr win;
{
  PsWindowPrivPtr pPriv;

  while( win )
  {
    pPriv = (PsWindowPrivPtr)win->devPrivates[PsWindowPrivateIndex].ptr;
    if( pPriv->validContext ) return pPriv->context;
    win = win->parent;
  }

  return NULL;
}
