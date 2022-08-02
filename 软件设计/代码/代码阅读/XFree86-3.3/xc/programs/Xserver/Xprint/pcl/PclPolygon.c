/* $XConsortium: PclPolygon.c /main/2 1996/12/30 14:57:02 kaleb $ */
/*******************************************************************
**
**    *********************************************************
**    *
**    *  File:		PclPolygon.c
**    *
**    *  Contents:
**    *                 Draws Polygons and Rectangles for the PCL DDX
**    *
**    *  Created:	10/23/95
**    *
**    *********************************************************
** 
********************************************************************/
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
/* $XFree86: xc/programs/Xserver/Xprint/pcl/PclPolygon.c,v 1.3 1996/12/31 07:06:00 dawes Exp $ */


#include "Pcl.h"
#include "gcstruct.h"
#include "windowstr.h"

void
PclPolyRectangle( pDrawable, pGC, nRects, pRects )
     DrawablePtr pDrawable;
     GCPtr pGC;
     int nRects;
     xRectangle *pRects;
{
    char t[80];
    FILE *outFile;
    int nbox, i;
    BoxPtr pbox;
    xRectangle *drawRects, *r;
    RegionPtr drawRegion, region;
    short fudge;
    int xoffset, yoffset;
    XpContextPtr pCon;
    PclContextPrivPtr pConPriv;
    
    if( PclUpdateDrawableGC( pGC, pDrawable, &outFile ) == FALSE )
      return;

    pCon = PclGetContextFromWindow( (WindowPtr) pDrawable );
    pConPriv = (PclContextPrivPtr)
			pCon->devPrivates[PclContextPrivateIndex].ptr;
    
    /*
     * Allocate the storage required to deal with the clipping
     * regions. 
     */
    region = miRegionCreate( NULL, 0 );
    drawRects = (xRectangle *)xalloc( nRects * sizeof( xRectangle ) );
    
    fudge = 3 * pGC->lineWidth + 1;
    
    /*
     * Generate the PCL code to draw the rectangles, by defining them
     * as a macro which uses the HP-GL/2 rectangle drawing function.
     */
    MACRO_START( outFile, pConPriv );
    SAVE_PCL( outFile, pConPriv, "\033%0B" );

    xoffset = pDrawable->x;
    yoffset = pDrawable->y;
    
    for( i = 0, r = drawRects; i < nRects; i++, r++ )
      {
	  xRectangle rect = pRects[i];
	  
	  /* Draw the rectangle */
	  sprintf( t, "PU%d,%d;ER%d,%d;", rect.x + xoffset, 
		  rect.y + yoffset, rect.width, rect.height );
	  SAVE_PCL( outFile, pConPriv, t );

	  /* Build the bounding box */
	  r->x = MIN( rect.x, rect.x + rect.width ) + xoffset -
	    fudge;
	  r->y = MIN( rect.y, rect.y + rect.height ) + yoffset -
	    fudge;
	  r->width = rect.width + 2 * fudge;
	  r->height = rect.height + 2 * fudge;
      }
    SAVE_PCL( outFile, pConPriv, ";\033%0A" ); /* End the macro */
    MACRO_END( outFile );
    
    /*
     * Convert the collection of rectangles to a proper region, then
     * intersect it with the clip region.
     */
    drawRegion = miRectsToRegion( nRects, drawRects, CT_UNSORTED );

    miIntersect( region, drawRegion,
		((PclGCPrivPtr)pGC->devPrivates[PclGCPrivateIndex].ptr)
		->pCompositeClip );
    
    /*
     * For each rectangle in the clip region, set the HP-GL/2 "input
     * window" and render the set of rectangles to it.
     */
    pbox = REGION_RECTS( region );
    nbox = REGION_NUM_RECTS( region );
    
    PclSendData(outFile, pConPriv, pbox, nbox, 1.0);
    
    /*
     * Clean up the temporary regions
     */
    miRegionDestroy( drawRegion );
    miRegionDestroy( region );
    xfree( drawRects );
}

