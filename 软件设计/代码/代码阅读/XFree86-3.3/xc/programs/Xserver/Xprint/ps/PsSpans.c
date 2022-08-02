/* $XConsortium: PsSpans.c /main/3 1996/12/30 14:58:09 kaleb $ */
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
**    *  File:		PsSpans.c
**    *
**    *  Contents:	Code to set and fill spans in the PS DDX
**    *
**    *  Created By:	Roger Helmendach (Liberty Systems)
**    *
**    *  Copyright:	Copyright 1996 X Consortium, Inc.
**    *
**    *********************************************************
** 
********************************************************************/
/* $XFree86: xc/programs/Xserver/Xprint/ps/PsSpans.c,v 1.3 1996/12/31 07:06:34 dawes Exp $ */

#include "Ps.h"
#include "gcstruct.h"
#include "windowstr.h"

void
PsFillSpans(
  DrawablePtr  pDrawable,
  GCPtr        pGC,
  int          nSpans,
  DDXPointPtr  pPoints,
  int         *pWidths,
  int          fSorted)
{
  char        t[80];
  PsOutPtr    psOut;
  int         xoffset, yoffset;
  xRectangle *rects, *r;
  RegionPtr   fillRegion, region;
  int         i;
  int         nbox;
  BoxPtr      pbox;
  ColormapPtr cMap;

  if( PsUpdateDrawableGC(pGC, pDrawable, &psOut, &cMap)==FALSE ) return;

  /*
   * Build a region out of the spans
   */
  rects   = (xRectangle *)xalloc(nSpans*sizeof(xRectangle));
  xoffset = pDrawable->x;
  yoffset = pDrawable->y;

  for( i = 0, r = rects; i < nSpans; i++, r++ )
  {
    r->x = pPoints[i].x + xoffset;
    r->y = pPoints[i].y + yoffset;
    r->width = pWidths[i];
    r->height = 1;
  }
  fillRegion = miRectsToRegion(nSpans, rects,
                               (fSorted)?CT_YSORTED:CT_UNSORTED);

  /*
   * Intersect this region with the clip region.  Whatever's left,
   * should be filled.
   */
/*miIntersect(region, fillRegion, pGC->clientClip);*/

  pbox = REGION_RECTS(region);
  nbox = REGION_NUM_RECTS(region);

  /* Enter HP-GL/2 */
  /*###SEND_PCL( outFile, "\27%0B" );*/

  while( nbox )
  {
/*###
    sprintf( t, "PU%d,%d;RR%d,%d;", pbox->x1, pbox->y1, pbox->x2, pbox->y2);
    SEND_PCL( outFile, t );
*/
    nbox--;
    pbox++;
  }

  /* Go back to PCL */
  /*###SEND_PCL( outFile, "\27%0A" );*/

  /*
   * Clean up the temporary regions
   */
  miRegionDestroy(fillRegion);
  miRegionDestroy(region);
  xfree(rects);
}

void
PsSetSpans(
  DrawablePtr  pDrawable,
  GCPtr        pGC,
  char        *pSrc,
  DDXPointPtr  pPoints,
  int         *pWidths,
  int          nSpans,
  int          fSorted)
{
}
