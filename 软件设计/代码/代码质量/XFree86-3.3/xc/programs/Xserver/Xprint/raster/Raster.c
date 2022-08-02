/* $XConsortium: Raster.c /main/3 1996/11/16 15:26:23 rws $ */
/*
(c) Copyright 1996 Hewlett-Packard Company
(c) Copyright 1996 International Business Machines Corp.
(c) Copyright 1996 Sun Microsystems, Inc.
(c) Copyright 1996 Novell, Inc.
(c) Copyright 1996 Digital Equipment Corp.
(c) Copyright 1996 Fujitsu Limited
(c) Copyright 1996 Hitachi, Ltd.

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
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the names of the copyright holders shall
not be used in advertising or otherwise to promote the sale, use or other
dealings in this Software without prior written authorization from said
copyright holders.
*/
/*******************************************************************
**
**    *********************************************************
**    *
**    *  File:		printer/Raster.c
**    *
**    *  Contents:
**    *                 Raster driver for the print server.
**    *
**    *  Copyright:	Copyright 1993, 1995 Hewlett-Packard Company
**    *
**    *********************************************************
** 
********************************************************************/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include "X.h"
#include "Xos.h"	/* for SIGCLD on pre-POSIX systems */
#define NEED_EVENTS
#include "Xproto.h"
#undef NEED_EVENTS
#include "Xatom.h"
#include "misc.h"
#include "dixstruct.h"
#include "scrnintstr.h"
#include "screenint.h"
#include "colormapst.h"
#include "windowstr.h"
#include "propertyst.h"
#include "servermd.h"	/* needed for IMAGE_BUFSIZE */

#define _XP_PRINT_SERVER_
#include "extensions/Print.h"
#undef  _XP_PRINT_SERVER_
#include "Raster.h"

#include "attributes.h"
#include "AttrValid.h"

static void AllocateRasterPrivates(
    ScreenPtr pScreen);
static Bool RasterChangeWindowAttributes(
    WindowPtr pWin,
    unsigned long   mask);
static int StartJob(
    XpContextPtr pCon,
    Bool sendClientData);
static int StartPage(
    XpContextPtr pCon,
    WindowPtr pWin);
static int StartDoc(
    XpContextPtr pCon);
static int EndDoc(
    XpContextPtr pCon,
    Bool cancel);
static int EndJob(
    XpContextPtr pCon,
    Bool cancel);
static int EndPage(
    XpContextPtr pCon,
    WindowPtr pWin,
    Bool cancel);
static int DocumentData(
    XpContextPtr pCon,
    DrawablePtr pDraw,
    char *pData,
    int len_data,
    char *pDoc_fmt,
    int len_fmt,
    char *pOptions,
    int len_options,
    ClientPtr client);
static int GetDocumentData(
    XpContextPtr pContext,
    ClientPtr client,
    int maxBufferSize);
static void FreePageFiles(
    RasterContextPrivPtr pWinPriv);
static int SystemCmd(
    char *pCommand);
static Bool RasterCloseScreen(
    int index,
    ScreenPtr pScreen);
static int RasterInitContext(XpContextPtr pCon);
static Bool RasterDestroyContext(XpContextPtr pCon);
static char *RasterGetAttributes(
		XpContextPtr pContext,
		XPAttributes class);
static char *RasterGetOneAttribute(XpContextPtr pCon,
			   XPAttributes class, 
			   char *attribute);
static void RasterSetAttributes(XpContextPtr pCon,
			  XPAttributes class,
			  char *attributes);
static void RasterAugmentAttributes(XpContextPtr pCon,
			      XPAttributes class,
			      char *attributes);
static int RasterMediumDimensions(XpContextPtr pCon,
			      CARD16 *width,
			      CARD16 *height);
static int RasterReproducibleArea(XpContextPtr pCon,
			      xRectangle *pRect);

#define MAX(a,b) (((a) > (b)) ? (a) : (b))

extern Bool _XpBoolNoop();
extern void _XpVoidNoop();
extern void XpDestroyAttributes();
extern char *ReplaceFileString(
    char *string,
    char *inFileName,
    char *outFileName);
extern char *XpGetConfigDir();

extern XpValidatePoolsRec RasterValidatePoolsRec; /* From RasterAttVal.c */

static int RasterScreenPrivateIndex, RasterContextPrivateIndex;
static int RasterGeneration = 0;
static char RASTER_DRIV_NAME[] = "XP-RASTER";

Bool
InitializeRasterDriver(
     int ndx,
     ScreenPtr pScreen,
     int argc,
     char **argv)
{
    char specifier[MAX_TOKEN_LEN];
    int xRes, yRes, maxWidth, maxHeight;
    int maxRes, maxDim, numBytes;
    RasterScreenPrivPtr pPriv;
    XpDriverFuncsPtr pFuncs;
    char **printerNames, *printDescFile;
    int numPrinters;
    
    /*
     * Register this driver's InitContext function with the print extension.
     * This is a bit
     * sleazy, as the extension hasn't yet been initialized, but the
     * extension needs to know this, and this seems the best time to
     * provide the information.
     */
    XpRegisterInitFunc( pScreen, RASTER_DRIV_NAME, RasterInitContext );

    /*
     * Create and load the devPrivate for the printer layer.
     */
    AllocateRasterPrivates(pScreen);
   
    pPriv = (RasterScreenPrivPtr)
      pScreen->devPrivates[RasterScreenPrivateIndex].ptr;

    maxDim = MAX( pScreen->height, pScreen->width );
    numBytes = maxDim + BITMAP_SCANLINE_PAD - 1; /* pixels per row */
    numBytes *= maxDim;
    numBytes /=  8; /* bytes per row */
    xRes = pScreen->width / (pScreen->mmWidth / 25.4);
    yRes = pScreen->height / (pScreen->mmHeight / 25.4);
    maxRes = MAX( xRes, yRes );

    pPriv->pBits = (char *)xalloc(numBytes);

    /*
     * Have to allocate maxDim X maxDim to allow for landscape mode.
     */
    mfbScreenInit(pScreen, pPriv->pBits, maxDim, maxDim, maxRes,
		  maxRes, maxDim);
    pScreen->blackPixel = 1;
    pScreen->whitePixel = 0;
    if(mfbCreateDefColormap(pScreen) == FALSE)
	; /* XXX what do I do if it fails? */
    
    /*
    cfbScreenInit(pScreen, pPriv->pBits, maxWidth, maxHeight, maxXres,
		  maxYres, maxWidth);
    scalingScreenInit(pScreen);
    */

    pScreen->SaveScreen = _XpBoolNoop;
    pPriv->ChangeWindowAttributes = pScreen->ChangeWindowAttributes;
    pScreen->ChangeWindowAttributes = RasterChangeWindowAttributes;
    pPriv->CloseScreen = pScreen->CloseScreen;
    pScreen->CloseScreen = RasterCloseScreen;

    return TRUE;
}

