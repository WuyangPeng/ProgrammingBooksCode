/* $XConsortium: pcfrgb.c,v 1.4 94/04/17 20:33:41 rws Exp $ */
/* $XFree86: xc/programs/Xserver/XIE/dixie/process/pcfrgb.c,v 3.1 1996/08/20 12:21:38 dawes Exp $ */
/**** module pcfrgb.c ****/
/******************************************************************************

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
  
	pcfrgb.c -- DIXIE routines for managing the ConvertFromRGB element
  
	Dean Verheiden -- AGE Logic, Inc. August 1993
  
*****************************************************************************/

#define _XIEC_PCFRGB

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
   *  Server XIE Includes
   */
#include <corex.h>
#include <error.h>
#include <macro.h>
#include <element.h>
#include <technq.h>
#include <difloat.h>
#include <memory.h>

/*
 *  routines referenced by other modules
 */
peDefPtr	MakeConvertFromRGB();
Bool		CopyPConvertFromRGBCIE();
Bool		CopyPConvertFromRGBYCC();
Bool		CopyPConvertFromRGBYCbCr();
Bool		PrepPConvertFromRGBCIE();
Bool		PrepPConvertFromRGBYCC();
Bool		PrepPConvertFromRGBYCbCr();

/*
 * white adjust techniques, utilities, defined in ConvertToRGB
 */
extern Bool	CopyPWhiteAdjustNone();
extern Bool	CopyPWhiteAdjustCIELabShift();
extern Bool	PrepPWhiteAdjustNone();
extern Bool	PrepPWhiteAdjustCIELabShift();

extern void	copy_floats();
extern void	swap_floats();


/*
 *  routines internal to this module
 */
static Bool	PrepPConvertFromRGB();

/*
 * dixie element entry points
 */
static diElemVecRec pConvertFromRGBVec = {
  PrepPConvertFromRGB		/* prepare for analysis and execution	*/
  };

/*------------------------------------------------------------------------
------------------ routine: make a ConvertFromRBG element ----------------
------------------------------------------------------------------------*/
peDefPtr MakeConvertFromRGB(flo,tag,pe)
floDefPtr      flo;
xieTypPhototag tag;
xieFlo        *pe;
{
  peDefPtr ped;
  ELEMENT(xieFloConvertFromRGB);
  ELEMENT_AT_LEAST_SIZE(xieFloConvertFromRGB);
  ELEMENT_NEEDS_1_INPUT(src);
  
  if(!(ped = MakePEDef(1, (CARD32)stuff->elemLength<<2, 0)))
    FloAllocError(flo,tag,xieElemConvertFromRGB, return(NULL)) ;

  ped->diVec	     = &pConvertFromRGBVec;
  ped->phototag      = tag;
  ped->flags.process = TRUE;
  raw = (xieFloConvertFromRGB *)ped->elemRaw;
  /*
   * copy the client element parameters (swap if necessary)
   */
  if( flo->reqClient->swapped ) {
    raw->elemType   = stuff->elemType;
    raw->elemLength = stuff->elemLength;
    cpswaps(stuff->src,       raw->src);
    cpswaps(stuff->convert,   raw->convert);
    cpswaps(stuff->lenParams, raw->lenParams);
  } else
    memcpy((char *)raw, (char *)stuff, sizeof(xieFloConvertFromRGB));
  /*
   * copy technique data (if any)
   */
  if(!(ped->techVec = FindTechnique(xieValConvertFromRGB,  raw->convert)) ||
     !(ped->techVec->copyfnc(flo, ped, &stuff[1], &raw[1], raw->lenParams)))
    TechniqueError(flo,ped,xieValConvertFromRGB,raw->convert,raw->lenParams,
		   return(ped));

 /*
   * assign phototag to inFlo
   */
  ped->inFloLst[SRCtag].srcTag = raw->src;


  return(ped);
}                               /* end MakePConvertFromRGB */

