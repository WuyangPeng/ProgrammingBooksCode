/* $XConsortium: roi.c,v 1.4 94/04/17 20:33:58 rws Exp $ */
/* $XFree86: xc/programs/Xserver/XIE/dixie/request/roi.c,v 3.0 1996/03/29 22:11:26 dawes Exp $ */
/**** module roi.c ****/
/****************************************************************************

Copyright (c) 1993, 1994  X Consortium

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


				NOTICE
                              
This software is being provided by AGE Logic, Inc. under the
following license.  By obtaining, using and/or copying this software,
you agree that you have read, understood, and will comply with these
terms and conditions:

     Permission to use, copy, modify, distribute and sell this
     software and its documentation for any purpose and without
     fee or royalty and to grant others any or all rights granted
     herein is hereby granted, provided that you agree to comply
     with the following copyright notice and statements, including
     the disclaimer, and that the same appears on all copies and
     derivative works of the software and documentation you make.
     
     "Copyright 1993, 1994 by AGE Logic, Inc."
     
     THIS SOFTWARE IS PROVIDED "AS IS".  AGE LOGIC MAKES NO
     REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.  By way of
     example, but not limitation, AGE LOGIC MAKE NO
     REPRESENTATIONS OR WARRANTIES OF MERCHANTABILITY OR FITNESS
     FOR ANY PARTICULAR PURPOSE OR THAT THE SOFTWARE DOES NOT
     INFRINGE THIRD-PARTY PROPRIETARY RIGHTS.  AGE LOGIC 
     SHALL BEAR NO LIABILITY FOR ANY USE OF THIS SOFTWARE.  IN NO
     EVENT SHALL EITHER PARTY BE LIABLE FOR ANY INDIRECT,
     INCIDENTAL, SPECIAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOSS
     OF PROFITS, REVENUE, DATA OR USE, INCURRED BY EITHER PARTY OR
     ANY THIRD PARTY, WHETHER IN AN ACTION IN CONTRACT OR TORT OR
     BASED ON A WARRANTY, EVEN IF AGE LOGIC LICENSEES
     HEREUNDER HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
     DAMAGES.
    
     The name of AGE Logic, Inc. may not be used in
     advertising or publicity pertaining to this software without
     specific, written prior permission from AGE Logic.

     Title to this software shall at all times remain with AGE
     Logic, Inc.
*****************************************************************************

	roi.c: Routines to manage region of interest protocol requests

	Dean Verheiden, AGE Logic, Inc., April 1993

****************************************************************************/

#define _XIEC_ROI

/*
 *  Include files
 */
#include <stdio.h>
/*
 *  Core X Includes
 */
#define NEED_EVENTS
#include <X.h>
#include <Xproto.h>
/*
 *  XIE Includes
 */
#include <XIE.h>
#include <XIEproto.h>
/*
 *  more X server includes.
 */
#include <misc.h>
#include <dixstruct.h>
/*
 *  Module Specific Includes
 */
#include <corex.h>
#include <macro.h>
#include <memory.h>
#include <roi.h>

/*
 *  Xie protocol proceedures called from the dispatcher
 */
int  ProcCreateROI();
int  ProcDestroyROI();
int  SProcCreateROI();
int  SProcDestroyROI();

/*
 *  routines referenced by other modules.
 */
int  DeleteROI();


/*------------------------------------------------------------------------
--------------------------- CreateROI Procedures -------------------------
------------------------------------------------------------------------*/
int ProcCreateROI(client)
 ClientPtr client;
{
  roiPtr roi;
  REQUEST(xieCreateROIReq);
  REQUEST_SIZE_MATCH(xieCreateROIReq);
  LEGAL_NEW_RESOURCE(stuff->roi, client);

  /* create a new lookup table
   */
  if( !(roi = (roiPtr) XieCalloc(sizeof(roiRec))) )
    return(client->errorValue = stuff->roi, BadAlloc);
  
  roi->ID	= stuff->roi;
  roi->refCnt  	= 1;
  ListInit(&roi->strips);

  return( AddResource(roi->ID, RT_ROI, (roiPtr)roi)
	? Success : (client->errorValue = stuff->roi, BadAlloc) );
}                               /* end ProcCreateROI */


/*------------------------------------------------------------------------
------------------------ DestroyROI Procedures --------------------------
------------------------------------------------------------------------*/
int ProcDestroyROI(client)
 ClientPtr client;
{
  roiPtr roi;
  REQUEST( xieDestroyROIReq );
  REQUEST_SIZE_MATCH( xieDestroyROIReq );

  if( !(roi = (roiPtr) LookupIDByType(stuff->roi, RT_ROI)) )
    return( SendResourceError(client, xieErrNoROI, stuff->roi) );
  
  /* Disassociate the ROI from core X -- it calls DeleteROI()
   */
  FreeResourceByType(stuff->roi, RT_ROI, RT_NONE);
  
  return(Success);
}                               /* end ProcDestroyROI */


/*------------------------------------------------------------------------
----------------------- deleteFunc: DeleteROI ---------------------------
------------------------------------------------------------------------*/
int DeleteROI(roi, id)
 roiPtr  roi;
 xieTypROI id;
{
  if( --roi->refCnt )
    return(Success);

  FreeStrips(&roi->strips);
  XieFree(roi);
  
  return(Success);
}                               /* end DeleteROI */

int SProcCreateROI(client)
ClientPtr client;
{
	register int n;
	REQUEST(xieCreateROIReq);
	swaps(&stuff->length, n);
	REQUEST_SIZE_MATCH(xieCreateROIReq);
	swapl(&stuff->roi,n);
	return (ProcCreateROI(client));
}                               /* end SProcCreateROI */

int SProcDestroyROI(client)
ClientPtr client;
{
	register int n;
	REQUEST( xieDestroyROIReq );
	swaps(&stuff->length, n);
	REQUEST_SIZE_MATCH( xieDestroyROIReq );
	swapl(&stuff->roi,n);
	return (ProcDestroyROI(client));
}                               /* end SProcDestroyROI */

/* end module ROI.c */