/*
 * GetPropString searches the context's config database for a property
 * by the name of propName.  If found, it returns the property's
 * value, otherwise it returns NULL unless the requested attribute
 * is RASTER_PRINT_PAGE_COMMAND, in which case it returns a hard-coded
 * default string to invoke xpr to produce a PostScript(tm) formatted
 * raster.
 */

static char *
GetPropString(
     XpContextPtr pCon,
     char *propName)
{
    RasterContextPrivPtr pConPriv = (RasterContextPrivPtr)
      pCon->devPrivates[RasterContextPrivateIndex].ptr;
    char *type;
    XrmValue val;
    
    if( XrmGetResource(pConPriv->config, propName, propName, &type, &val) == 
       True )
        return (char *)val.addr;

    if( !strcmp( propName, RASTER_PRINT_PAGE_COMMAND ) )
      return "xpr -device ps %(InFile)% > %(OutFile)%";
    else
      return NULL;
}

static int
StartJob(
     XpContextPtr pCon,
     Bool sendClientData)
{
    RasterContextPrivPtr pConPriv = (RasterContextPrivPtr)
			 pCon->devPrivates[RasterContextPrivateIndex].ptr;
    char *jobHeader;

    /*
     * Check for existing page file, and delete it if it exists.
     */
    if(pConPriv->pageFileName != (char *)NULL)
    {
	if(pConPriv->pPageFile != (FILE *)NULL)
	{
	    fclose(pConPriv->pPageFile);
	    pConPriv->pPageFile = (FILE *)NULL;
	}
	unlink(pConPriv->pageFileName);
	Xfree(pConPriv->pageFileName);
	pConPriv->pageFileName = (char *)NULL;
    }

    /* 
     * Create a temporary file to store the printer output.
     */
    if(!sendClientData)
    {
	/* 
	 * Create a temporary file to store the printer output.
	 */
	if (!XpOpenTmpFile("w", &pConPriv->jobFileName, &pConPriv->pJobFile))
	    return BadAlloc;
    }

    return Success;
}

/*
 * StartDoc and EndDoc are just no-ops in this implementation, since
 * our view of the spooler really doesn't recognize documents.
 */

static int 
StartDoc(
     XpContextPtr pCon)
{
    return Success;
}

static int EndDoc(
     XpContextPtr pCon,
     Bool cancel)
{
    return Success;
}

/*
 * BuidArgVector takes a pointer to a comma-separated list of command
 * options and splits it out into an array of argument pointers.  The
 * caller must not free the optionList after calling this function until
 * the returned arg vector is no longer needed, at which time the arg
 * vector should also be freed.
 */

#define SEPARATOR_CHAR (char)','

static char **
BuildArgVector(
    char *optionList,
    char **argVector,
    int argCount)
{
    char *curArg, *lastChar, *endArg;
    int optionLen;

    curArg = optionList;
    lastChar = optionList + strlen(optionList); /* includes final NULL */

    while(curArg != (char *)NULL && curArg < lastChar)
    {
	/* strip leading white space */
	while(curArg < lastChar && isascii((int)*curArg) && 
	      isspace((int)*curArg))
	    curArg++;

	if(curArg < lastChar)
	{
	    argVector = (char **)Xrealloc(argVector, 
					  sizeof(char *) * (argCount + 2));
	    argVector[argCount] = curArg;
	    argVector[++argCount] = (char *)NULL;

	    endArg = strchr(curArg, SEPARATOR_CHAR);

	    /* Should I strip trailing white space ??? */

	    if(endArg != (char *)NULL)
	    {
	        *endArg = (char)'\0';
	        curArg = endArg + 1;
	    }
	    else
	        curArg = (char *)NULL;
	}
    }

    return argVector;
}

static int
EndJob(
     XpContextPtr pCon,
     Bool cancel)
{
    RasterContextPrivPtr pConPriv = (RasterContextPrivPtr)
			 pCon->devPrivates[RasterContextPrivateIndex].ptr;

    if( cancel == True )
    {
        if(pConPriv->getDocClient != (ClientPtr)NULL) {
	    XpFinishDocData(pConPriv->getDocClient);
	    
	    pConPriv->getDocClient == NULL;
	    pConPriv->getDocBufSize = 0;
	}
	    
	if(pConPriv->jobFileName != (char *)NULL)
	{
	    unlink(pConPriv->jobFileName);
	    Xfree(pConPriv->jobFileName);
	    pConPriv->jobFileName = (char *)NULL;
	}

        return Success;
    }

    if(pConPriv->getDocClient != (ClientPtr)NULL&&pConPriv->getDocBufSize > 0)
    {
        XpFinishDocData(pConPriv->getDocClient);
	    
	pConPriv->getDocClient == NULL;
	pConPriv->getDocBufSize = 0;

        return Success;
    }
    
    if(pConPriv->pJobFile != (FILE *)NULL)
    {
        fclose(pConPriv->pJobFile);
        pConPriv->pJobFile = (FILE *)NULL;
	
	if(pConPriv->jobFileName != (char *)NULL)
	{
	      XpSubmitJob( pConPriv->jobFileName, pCon );
	      unlink(pConPriv->jobFileName);
	      Xfree(pConPriv->jobFileName);
	      pConPriv->jobFileName = (char *)NULL;
	}
    }

    return Success;
}