/*------------------------------------------------------------------------
------ routine: copy routine for CIELab and CIEXYZ techniques  -----------
------------------------------------------------------------------------*/
Bool CopyPConvertFromRGBCIE(flo, ped, sparms, rparms, tsize) 
floDefPtr  flo;
peDefPtr   ped;
xieTecRGBToCIELab *sparms, *rparms; 	 /* same as xieTecRGBToCIEXYZ */
CARD16	tsize;
{
   pTecRGBToCIEDefPtr pvt;

   VALIDATE_TECHNIQUE_SIZE(ped->techVec, tsize, FALSE);

   if (!(ped->techPvt = (pointer )XieMalloc(sizeof(pTecRGBToCIEDefRec))))
	FloAllocError(flo, ped->phototag,xieElemConvertFromRGB, return(TRUE));

   pvt = (pTecRGBToCIEDefPtr)ped->techPvt;

   if( flo->reqClient->swapped ) {
	swap_floats(&pvt->matrix[0], &sparms->matrix00, 9);
	cpswaps(sparms->whiteAdjusted, pvt->whiteAdjusted);
	cpswaps(sparms->lenParams,     pvt->lenWhiteParams);
   } else {
	copy_floats(&pvt->matrix[0], &sparms->matrix00, 9);
        pvt->whiteAdjusted  = sparms->whiteAdjusted;
        pvt->lenWhiteParams = sparms->lenParams;
   }

   if(!(pvt->whiteTec = FindTechnique(xieValWhiteAdjust, pvt->whiteAdjusted)) ||
      !(pvt->whiteTec->copyfnc(flo, ped, &sparms[1], pvt->whitePoint, 
					 pvt->whiteTec, pvt->lenWhiteParams,
			                 pvt->whiteAdjusted == xieValDefault)))
       TechniqueError(flo,ped,xieValWhiteAdjust,pvt->whiteAdjusted,
		      pvt->lenWhiteParams, return(TRUE));

   return (TRUE);
}

/*------------------------------------------------------------------------
---------- routine: copy routine for YCbCr and YCC techniques ------------
------------------------------------------------------------------------*/
Bool CopyPConvertFromRGBYCbCr(flo, ped, sparms, rparms, tsize) 
floDefPtr  flo;
peDefPtr   ped;
xieTecRGBToYCbCr *sparms, *rparms;
CARD16	tsize;
{
   pTecRGBToYCbCrDefPtr pvt;

   VALIDATE_TECHNIQUE_SIZE(ped->techVec, tsize, FALSE);

   if (!(ped->techPvt = (pointer )XieMalloc(sizeof(pTecRGBToYCbCrDefRec))))
	FloAllocError(flo, ped->phototag,xieElemConvertFromRGB, return(TRUE));

   pvt = (pTecRGBToYCbCrDefPtr)ped->techPvt;

   if( flo->reqClient->swapped ) {
	cpswapl(sparms->levels0, pvt->levels0);
	cpswapl(sparms->levels1, pvt->levels1);
	cpswapl(sparms->levels2, pvt->levels2);
	swap_floats(&pvt->red, &sparms->lumaRed, 3);
	swap_floats(&pvt->bias0, &sparms->bias0, 3);
   } else {
	pvt->levels0 = sparms->levels0;
	pvt->levels1 = sparms->levels1;
	pvt->levels2 = sparms->levels2;
	copy_floats(&pvt->red, &sparms->lumaRed, 3);
	copy_floats(&pvt->bias0, &sparms->bias0, 3);
   }

   return (TRUE);
}

Bool CopyPConvertFromRGBYCC(flo, ped, sparms, rparms, tsize) 
floDefPtr  flo;
peDefPtr   ped;
xieTecRGBToYCC *sparms, *rparms;
CARD16	tsize;
{
   pTecRGBToYCCDefPtr pvt;

   VALIDATE_TECHNIQUE_SIZE(ped->techVec, tsize, FALSE);

   if (!(ped->techPvt = (pointer )XieMalloc(sizeof(pTecRGBToYCCDefRec))))
	FloAllocError(flo, ped->phototag,xieElemConvertFromRGB, return(TRUE));

   pvt = (pTecRGBToYCCDefPtr)ped->techPvt;

   if( flo->reqClient->swapped ) {
	cpswapl(sparms->levels0, pvt->levels0);
	cpswapl(sparms->levels1, pvt->levels1);
	cpswapl(sparms->levels2, pvt->levels2);
	swap_floats(&pvt->red, &sparms->lumaRed, 3);
	pvt->scale = ConvertFromIEEE(lswapl(sparms->scale));
   } else {
	pvt->levels0 = sparms->levels0;
	pvt->levels1 = sparms->levels1;
	pvt->levels2 = sparms->levels2;
	copy_floats(&pvt->red, &sparms->lumaRed, 3);
	pvt->scale = ConvertFromIEEE(sparms->scale);
   }

   return (TRUE);
}

/*------------------------------------------------------------------------
-- routine: prep routine for RGB to CIElab and CIEXYZ techniques ---------
------------------------------------------------------------------------*/