void
PclFillPolygon( pDrawable, pGC, shape, mode, nPoints, pPoints )
     DrawablePtr pDrawable;
     GCPtr pGC;
     int shape;
     int mode;
     int nPoints;
     DDXPointPtr pPoints;
{
    char t[80];
    FILE *outFile;
    int nbox, i;
    BoxPtr pbox;
    BoxRec box;
    xRectangle *drawRects, *r;
    RegionPtr drawRegion, region;
    int xoffset, yoffset;
    int xtop, xbottom, yleft, yright;
    int fillRule;
    XpContextPtr pCon;
    PclContextPrivPtr pConPriv;
    char *command;
    
    if( PclUpdateDrawableGC( pGC, pDrawable, &outFile ) == FALSE )
      return;

    pCon = PclGetContextFromWindow( (WindowPtr) pDrawable );
    pConPriv = (PclContextPrivPtr)
			pCon->devPrivates[PclContextPrivateIndex].ptr;
    
    /*
     * Generate the PCL code to draw the filled polygon, by defining
     * it as a macro which uses the HP-GL/2 polygon drawing function.
     */
    MACRO_START( outFile, pConPriv );
    SAVE_PCL( outFile, pConPriv, "\033%0B" );

    if( mode == CoordModeOrigin )
      {
	  xoffset = pDrawable->x;
	  yoffset = pDrawable->y;
	  command = "PA";
      }
    else
      {
	  xoffset = yoffset = 0;
	  command = "PR";
      }
    
    /* Begin the polygon */
    sprintf( t, "PU%d,%d;PM0;%s", pPoints[0].x + xoffset, pPoints[0].y
	    + yoffset, command );
    SAVE_PCL( outFile, pConPriv, t );

    /* Seed the bounding box */
    xtop = xbottom = pPoints[0].x + xoffset;
    yleft = yright = pPoints[0].y + yoffset;
    
    /* Add the rest of the points to the polygon */
    for( i = 1; i < nPoints; i++ )
      {
	  if( i != 1 )
	    SAVE_PCL( outFile, pConPriv, "," );
	  
	  sprintf( t, "%d,%d", pPoints[i].x + xoffset, pPoints[i].y +
		  yoffset );
	  SAVE_PCL( outFile, pConPriv, t );

	  /* Update the bounding box */
	  xtop = MIN( xtop, pPoints[i].x + xoffset );
	  xbottom = MAX( xbottom, pPoints[i].x + xoffset );
	  yleft = MIN( yleft, pPoints[i].y + yoffset );
	  yright = MAX( yright, pPoints[i].y + yoffset );
      }

    /* Close the polygon and the macro */

    if( pGC->fillRule == EvenOddRule )
      fillRule = 0;
    else
      fillRule = 1;
    
    sprintf( t, ";PM2;FP%d;\033%%0A", fillRule );
    SAVE_PCL( outFile, pConPriv, t );
    MACRO_END ( outFile );

    /*
     * Build the bounding region from the bounding box of the polygon
     */
    box.x1 = xtop;
    box.y1 = yleft;
    box.x2 = xbottom;
    box.y2 = yright;
    drawRegion = miRegionCreate( &box, 0 );

    if( mode == CoordModePrevious )
      miTranslateRegion( drawRegion, pPoints[0].x, pPoints[0].y );
    
    region = miRegionCreate( NULL, 0 );

    miIntersect( region, drawRegion,
		 ((PclGCPrivPtr)pGC->devPrivates[PclGCPrivateIndex].ptr)
		 ->pCompositeClip );

    /*
     * For each rectangle in the clip region, set the HP-GL/2 "input
     * window" and render the polygon to it.
     */
    pbox = REGION_RECTS( region );
    nbox = REGION_NUM_RECTS( region );
    
    PclSendData(outFile, pConPriv, pbox, nbox, 1.0);

    /*
     * Clean up the temporary regions
     */
    miRegionDestroy( drawRegion );
    miRegionDestroy( region );
}

void
PclPolyFillRect( pDrawable, pGC, nRects, pRects )
     DrawablePtr pDrawable;
     GCPtr pGC;
     int nRects;
     xRectangle *pRects;
{
    char t[80];
    FILE *outFile;
    int nbox, i;
    BoxPtr pbox;
    xRectangle *drawRects, *r;
    RegionPtr drawRegion, region;
    int xoffset, yoffset;
    short fudge;
    XpContextPtr pCon;
    PclContextPrivPtr pConPriv;
    
    if( PclUpdateDrawableGC( pGC, pDrawable, &outFile ) == FALSE )
      return;

    pCon = PclGetContextFromWindow( (WindowPtr) pDrawable );
    pConPriv = (PclContextPrivPtr)
			pCon->devPrivates[PclContextPrivateIndex].ptr;
    
    /*
     * Allocate the storage required to deal with the clipping
     * regions.
     */
    region = miRegionCreate( NULL, 0 );
    drawRects = (xRectangle *)xalloc( nRects * sizeof( xRectangle ) );


    fudge = 3 * pGC->lineWidth + 1;
    
    /*
     * Generate the PCL code to draw the filled rectangles, by
     * defining them as a macro which uses the HP-GL/2 rectangle
     * drawing function.
     */
    MACRO_START( outFile, pConPriv );
    SAVE_PCL( outFile, pConPriv, "\033%0B" );
    
    xoffset = pDrawable->x;
    yoffset = pDrawable->y;
    
    for( i = 0, r = drawRects; i < nRects; i++, r++ )
      {
	  xRectangle rect = pRects[i];
	  
	  /* Draw the rectangle */
	  sprintf( t, "PU%d,%d;RR%d,%d;", rect.x + xoffset, rect.y +
		  yoffset, rect.width, rect.height );
	  SAVE_PCL( outFile, pConPriv, t );
	  
	  /* Build the bounding box */
	  r->x = MIN( rect.x, rect.x + rect.width ) + xoffset - fudge;
	  r->y = MIN( rect.y, rect.y + rect.height ) + yoffset -
	    fudge;
	  r->width = rect.width + 2 * fudge;
	  r->height = rect.height + 2 * fudge;
      }
    SAVE_PCL( outFile, pConPriv, ";\033%0A" ); /* End the macro */
    MACRO_END( outFile );
    
    /*
     * Convert the collection of rectangles to a proper region, then
     * intersect it with the clip region.
     */
    drawRegion = miRectsToRegion( nRects, drawRects, CT_UNSORTED );
    miIntersect( region, drawRegion,
		((PclGCPrivPtr)pGC->devPrivates[PclGCPrivateIndex].ptr)
		->pCompositeClip );
    
    /*
     * For each rectangle in the clip region, set the HP-GL/2 "input
     * window" and render the set of rectangles to it.
     */
    pbox = REGION_RECTS( region );
    nbox = REGION_NUM_RECTS( region );
    
    PclSendData(outFile, pConPriv, pbox, nbox, 1.0);
    
    /*
     * Clean up the temporary regions
     */
    miRegionDestroy( drawRegion );
    miRegionDestroy( region );
    xfree( drawRects );
}