/* StartPage 
 *
 * If page file exists
 *     close page file
 *     set page file pointer = NULL
 *     unlink page file
 */
static int
StartPage(
     XpContextPtr pCon,
     WindowPtr pWin)
{
    register WindowPtr pChild;
    RasterContextPrivPtr pConPriv = (RasterContextPrivPtr)
			 pCon->devPrivates[RasterContextPrivateIndex].ptr;
    unsigned short width, height;
    xEvent event;

    if(pConPriv->pPageFile != (FILE *)NULL)
    {
	fclose(pConPriv->pPageFile);
	pConPriv->pPageFile = (FILE *)NULL;
    }
    if(pConPriv->pageFileName != (char *)NULL)
    {
	unlink(pConPriv->pageFileName);
	pConPriv->pageFileName = (char *)NULL;
    }

    return Success;
}

#include "X11/XWDFile.h"


#define lowbit(x) ((x) & (~(x) + 1))

/*
 * Get the XWDColors of all pixels in colormap - returns # of colors
 */
static XWDColor *
Get_XWDColors(
     ColormapPtr pCmap)
{
    int i, ncolors;
    xrgb *prgbList;
    Pixel *pPixels;
    XWDColor *colors;

    ncolors = pCmap->pVisual->ColormapEntries;
    if (!(colors = (XWDColor *) malloc (sizeof(XWDColor) * ncolors)))
        return (XWDColor *) NULL;
    if (!(prgbList = (xrgb*) malloc(sizeof(xrgb) * ncolors)))
    {
	Xfree(colors);
        return (XWDColor *) NULL;
    }
    if (!(pPixels = (Pixel*) malloc(sizeof(Pixel) * ncolors)))
    {
	Xfree(colors);
	Xfree(prgbList);
        return (XWDColor *) NULL;
    }

    if (pCmap->pVisual->class == DirectColor ||
        pCmap->pVisual->class == TrueColor) {
        Pixel red, green, blue, red1, green1, blue1;

        red = green = blue = 0;
        red1 = lowbit(pCmap->pVisual->redMask);
        green1 = lowbit(pCmap->pVisual->greenMask);
        blue1 = lowbit(pCmap->pVisual->blueMask);
        for (i=0; i<ncolors; i++) {
          colors[i].pixel = red|green|blue;
          colors[i].pad = 0;
          red += red1;
          if (red > pCmap->pVisual->redMask)
            red = 0;
          green += green1;
          if (green > pCmap->pVisual->greenMask)
            green = 0;
          blue += blue1;
          if (blue > pCmap->pVisual->blueMask)
            blue = 0;
        }
    } else {
        for (i=0; i<ncolors; i++) {
          colors[i].pixel = i;
          colors[i].pad = 0;
        }
    }

    for(i = 0; i < ncolors; i++)
	pPixels[i] = colors[i].pixel;

    QueryColors(pCmap, ncolors, pPixels, prgbList);
    Xfree(pPixels);

    for(i = 0; i < ncolors; i++)
    {
	colors[i].red = prgbList[i].red;
	colors[i].green = prgbList[i].green;
	colors[i].blue = prgbList[i].blue;
    }
    Xfree(prgbList);

    return(colors);
}

static
_swapshort (
    register char *bp,
    register unsigned n)
{
    register char c;
    register char *ep = bp + n;

    while (bp < ep) {
        c = *bp;
        *bp = *(bp + 1);
        bp++;
        *bp++ = c;
    }
}