Bool PrepPConvertFromRGBCIE(flo, ped, raw, tec) 
floDefPtr  flo;
peDefPtr   ped;
xieFloConvertFromRGB *raw;
xieTecRGBToCIELab *tec;   /* same as xieTecRGBToCIEXYZ */
{
  inFloPtr inf = &ped->inFloLst[SRCtag];
  outFloPtr src = &inf->srcDef->outFlo;
  outFloPtr dst = &ped->outFlo;
  pTecRGBToCIEDefPtr pvt = (pTecRGBToCIEDefPtr)ped->techPvt;
  int b;

  /* grab a copy of the src attributes and propagate them to our input */
  dst->bands = inf->bands = src->bands;
  for(b = 0; b < src->bands; b++) {
	dst->format[b] = inf->format[b] = src->format[b];
	/* Now, fix up everthing in the destination that will change */
	/* For this element, src may have been CONSTRAINED */
	dst->format[b].class = UNCONSTRAINED;
	dst->format[b].depth = sz_RealPixel;
	dst->format[b].levels = 0;	/* Unconstrained */
	dst->format[b].stride = sz_RealPixel;
	dst->format[b].pitch = sz_RealPixel * dst->format[b].width;
  }

  return(pvt->whiteTec->prepfnc(flo,ped,pvt->whitePoint));
}

/*------------------------------------------------------------------------
-- routine: prep routine for RGB to YCbCr and YCC techniques -------------
------------------------------------------------------------------------*/
Bool PrepPConvertFromRGBYCbCr(flo, ped, raw, tec) 
floDefPtr  flo;
peDefPtr   ped;
xieFloConvertFromRGB *raw;
xieTecRGBToYCbCr *tec;
{
  inFloPtr inf = &ped->inFloLst[SRCtag];
  outFloPtr src = &inf->srcDef->outFlo;
  outFloPtr dst = &ped->outFlo;
  pTecRGBToYCbCrDefPtr pvt = (pTecRGBToYCbCrDefPtr)ped->techPvt;
  CARD32 *levels = &(pvt->levels0);
  int b;

  /* grab a copy of the src attributes and propagate them to our input */
  dst->bands = inf->bands = src->bands;
  for(b = 0; b < src->bands; b++) {
	dst->format[b] = inf->format[b] = src->format[b];
	if (IsConstrained(dst->format[b].class))
	    dst->format[b].levels = *(levels+b);
  }

  if (IsConstrained(dst->format[0].class)) {
      if (UpdateFormatfromLevels(ped) == FALSE)
	MatchError(flo,ped, return(FALSE));
  } /* else the structure copy was sufficient */

  return(TRUE);
}

Bool PrepPConvertFromRGBYCC(flo, ped, raw, tec) 
floDefPtr  flo;
peDefPtr   ped;
xieFloConvertFromRGB *raw;
xieTecRGBToYCC *tec;
{
  inFloPtr inf = &ped->inFloLst[SRCtag];
  outFloPtr src = &inf->srcDef->outFlo;
  outFloPtr dst = &ped->outFlo;
  pTecRGBToYCCDefPtr pvt = (pTecRGBToYCCDefPtr)ped->techPvt;
  CARD32 *levels = &(pvt->levels0);
  int b;

  /* grab a copy of the src attributes and propagate them to our input */
  dst->bands = inf->bands = src->bands;
  for(b = 0; b < src->bands; b++) {
	dst->format[b] = inf->format[b] = src->format[b];
	if (IsConstrained(dst->format[b].class))
	    dst->format[b].levels = *(levels+b);
  }

  if (IsConstrained(dst->format[0].class)) {
      if (UpdateFormatfromLevels(ped) == FALSE)
	MatchError(flo,ped, return(FALSE));
  } /* else the structure copy was sufficient */

  if (pvt->scale < .001) { /* should be about 1.35 or 1.4 */
	ValueError(flo, ped, tec->scale, return(FALSE));
  }

  return(TRUE);
}

/*------------------------------------------------------------------------
---------------- routine: prepare for analysis and execution -------------
------------------------------------------------------------------------*/

static Bool PrepPConvertFromRGB(flo,ped)
     floDefPtr  flo;
     peDefPtr   ped;
{
  inFloPtr inf = &ped->inFloLst[SRCtag];
  outFloPtr src = &inf->srcDef->outFlo;
  xieFloConvertFromRGB *raw = (xieFloConvertFromRGB *)ped->elemRaw;

  /* Input must be triple band and dimensions must match */
  if (IsntCanonic(src->format[0].class) ||
      src->bands != 3 ||
      src->format[0].width  != src->format[1].width ||
      src->format[1].width  != src->format[2].width ||
      src->format[0].height != src->format[1].height ||
      src->format[1].height != src->format[2].height)
      MatchError(flo,ped, return(FALSE));

  /*
  ** Technique Prep routine will complete the normal propagation of src
  ** attributes, and setup of destination attributes.
  */

  if (!(ped->techVec->prepfnc(flo, ped, raw, &raw[1])))
	TechniqueError(flo,ped,xieValConvertFromRGB,raw->convert,
		       raw->lenParams, return(FALSE));

  return (TRUE);
}	

/* end module pcfrgb.c */