static
_swaplong (
    register char *bp,
    register unsigned n)
{
    register char c;
    register char *ep = bp + n;
    register char *sp;

    while (bp < ep) {
        sp = bp + 3;
        c = *sp;
        *sp = *bp;
        *bp++ = c;
        sp = bp + 1;
        c = *sp;
        *sp = *bp;
        *bp++ = c;
        bp += 2;
    }
}
static int
WriteWindowRaster(
    WindowPtr pWin,
    FILE *pRasterFile)
{
    long widthBytesLine, length;
    int nlines, linesPerBuf, height, linesDone;
    char *pBuf;
    DrawablePtr pDraw = &pWin->drawable;
    XWDFileHeader header;
    int win_name_size;
    int header_size;
    int ncolors, i;
    char *win_name;
    VisualPtr pVisual;
    ColormapPtr pCmap;
    XWDColor *pColors;
    unsigned long swaptest = 1;

    widthBytesLine = PixmapBytePad(pWin->drawable.width, pWin->drawable.depth);
    length = widthBytesLine * pWin->drawable.height;
    height = pWin->drawable.height;

    if(length <= 0)
        return Success;

    if (widthBytesLine >= IMAGE_BUFSIZE)
        linesPerBuf = 1;
    else
    {
        linesPerBuf = IMAGE_BUFSIZE / widthBytesLine;
        if (linesPerBuf > height)
            linesPerBuf = height;
    }
    length = linesPerBuf * widthBytesLine;
    if (linesPerBuf < height)
    {
        /* we have to make sure intermediate buffers don't need padding */
        while ((linesPerBuf > 1) && (length & 3))
        {
            linesPerBuf--;
            length -= widthBytesLine;
        }
        while (length & 3)
        {
            linesPerBuf++;
            length += widthBytesLine;
        }
    }
    if(!(pBuf = (char *) Xalloc(length)))
        return (BadAlloc);

    /*
     * Start of Xwd header code.
     */

    /*
     * XXX - Should we use the real window name???
     */
    win_name = "xwdump";
    /* sizeof(char) is included for the null string terminator. */
    win_name_size = strlen(win_name) + sizeof(char);
    
    pCmap = (ColormapPtr)LookupIDByType(wColormap (pWin), RT_COLORMAP);
    pVisual = pCmap->pVisual;
    if((pColors = Get_XWDColors(pCmap)) == (XWDColor *)NULL)
    {
	Xfree(pBuf);
	return (BadAlloc);
    }

    /*
     * Write out header information.
     */
    header_size = sizeof(header) + win_name_size;
    header.header_size = (CARD32) header_size;
    header.file_version = (CARD32) XWD_FILE_VERSION;
    header.pixmap_format = (CARD32) ZPixmap; /* Must match GetImage below */
    header.pixmap_depth = (CARD32) pDraw->depth;
    header.pixmap_width = (CARD32) pDraw->width;
    header.pixmap_height = (CARD32) pDraw->height;
    header.xoffset = (CARD32) 0;
    header.byte_order = (CARD32) screenInfo.imageByteOrder;
    header.bitmap_unit = (CARD32) screenInfo.bitmapScanlineUnit;
    header.bitmap_bit_order = (CARD32) screenInfo.bitmapBitOrder;
    header.bitmap_pad = (CARD32) screenInfo.bitmapScanlinePad;
    header.bits_per_pixel = (CARD32) pDraw->bitsPerPixel;
    header.bytes_per_line = (CARD32) widthBytesLine;
    header.visual_class = (CARD32) pVisual->class;
    header.red_mask = (CARD32) pVisual->redMask;
    header.green_mask = (CARD32) pVisual->greenMask;
    header.blue_mask = (CARD32) pVisual->blueMask;
    header.bits_per_rgb = (CARD32) pVisual->bitsPerRGBValue;
    header.colormap_entries = (CARD32) pVisual->ColormapEntries;
    header.ncolors = ncolors = (CARD32) pVisual->ColormapEntries;
    header.window_width = (CARD32) pDraw->width;
    header.window_height = (CARD32) pDraw->height;
    header.window_x = 0;
    header.window_y = 0;
    header.window_bdrwidth = (CARD32) 0;

    if (*(char *) &swaptest) {
        _swaplong((char *) &header, sizeof(header));
        for (i = 0; i < ncolors; i++) {
            _swaplong((char *) &pColors[i].pixel, sizeof(long));
            _swapshort((char *) &pColors[i].red, 3 * sizeof(short));
        }
    }

    (void) fwrite((char *)&header, sizeof(header), 1, pRasterFile);
    (void) fwrite(win_name, win_name_size, 1, pRasterFile);
    (void) fwrite((char *) pColors, sizeof(XWDColor), ncolors, pRasterFile);

    Xfree(pColors);

    /*
     * End of Xwd header code.
     */

    linesDone = 0;
    while(height - linesDone > 0)
    {
        nlines = min(linesPerBuf, height - linesDone);
        (*pDraw->pScreen->GetImage) (pDraw,
                                     0,
                                     linesDone,
                                     pWin->drawable.width,
                                     nlines,
                                     ZPixmap,
                                     ~0,
                                     pBuf);

        if(fwrite(pBuf, sizeof(char), (size_t)(nlines * widthBytesLine),
	   pRasterFile) != 
	   (size_t)(nlines * widthBytesLine))
	{
	    Xfree(pBuf);
	    return BadAlloc;
	}
        linesDone += nlines;
    }
    Xfree(pBuf);
    return Success;
}


static int
SendPage( XpContextPtr pCon )
{
    struct stat statBuf;
    RasterContextPrivPtr pConPriv = (RasterContextPrivPtr)
			 pCon->devPrivates[RasterContextPrivateIndex].ptr;

    if(stat(pConPriv->pageFileName, &statBuf) < 0)
        return BadAlloc;

    return XpSendDocumentData(pConPriv->getDocClient, 
		              pConPriv->pPageFile, (int)statBuf.st_size, 
		              pConPriv->getDocBufSize);
}

/*
 * EndPage:
 *
 * If page file doesn't exist:
 * {
 *     Create page file
 *     Open page file
 *     Write page header to page file
 *     if(preRasterFile exists)
 *         copy preRasterFile contents to page file
 *     if(noRasterFile exists)
 *         write noRasterFile contents to page file
 *     else
 *         Create raster image file
 *         Open raster image file
 *         GetImage data
 *         Write Image data to raster image file
 *         invoke page_command on raster image file
 *         Write raster image file contents to page file
 *         Unlink tempPage file
 *     if(postRasterFile exists)
 *         write postRasterFile contents to page file
 *     Write page trailer to page file
 * }
 * Write page file to job file
 */
static int
EndPage(
     XpContextPtr pCon,
     WindowPtr pWin,
     Bool cancel)
{
    RasterContextPrivPtr pConPriv = (RasterContextPrivPtr)
			 pCon->devPrivates[RasterContextPrivateIndex].ptr;
    struct stat statBuf;
    char *rasterFileName = (char *)NULL, *pCommand = (char *)NULL, 
	 *pHeader = (char *)NULL, *pTrailer = (char *)NULL;
    FILE *pRasterFile = (FILE *)NULL;

    if( cancel == True )
      return Success;
    
    if(pConPriv->pageFileName == (char *)NULL)
    {
	/*
	 * Open the page file.
	 */
	if (!XpOpenTmpFile("w+", &pConPriv->pageFileName,
			   &pConPriv->pPageFile))
	    goto BAD_PAGE_ALLOC;

	/*
	 * Copy any pre-raster document data to the page file.
	 */
	if(pConPriv->pPreRasterFile != (FILE *)NULL)
	{
	    if(CopyContentsAndDelete(&pConPriv->pPreRasterFile, 
			             &pConPriv->preRasterFileName,
			             pConPriv->pPageFile) == FALSE)
		goto BAD_PAGE_ALLOC;
	}

	/*
	 * Copy either the no-raster document data, or the raster 
	 * data itself to the page file.
	 * If the no-raster file exists, then we don't process the
	 * actual window raster bits.
	 */
	if(pConPriv->pNoRasterFile != (FILE *)NULL)
	{
	    if(CopyContentsAndDelete(&pConPriv->pNoRasterFile, 
			             &pConPriv->noRasterFileName,
			             pConPriv->pPageFile) == FALSE)
		goto BAD_PAGE_ALLOC;
	}
	else
	{
	    /*
	     * Open the raster image file.
	     */
	    if (!XpOpenTmpFile("w", &rasterFileName, &pRasterFile))
		goto BAD_PAGE_ALLOC;
    
	    /*
	     * Write the page image data to the raster image file.
	     */
	    if(WriteWindowRaster(pWin, pRasterFile) != Success)
	        goto BAD_PAGE_ALLOC;

	    /*
	     * Invoke the page_command on the raster image file.
	     */
	    if((pCommand = GetPropString(pCon, RASTER_PRINT_PAGE_COMMAND)) !=
	       (char *)NULL)
	    {
	        char *outFileName;
	        FILE *pOutFile;

		if (!XpOpenTmpFile("w", &outFileName, &pOutFile))
		    goto BAD_PAGE_ALLOC;
	        fclose(pOutFile);

	        pCommand = ReplaceFileString(strdup(pCommand), rasterFileName,
					     outFileName);
	        fclose(pRasterFile);
	        SystemCmd(pCommand);
		free(pCommand);
	        /*
	         * Delete the unprocessed raster file.
	         */
	        unlink(rasterFileName);
	        Xfree(rasterFileName);
	        rasterFileName = outFileName;
                if((pRasterFile = fopen(rasterFileName, "r")) == (FILE *)NULL)
	            goto BAD_PAGE_ALLOC;
	    }
	    else
	    {
	        fclose(pRasterFile);
                if((pRasterFile = fopen(rasterFileName, "r")) == (FILE *)NULL)
	            goto BAD_PAGE_ALLOC;
	    }

	    /*
	     * Copy the raster image file contents to the page file.
	     * Note that pRasterFile must be set to the start of the
	     * raster file.
	     */
	    if(CopyContentsAndDelete(&pRasterFile,
			             &rasterFileName,
			             pConPriv->pPageFile) == FALSE)
		goto BAD_PAGE_ALLOC;
	}

	/*
	 * Copy any post-raster document data to the page file.
	 */
	if(pConPriv->pPostRasterFile != (FILE *)NULL)
	{
	    if(CopyContentsAndDelete(&pConPriv->pPostRasterFile, 
			             &pConPriv->postRasterFileName,
			             pConPriv->pPageFile) == FALSE)
		goto BAD_PAGE_ALLOC;
	}

    }

    /*
     * Write the page file contents to the job file or to the client
     * performing GetDocumentData.
     * pConPriv->pPageFile must first be set to the start of the page file.
     */
    rewind(pConPriv->pPageFile);
    if(stat(pConPriv->pageFileName, &statBuf) < 0)
        goto BAD_PAGE_ALLOC;

    /*
     * Send the page data to whatever client has called GetDocumentData.
     */
    if(pConPriv->getDocClient != (ClientPtr)NULL&&pConPriv->getDocBufSize > 0)
    {
	int retval;
        /*
         * We should do something like the following: suspend the 
         * caller until we can gracefully write all the data in small
         * chunks to the receiver, but for now we'll just call WriteToClient
         * on the huge chunk
         */
	retval = SendPage(pCon);
        fclose(pConPriv->pPageFile);
        pConPriv->pPageFile = (FILE *)NULL;
        unlink(pConPriv->pageFileName);
        free(pConPriv->pageFileName);
        pConPriv->pageFileName = (char *)NULL;
	return retval;
    }

    if(pConPriv->pJobFile == (FILE *)NULL)
    {
	/*
	 * This shouldn't be necessary.  I believe we only get here if
	 * someone calls "EndPage" prior to "StartJob".  This error 
	 * condition should probably be trapped at a higher level.
	 */

	if(pConPriv->jobFileName != (char *)NULL)
	    Xfree(pConPriv->jobFileName);
        /*
         * Create a temporary file to store the printer output.
         */
	if (!XpOpenTmpFile("w", &pConPriv->jobFileName, &pConPriv->pJobFile))
	    goto BAD_PAGE_ALLOC;
    }

    if(TransferBytes(pConPriv->pPageFile, pConPriv->pJobFile, 
       (int)statBuf.st_size) != (int)statBuf.st_size)
        goto BAD_PAGE_ALLOC;

    fclose(pConPriv->pPageFile);
    pConPriv->pPageFile = (FILE *)NULL;
    unlink(pConPriv->pageFileName);
    free(pConPriv->pageFileName);
    pConPriv->pageFileName = (char *)NULL;

    return Success;

  BAD_PAGE_ALLOC:

    FreePageFiles(pConPriv);

    if(pRasterFile != (FILE *)NULL)
	fclose(pRasterFile);
    if(rasterFileName != (char *)NULL)
    {
	unlink(rasterFileName);
        Xfree(rasterFileName);
    }
    return BadAlloc;
}

static int
DocumentData(
     XpContextPtr pCon,
     DrawablePtr pDraw,
     char *pData,
     int len_data,
     char *pDoc_fmt,
     int len_fmt,
     char *pOptions,
     int len_options,
     ClientPtr client)
{
    RasterContextPrivPtr pConPriv = (RasterContextPrivPtr)
			 pCon->devPrivates[RasterContextPrivateIndex].ptr;
    char *preRasterStr = PRE_RASTER, *postRasterStr = POST_RASTER,
	 *noRasterStr = NO_RASTER;

    /*
     * Check that options equals either PRE_RASTER or POST_RASTER.
     */
    if(len_options == strlen(preRasterStr) &&
       strncmp(pOptions, preRasterStr, strlen(preRasterStr)) == 0)
    {
	if(pConPriv->pPreRasterFile == (FILE *)NULL)
	{
	    if (!XpOpenTmpFile("w+", &pConPriv->preRasterFileName,
			       &pConPriv->pPreRasterFile))
		return BadAlloc;
	}
	if(fwrite(pData, sizeof(char), (size_t)len_data,
	   pConPriv->pPreRasterFile) != (size_t)len_data)
	    return BadAlloc;
	fflush(pConPriv->pPreRasterFile);
    }
    else if(len_options == strlen(postRasterStr) &&
	    strncmp(pOptions, postRasterStr, strlen(postRasterStr)) == 0)
    {
	if(pConPriv->pPostRasterFile == (FILE *)NULL)
	{
	    if (!XpOpenTmpFile("w+", &pConPriv->postRasterFileName,
			       &pConPriv->pPostRasterFile))
		return BadAlloc;
	}
	if(fwrite(pData, sizeof(char), (size_t)len_data,
	   pConPriv->pPostRasterFile) != (size_t)len_data)
	    return BadAlloc;
	fflush(pConPriv->pPostRasterFile);
    }
    else if(len_options == strlen(noRasterStr) &&
	    strncmp(pOptions, noRasterStr, strlen(noRasterStr)) == 0)
    {
	if(pConPriv->pNoRasterFile == (FILE *)NULL)
	{
	    if (!XpOpenTmpFile("w+", &pConPriv->noRasterFileName,
			       &pConPriv->pNoRasterFile))
		return BadAlloc;
	}
	if(fwrite(pData, sizeof(char), (size_t)len_data,
	   pConPriv->pNoRasterFile) != (size_t)len_data)
	    return BadAlloc;
	fflush(pConPriv->pNoRasterFile);
    }
    else
	return BadValue;

    return Success;
}

/*
 * GetDocumentData notes which client is requesting the document data for
 * a particular context. The Raster driver's EndPage function causes the
 * data to be written to the proper client.
 */
static int
GetDocumentData(
    XpContextPtr pContext, 
    ClientPtr client,
    int maxBufferSize)
{
    RasterContextPrivPtr pConPriv = (RasterContextPrivPtr)
			 pContext->devPrivates[RasterContextPrivateIndex].ptr;

    pConPriv->getDocClient = client;
    pConPriv->getDocBufSize = maxBufferSize;
    return Success;
}

static void
AllocateRasterPrivates(
    ScreenPtr pScreen)
{
    if(RasterGeneration != serverGeneration)
    {
        RasterScreenPrivateIndex = AllocateScreenPrivateIndex();
	RasterContextPrivateIndex = XpAllocateContextPrivateIndex();
        XpAllocateContextPrivate( RasterContextPrivateIndex, 
			     sizeof( RasterContextPrivRec ) );

        RasterGeneration = serverGeneration;
    }
    pScreen->devPrivates[RasterScreenPrivateIndex].ptr = (pointer)Xalloc(
                sizeof(RasterScreenPrivRec));
}

/*
 * RasterChangeWindowAttributes - Make sure that the window's backing
 * store is turned on.
 */
static Bool 
RasterChangeWindowAttributes(
    WindowPtr pWin,
    unsigned long mask)
{
    Bool status = Success;
    ScreenPtr pScreen = pWin->drawable.pScreen;
    RasterScreenPrivPtr pScreenPriv = (RasterScreenPrivPtr) 
		     pScreen->devPrivates[RasterScreenPrivateIndex].ptr;

    if(pWin->backingStore == NotUseful)
    {
	pWin->backingStore = WhenMapped;
	mask |= CWBackingStore;
    }

    if(pScreenPriv->ChangeWindowAttributes != (Bool (*)())NULL)
    {
        pScreen->ChangeWindowAttributes = pScreenPriv->ChangeWindowAttributes;
        status = pScreen->ChangeWindowAttributes(pWin, mask);
        pScreen->ChangeWindowAttributes = RasterChangeWindowAttributes;
    }
    if(status != TRUE)
	return status;
}

/*
 * RasterValidateDocFormats - Inspects the files available in the 
 * ddx-config/XP-RASTER directory to find the names of PDLs for which
 * we have processing commands.  These names are then intersected with
 * the contents of the printer's document-formats-supported attribute,
 * and the result is stored back into document-formats-supported.  
 * We have hard-coded knowledge of how to produce PS, so we always 
 * leave that in, if it's listed in document-formats-supported, 
 * even if we don't have a configuration file.  If there is a 
 * configuration file for PS, then its contents will override our default.
 */
static void
RasterValidateDocFormats(
     XpContextPtr pCon)
{
}

/*
 * RasterValidateAttrs - Inspects and Corrects the attribute values
 * in the specified context.
 */
static void
RasterValidateAttrs(
     XpContextPtr pCon)
{
    RasterValidateDocFormats(pCon);
    XpValidatePrinterPool(pCon, &RasterValidatePoolsRec);
    XpValidateJobPool(pCon, &RasterValidatePoolsRec);
    XpValidateDocumentPool(pCon, &RasterValidatePoolsRec);
}
    
/*
 * RasterInitContext - Establish the appropriate values for a
 * PrintContext used with the Raster Driver.
 */
static char DOC_ATT_SUPP[]="document-attributes-supported:\tdefault-medium document-format";
static char JOB_ATT_SUPP[]="job-attributes-supported:\t";
static char DDX_DIR[]="ddx-config";

static int
RasterInitContext(
     XpContextPtr pCon)
{
    char *configFileName, *val, *attrStr;
    RasterContextPrivPtr pConPriv;
    XpDriverFuncsPtr pFuncs;
    
    /*
     * Initialize the attribute store for this printer.
     */
    XpInitAttributes( pCon );

    /*
     * Validate the attributes
     */
    RasterValidateAttrs( pCon );


    /*
     * Initialize the function pointers
     */
    pFuncs = &( pCon->funcs );
    pFuncs->StartJob = StartJob;
    pFuncs->EndJob = EndJob;
    pFuncs->StartDoc = StartDoc;
    pFuncs->EndDoc = EndDoc;
    pFuncs->StartPage = StartPage;
    pFuncs->EndPage = EndPage;
    pFuncs->PutDocumentData = DocumentData;
    pFuncs->GetDocumentData = GetDocumentData;
    pFuncs->DestroyContext = RasterDestroyContext;
    pFuncs->GetAttributes = (char *(*)())RasterGetAttributes;
    pFuncs->GetOneAttribute = (char *(*)())RasterGetOneAttribute;
    pFuncs->SetAttributes = (int(*)())RasterSetAttributes;
    pFuncs->AugmentAttributes = (int(*)())RasterAugmentAttributes;
    pFuncs->GetMediumDimensions = (int(*)())RasterMediumDimensions;
    pFuncs->GetReproducibleArea = (int(*)())RasterReproducibleArea;
    
    /*
     * Set up the context privates
     */
    pConPriv = (RasterContextPrivPtr)
      pCon->devPrivates[RasterContextPrivateIndex].ptr;
    
    pConPriv->jobFileName = (char *)NULL;
    pConPriv->pageFileName = (char *)NULL;
    pConPriv->preRasterFileName = (char *)NULL;
    pConPriv->postRasterFileName = (char *)NULL;
    pConPriv->noRasterFileName = (char *)NULL;
    pConPriv->pJobFile = (FILE *)NULL;
    pConPriv->pPageFile = (FILE *)NULL;
    pConPriv->pPreRasterFile = (FILE *)NULL;
    pConPriv->pPostRasterFile = (FILE *)NULL;
    pConPriv->pNoRasterFile = (FILE *)NULL;

    pConPriv->getDocClient = (ClientPtr)NULL;
    pConPriv->getDocBufSize = 0;

    /*
     * Get the configuration information for the context's printer
     */
    configFileName = XpGetOneAttribute( pCon, XPPrinterAttr,
				       "xp-ddx-config-file-name" );
    if(configFileName && strlen(configFileName))
    {
        if( configFileName[0] == '/' )
            pConPriv->config = XrmGetFileDatabase( configFileName );
        else
        {
	    char *configDir, *configFilePath;

	    configDir = XpGetConfigDir(FALSE);
            configFilePath = (char *)malloc((strlen(configDir) +
					     strlen(DDX_DIR) +
					     strlen(RASTER_DRIV_NAME) +
					     strlen(configFileName) +
					     4)* sizeof(char));
	    sprintf(configFilePath, "%s/%s/%s/%s", configDir, DDX_DIR,
		    RASTER_DRIV_NAME, configFileName);
	    pConPriv->config = XrmGetFileDatabase(configFilePath);
	    free(configDir);
	    free(configFilePath);
        }
    }
    else
	pConPriv->config = (XrmDatabase)NULL;

    /*
     * Add our own attribute initialization
     */
    /*
     * document-attributes-supported
     */
    val = XpGetOneAttribute(pCon, XPServerAttr, "document-attributes-supported");
    if((attrStr = (char *)xalloc(strlen(val) + strlen(DOC_ATT_SUPP) + 4)) == 
       (char *)NULL)
	return BadAlloc;
    sprintf(attrStr, "*%s %s", DOC_ATT_SUPP, val);
    XpAugmentAttributes(pCon, XPPrinterAttr, attrStr);
    xfree(attrStr);

    /*
     * job-attributes-supported
     */
    val = XpGetOneAttribute(pCon, XPServerAttr, "job-attributes-supported");
    if((attrStr = (char *)xalloc(strlen(val) + strlen(JOB_ATT_SUPP) + 4)) == 
       (char *)NULL)
	return BadAlloc;
    sprintf(attrStr, "*%s %s", JOB_ATT_SUPP, val);
    XpAugmentAttributes(pCon, XPPrinterAttr, attrStr);
    xfree(attrStr);

    /*
     * PageAttributesSupported
     */
    XpAugmentAttributes(pCon, XPPrinterAttr, "*xp-page-attributes-supported:");
    
    return Success;
}

    

static Bool
RasterDestroyContext(
     XpContextPtr pCon)
{
    RasterContextPrivPtr pConPriv = (RasterContextPrivPtr)
      pCon->devPrivates[RasterContextPrivateIndex].ptr;
    
    /*
     * Clean up the temporary files
     */
    FreePageFiles( pConPriv );
    
    if( pConPriv->pJobFile != (FILE *)NULL )
      {
	  fclose( pConPriv->pJobFile );
	  pConPriv->pJobFile = (FILE *)NULL;
      }
    if( pConPriv->jobFileName != (char *)NULL )
      {
	  unlink( pConPriv->jobFileName );
	  Xfree( pConPriv->jobFileName );
      }
    if(pConPriv->config)
    {
	XrmDestroyDatabase(pConPriv->config);
	pConPriv->config = (XrmDatabase)NULL;
    }

    XpDestroyAttributes( pCon );
    return Success;
}

static char *
RasterGetAttributes(
     XpContextPtr pContext,
     XPAttributes class)
{
    return XpGetAttributes( pContext, class );
}

static char *
RasterGetOneAttribute(
     XpContextPtr pContext,
     XPAttributes class,
     char *attr)
{
    return XpGetOneAttribute( pContext, class, attr );
}

static void 
RasterSetAttributes(XpContextPtr pCon,
    XPAttributes class,
    char *attributes)
{
    XpSetAttributes( pCon, class, attributes );
}

static void
RasterAugmentAttributes(
     XpContextPtr pCon,
     XPAttributes class,
     char *attributes)
{
    XpAugmentAttributes( pCon, class, attributes );
}

static void
FreePageFiles(
    RasterContextPrivPtr pConPriv)
{
    if(pConPriv->pPageFile != (FILE *)NULL)
    {
        fclose(pConPriv->pPageFile);
        pConPriv->pPageFile = (FILE *)NULL;
    }
    if(pConPriv->pageFileName != (char *)NULL)
    {
	unlink(pConPriv->pageFileName);
        Xfree(pConPriv->pageFileName);
        pConPriv->pageFileName = (char *)NULL;
    }
    if(pConPriv->pPreRasterFile != (FILE *)NULL)
    {
        fclose(pConPriv->pPreRasterFile);
        pConPriv->pPreRasterFile = (FILE *)NULL;
    }
    if(pConPriv->preRasterFileName != (char *)NULL)
    {
	unlink(pConPriv->preRasterFileName);
	Xfree(pConPriv->preRasterFileName);
	pConPriv->preRasterFileName = (char *)NULL;
    }
    if(pConPriv->pPostRasterFile != (FILE *)NULL)
    {
        fclose(pConPriv->pPostRasterFile);
        pConPriv->pPostRasterFile = (FILE *)NULL;
    }
    if(pConPriv->postRasterFileName != (char *)NULL)
    {
	unlink(pConPriv->postRasterFileName);
	Xfree(pConPriv->postRasterFileName);
	pConPriv->postRasterFileName = (char *)NULL;
    }
    if(pConPriv->pNoRasterFile != (FILE *)NULL)
    {
        fclose(pConPriv->pNoRasterFile);
        pConPriv->pNoRasterFile = (FILE *)NULL;
    }
    if(pConPriv->noRasterFileName != (char *)NULL)
    {
	unlink(pConPriv->noRasterFileName);
	Xfree(pConPriv->noRasterFileName);
	pConPriv->noRasterFileName = (char *)NULL;
    }
}

/*
 * RasterCloseScreen - Call any wrapped CloseScreen function,
 * and free the screen memory.
 */
static Bool 
RasterCloseScreen(
    int index,
    ScreenPtr pScreen)
{
    Bool status = Success;
    RasterScreenPrivPtr pScreenPriv = (RasterScreenPrivPtr) 
		     pScreen->devPrivates[RasterScreenPrivateIndex].ptr;
    
    /*
     * Call any wrapped CloseScreen proc.
     */
    if(pScreenPriv->CloseScreen != (Bool (*)())NULL)
    {
        pScreen->CloseScreen = pScreenPriv->CloseScreen;
        status = pScreen->CloseScreen(index, pScreen);
        pScreen->CloseScreen = RasterCloseScreen;
    }

    Xfree(pScreenPriv->pBits);
    Xfree(pScreenPriv);

    return status;
}

#include <signal.h>

/* ARGSUSED */
static void SigchldHndlr (int dummy)
{
    int   status, w;
    struct sigaction act;
    sigfillset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = SigchldHndlr;

    w = wait (&status);

    /*
     * Is this really necessary?
     */
    sigaction(SIGCHLD, &act, (struct sigaction *)NULL);
}

/*
 * SystemCmd provides a wrapper for the 'system' library call.  The call
 * appears to be sensitive to the handling of SIGCHLD, so this wrapper
 * sets the status to SIG_DFL, and then resets the established handler
 * after system returns.
 */
static int
SystemCmd(char *cmdStr)
{
    int status;
    struct sigaction newAct, oldAct;
    sigfillset(&newAct.sa_mask);
    newAct.sa_flags = 0;
    newAct.sa_handler = SIG_DFL;
    sigfillset(&oldAct.sa_mask);
    oldAct.sa_flags = 0;
    oldAct.sa_handler = SigchldHndlr;

    /*
     * get the old handler, and set the action to IGN
     */
    sigaction(SIGCHLD, &newAct, &oldAct);

    status = system (cmdStr);

    sigaction(SIGCHLD, &oldAct, (struct sigaction *)NULL);
    return status;
}

/*
 * RasterMediumDimensions is installed in the GetMediumDimensions field
 * of each raster-initialized context.
 */
static int
RasterMediumDimensions(XpContextPtr pCon, 
		       CARD16 *width,
		       CARD16 *height)
{
    XpGetMediumDimensions(pCon, width, height);
    return Success;
}

/*
 * RasterReproducibleArea is installed in the GetReproducibleArea field
 * of each raster-initialized context.
 */
static int 
RasterReproducibleArea(XpContextPtr pCon, 
		       xRectangle *pRect)
{
    XpGetReproductionArea(pCon, pRect);
    return Success;
}
