/* $XConsortium: uOCprim.c,v 5.10 94/04/17 20:36:33 hersh Exp $ */

/***********************************************************

Copyright (c) 1989, 1990, 1991  X Consortium

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

Copyright 1989, 1990, 1991 by Sun Microsystems, Inc. 

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of Sun Microsystems,
not be used in advertising or publicity pertaining to distribution of 
the software without specific, written prior permission.  

SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT 
SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/


/*
	Contains swap routines for certain OCs and utility routines.
	The difference between this file and its companion cOCprim.c
	are subtle, having to do with, for example, whether or not
	you have to swap strmPtr->numPoints before or after you will
	need to use it to know how many points to convert.
 */

/*	All such packet interdependencies should be handled in these two 
	files: cOCprim.c and uOCprim.c
 */

#include "X.h"
#include "Xproto.h"
#include "misc.h"
#include "PEX.h"
#include "PEXproto.h"
#include "PEXprotost.h"
#include "dipex.h"
#include "pexSwap.h"
#include "pex_site.h"
#include "convertStr.h"

#define LOCAL_FLAG extern
#include "convUtil.h"
#include "OCattr.h"
#undef LOCAL_FLAG

#include "UconvName.h"
#define LOCAL_FLAG
#include "OCprim.h"

#ifndef PADDING
#define PADDING(n) ( (n)%4 ? (4 - (n)%4) : 0)
#endif 


unsigned char *
SWAP_FUNC_PREFIX(SwapFacet) (swapPtr, facetMask, vertexMask, colourType, ptr)
pexSwap	    *swapPtr;
CARD16		    facetMask;
CARD16		    vertexMask;
pexEnumTypeIndex    colourType;
CARD8		    *ptr;
{
    CARD32 numVerts;
    CARD32 i;

    ptr = SwapOptData (swapPtr, ptr, facetMask, colourType);

    numVerts = *((CARD32 *)ptr);
    SWAP_CARD32((*((CARD32 *)ptr)));
    ptr += sizeof(CARD32);

    for (i=0; i<numVerts; i++) 
	ptr = SwapVertex (swapPtr, (pexVertex *)ptr, vertexMask, colourType);
}



unsigned char *
SWAP_FUNC_PREFIX(SwapColourSpecifier) (swapPtr, pc)
pexSwap	    *swapPtr;
pexColourSpecifier  *pc;
{
    unsigned char *ptr;

    ptr = (unsigned char *)(pc+1);
    ptr = SwapColour (swapPtr,	(pexColour *)ptr, pc->colourType);
    SWAP_CARD16 (pc->colourType);
    return (ptr);
}


unsigned char *
SWAP_FUNC_PREFIX(SwapReflectionAttr) (swapPtr, ptr) 
pexSwap	    *swapPtr;
pexReflectionAttr   *ptr;
{
    unsigned char *pret = (unsigned char *)ptr;

    SWAP_FLOAT (ptr->ambient);
    SWAP_FLOAT (ptr->diffuse);
    SWAP_FLOAT (ptr->specular);
    SWAP_FLOAT (ptr->specularConc);
    SWAP_FLOAT (ptr->transmission); 
    pret = SWAP_FUNC_PREFIX(SwapColourSpecifier) (swapPtr, &(ptr->specularColour));
    return (pret);
}


void
SWAP_FUNC_PREFIX(SwapMonoEncoding) (swapPtr, pME, num)
pexSwap	*swapPtr;
pexMonoEncoding	*pME;
CARD32		num;
{
    CARD16 i, j;
    int bytes;

    for (i=0; i<num; i++) {
	SWAP_CARD16(pME->characterSet);
	switch (pME->characterSetWidth) {
	    case PEXCSByte: 
	  	bytes = pME->numChars;
	  	break;
	    case PEXCSShort: {
		CARD16 *ptr = (CARD16 *)(pME+1);
		for (j=0; j<pME->numChars; j++, ptr++) SWAP_CARD16((*ptr));
	  	bytes = pME->numChars * sizeof(CARD16);
	  	break;
	    }

	    case PEXCSLong: {
		CARD32 *ptr = (CARD32 *)(pME+1);
		for (j=0; j<pME->numChars; j++, ptr++) SWAP_CARD32((*ptr));
	  	bytes = pME->numChars * sizeof(CARD32);
	  	break;
	    }

	}
	
	SWAP_CARD16(pME->numChars);
	pME = (pexMonoEncoding *) ((char *) (pME + 1) +
	  bytes + PADDING (bytes));

    }
    
}


/*  The rest are OC's */

ErrorCode
SWAP_FUNC_PREFIX(PEXModelClipVolume) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexModelClipVolume	*strmPtr;
{
    int i;
    pexHalfSpace *ph;

    SWAP_ENUM_TYPE_INDEX (strmPtr->modelClipOperator);

    for (i=0, ph=(pexHalfSpace *)(strmPtr+1); i<strmPtr->numHalfSpaces; i++,ph++)
	SwapHalfSpace(swapPtr, ph);

    SWAP_CARD16 (strmPtr->numHalfSpaces);

}

ErrorCode
SWAP_FUNC_PREFIX(PEXModelClipVolume2D) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexModelClipVolume2D	*strmPtr;
{
    int i;
    pexHalfSpace2D *ph;

    SWAP_ENUM_TYPE_INDEX (strmPtr->modelClipOperator);

    for (i=0, ph=(pexHalfSpace2D *)(strmPtr+1); i<strmPtr->numHalfSpaces; i++,ph++)
	SwapHalfSpace2D(swapPtr, ph);

    SWAP_CARD16 (strmPtr->numHalfSpaces);
}


ErrorCode
SWAP_FUNC_PREFIX(PEXLightState) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexLightState	*strmPtr;
{
    int i, numE, numD;
    CARD16 *light;

    numE = strmPtr->numEnable; 
    numD = strmPtr->numDisable;

    SWAP_CARD16 (strmPtr->numEnable);
    SWAP_CARD16 (strmPtr->numDisable);

    for (i=0, light = (CARD16 *)(strmPtr+1); i<numE; i++, light++)
	SWAP_CARD16 ((*light));

    /* skip pad if there */
    if (numE & 0x1) light++;

    for (i=0; i<numD; i++, light++)
	SWAP_CARD16 ((*light));
}


ErrorCode
SWAP_FUNC_PREFIX(PEXAddToNameSet) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexAddToNameSet	*strmPtr;
{
    int i, num;
    pexName *pn;

    num = (int)(((sizeof (CARD32) * strmPtr->head.length) - sizeof(pexAddToNameSet))
	/sizeof(pexName));

    for (i=0, pn=(pexName *)(strmPtr+1); i<num; i++, pn++)
	SWAP_NAME ((*pn));

}


/* typedef pexAddToNameSet pexRemoveFromNameSet;*/

ErrorCode
SWAP_FUNC_PREFIX(PEXMarker) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexMarker	*strmPtr;
{
    CARD32 num;
    pexCoord3D *pc = (pexCoord3D *)(strmPtr+1);

    num = (CARD32)(((sizeof (CARD32) * strmPtr->head.length) - sizeof(pexMarker))
	/sizeof(pexCoord3D));

    SwapCoord3DList(swapPtr, pc, num);
}

ErrorCode
SWAP_FUNC_PREFIX(PEXMarker2D) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexMarker2D	*strmPtr;
{
    CARD32 num;
    pexCoord2D *pc = (pexCoord2D *)(strmPtr+1);

    num = (CARD32)(((sizeof (CARD32) * strmPtr->head.length) - sizeof(pexMarker2D))
	/sizeof(pexCoord2D));

    SwapCoord2DList(swapPtr, pc, num);

}


ErrorCode
SWAP_FUNC_PREFIX(PEXPolyline) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexPolyline	*strmPtr;
{
    CARD32 num;
    pexCoord3D *pc = (pexCoord3D *)(strmPtr+1);

    num = (CARD32)(((sizeof (CARD32) * strmPtr->head.length) - sizeof(pexPolyline))
	/sizeof(pexCoord3D));

    SwapCoord3DList(swapPtr, pc, num);

}

ErrorCode
SWAP_FUNC_PREFIX(PEXPolyline2D) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexPolyline2D	*strmPtr;
{
    CARD32 num;
    pexCoord2D *pc = (pexCoord2D *)(strmPtr+1);

    num = (CARD32)(((sizeof (CARD32) * strmPtr->head.length) - sizeof(pexPolyline2D))
	/sizeof(pexCoord2D));

    SwapCoord2DList(swapPtr, pc, num);

}

ErrorCode
SWAP_FUNC_PREFIX(PEXPolylineSet) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexPolylineSet	*strmPtr;
{
    unsigned long i, j, k;
    CARD32 *pj;
    pexVertex *pv;
    

    pj = (CARD32 *)(strmPtr+1);
    for (i=0; i<strmPtr->numLists; i++, pj = (CARD32 *)pv) {

	k = *pj;
	SWAP_CARD32 ((*pj));
	for (j=0, pv = (pexVertex *)(pj + 1); j<k; j++) {
	    pv = (pexVertex *) SwapVertex (swapPtr, pv, strmPtr->vertexAttribs, strmPtr->colourType);
	}

    }

    SWAP_COLOUR_TYPE (strmPtr->colourType);
    SWAP_CARD16 (strmPtr->vertexAttribs);
    SWAP_CARD32 (strmPtr->numLists);
}

ErrorCode
SWAP_FUNC_PREFIX(PEXNurbCurve) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexNurbCurve	*strmPtr;
{
    int i;
    PEXFLOAT *pf;

    SWAP_CARD16 (strmPtr->curveOrder);
    SWAP_COORD_TYPE (strmPtr->coordType);
    SWAP_FLOAT (strmPtr->tmin);
    SWAP_FLOAT (strmPtr->tmax);

    for (i=0, pf=(PEXFLOAT *)(strmPtr+1); i<strmPtr->numKnots; i++, pf++)
	SWAP_FLOAT((*pf));

    if (strmPtr->coordType == PEXRational) 
	SwapCoord4DList(swapPtr, (pexCoord4D *)pf, strmPtr->numPoints);
    else
	SwapCoord3DList(swapPtr, (pexCoord3D *)pf, strmPtr->numPoints);

    SWAP_CARD32 (strmPtr->numKnots);
    SWAP_CARD32 (strmPtr->numPoints);
}

ErrorCode
SWAP_FUNC_PREFIX(PEXFillArea) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexFillArea	*strmPtr;
{
    CARD32 num;

    num = (CARD32)(((sizeof (CARD32) * strmPtr->head.length) - sizeof(pexFillArea))
	/sizeof(pexCoord3D));

    SWAP_CARD16 (strmPtr->shape);

    SwapCoord3DList(swapPtr, (pexCoord3D *)(strmPtr+1), num);

}

ErrorCode
SWAP_FUNC_PREFIX(PEXFillArea2D) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexFillArea2D	*strmPtr;
{
    CARD32 num;

    num = (CARD32)(((sizeof (CARD32) * strmPtr->head.length) - sizeof(pexFillArea2D))
	    /sizeof(pexCoord2D));

    SWAP_CARD16 (strmPtr->shape);

    SwapCoord2DList(swapPtr, (strmPtr+1), num);


}

ErrorCode
SWAP_FUNC_PREFIX(PEXExtFillArea) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexExtFillArea	*strmPtr;
{

    SWAP_FUNC_PREFIX(SwapFacet)(    swapPtr, strmPtr->facetAttribs,
				    strmPtr->vertexAttribs, strmPtr->colourType,
				    (CARD8 *)(strmPtr+1));

    SWAP_CARD16 (strmPtr->shape);
    SWAP_COLOUR_TYPE (strmPtr->colourType);
    SWAP_CARD16 (strmPtr->facetAttribs);
    SWAP_CARD16 (strmPtr->vertexAttribs);
    /* SINGLE Facet(facetAttribs, vertexAttribs, colourType) */

}

ErrorCode
SWAP_FUNC_PREFIX(PEXFillAreaSet) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexFillAreaSet	*strmPtr;
{
    unsigned long i, j, k;
    CARD32 *pj;
    pexCoord3D *pc;

    pj = (CARD32 *)(strmPtr+1);

    for (i=0; i<strmPtr->numLists; i++, pj = (CARD32 *)pc ) {

	k = *pj;
	SWAP_CARD32 ((*pj));
	for (j=0, pc = (pexCoord3D *)(pj + 1); j<k; j++, pc++) {
	    SWAP_COORD3D ((*pc));
	}
    }

    SWAP_CARD16 (strmPtr->shape);
    SWAP_CARD32 (strmPtr->numLists);
}

ErrorCode
SWAP_FUNC_PREFIX(PEXFillAreaSet2D) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexFillAreaSet2D	*strmPtr;
{
    unsigned long i, j, k;
    CARD32 *pj;
    pexCoord2D *pc;

    pj = (CARD32 *)(strmPtr+1);

    for (i=0; i<strmPtr->numLists; i++, pj = (CARD32 *)pc ) {

	k = *pj;
	SWAP_CARD32 ((*pj));
	for (j=0, pc = (pexCoord2D *)(pj + 1); j<k; j++, pc++) {
	    SWAP_COORD2D ((*pc));
	}
    }

    SWAP_CARD16 (strmPtr->shape);
    SWAP_CARD32 (strmPtr->numLists);
}


ErrorCode
SWAP_FUNC_PREFIX(PEXExtFillAreaSet) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexExtFillAreaSet	*strmPtr;
{
    unsigned long i, j, k;
    CARD32 *pj;
    pexVertex *pv;
    unsigned char *ptr = 0;

    ptr = SwapOptData (swapPtr, (CARD8 *) (strmPtr+1),
		       strmPtr->facetAttribs, strmPtr->colourType);

    for (i=0, pj = (CARD32 *)ptr; i<strmPtr->numLists; i++, pj = (CARD32 *)pv) {
	k = *pj;
	SWAP_CARD32 ((*pj));
	for (j=0, pv = (pexVertex *)(pj + 1); j<k; j++) {
	    pv = (pexVertex *) SwapVertex(  swapPtr, pv, strmPtr->vertexAttribs,
					    strmPtr->colourType);
	}

    }

    SWAP_CARD16 (strmPtr->shape);
    SWAP_COLOUR_TYPE (strmPtr->colourType);
    SWAP_CARD16 (strmPtr->facetAttribs);
    SWAP_CARD16 (strmPtr->vertexAttribs);
    SWAP_CARD32 (strmPtr->numLists);
}


ErrorCode
SWAP_FUNC_PREFIX(PEXTriangleStrip) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexTriangleStrip	*strmPtr;
{
    CARD32 i;
    unsigned char *ptr = (unsigned char *)(strmPtr+1);


    for (i=0; i<(strmPtr->numVertices-2); i++)
	ptr = SwapOptData(  swapPtr, ptr, strmPtr->facetAttribs,
			    strmPtr->colourType);

    for (i=0; i<strmPtr->numVertices; i++)
	ptr = SwapVertex(   swapPtr, (pexVertex *)ptr, strmPtr->vertexAttribs,
			    strmPtr->colourType);

    SWAP_COLOUR_TYPE (strmPtr->colourType);
    SWAP_CARD16 (strmPtr->facetAttribs);
    SWAP_CARD16 (strmPtr->vertexAttribs);
    SWAP_CARD32 (strmPtr->numVertices);

}

ErrorCode
SWAP_FUNC_PREFIX(PEXQuadrilateralMesh) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexQuadrilateralMesh	*strmPtr;
{
    int i;
    unsigned char *ptr = (unsigned char *)(strmPtr+1);


    for (i=0; i<((strmPtr->mPts -1) * (strmPtr->nPts -1)); i++)
	ptr = SwapOptData(  swapPtr, ptr, strmPtr->facetAttribs,
			    strmPtr->colourType);

    for (i=0; i<(strmPtr->mPts * strmPtr->nPts); i++)
	ptr = SwapVertex(   swapPtr, (pexVertex *)ptr, strmPtr->vertexAttribs,
			    strmPtr->colourType);

    SWAP_COLOUR_TYPE (strmPtr->colourType);
    SWAP_CARD16 (strmPtr->mPts);
    SWAP_CARD16 (strmPtr->nPts);
    SWAP_CARD16 (strmPtr->facetAttribs);
    SWAP_CARD16 (strmPtr->vertexAttribs);

}


ErrorCode
SWAP_FUNC_PREFIX(PEXSOFAS) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexSOFAS	*strmPtr;
{
    CARD16 i, j, k;
    unsigned char *ptr = (unsigned char *)(strmPtr+1);
    CARD16 numList, numSubList;

    for (i=0; i<strmPtr->numFAS; i++)
	ptr = SwapOptData(  swapPtr, ptr, strmPtr->FAS_Attributes,
			    strmPtr->colourType);

    for (i=0; i<strmPtr->numVertices; i++)
	ptr = SwapVertex(   swapPtr, (pexVertex *)ptr, 
			    strmPtr->vertexAttributes, strmPtr->colourType);

    ptr += ((int)(((strmPtr->numEdges * strmPtr->edgeAttributes) + 3) / 4)) * 4;

    for (i=0; i < strmPtr->numFAS; i++){
	numList = *((CARD16 *)ptr);
	SWAP_CARD16((*ptr));
	ptr += sizeof (CARD16);
	for (j=0; j < numList; j++) {
	    numSubList = *((CARD16 *)ptr);
	    SWAP_CARD16((*ptr));
	    ptr += sizeof (CARD16);
	    for (k=0; k < numSubList; k++) {
		SWAP_CARD16((*ptr));
		ptr += sizeof (CARD16);
	    }
	}
    }
    SWAP_CARD16 (strmPtr->shape);
    SWAP_COLOUR_TYPE (strmPtr->colourType);
    SWAP_CARD16 (strmPtr->FAS_Attributes);
    SWAP_CARD16 (strmPtr->vertexAttributes);
    SWAP_CARD16 (strmPtr->edgeAttributes);
    SWAP_CARD16 (strmPtr->numFAS);
    SWAP_CARD16 (strmPtr->numVertices);
    SWAP_CARD16 (strmPtr->numEdges);
    SWAP_CARD16 (strmPtr->numContours);

}


ErrorCode
SWAP_FUNC_PREFIX(PEXNurbSurface) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexNurbSurface	*strmPtr;
{
    CARD32 i, j, k;
    PEXFLOAT *pf;
    unsigned char *ptr;
    CARD32 numPoints, numKnots;
    CARD32 numSublists;
    CARD16 curveType;
    pexTrimCurve *pTC = 0;


    for (i=0, pf=(PEXFLOAT *)(strmPtr+1); i<strmPtr->numUknots; i++, pf++)
	SWAP_FLOAT((*pf));

    for (i=0; i<strmPtr->numVknots; i++, pf++)
	SWAP_FLOAT((*pf));

    ptr = (unsigned char *)pf;
    if (strmPtr->type == PEXRational) 
	ptr = SwapCoord4DList(	swapPtr, (pexCoord4D *)ptr,
				(CARD32)(strmPtr->mPts*strmPtr->nPts));
    else 
	ptr = SwapCoord3DList(	swapPtr, (pexCoord3D *)ptr,
				(CARD32)(strmPtr->mPts*strmPtr->nPts));

    for (i=0; i<strmPtr->numLists; i++) {
	numSublists = *((CARD32 *)ptr);			/* num trim curves */
	SWAP_CARD32((*((CARD32 *)ptr)));
	ptr+=4;
	for (j=0; j<numSublists; j++) {
	    pTC = (pexTrimCurve *)ptr;
	    ptr = SwapTrimCurve(swapPtr, pTC); 
	    SWAP_CARD16(pTC->type);
	    SWAP_CARD32(pTC->numKnots);
	    SWAP_CARD32(pTC->numCoord);
	}
    }
    SWAP_COORD_TYPE (strmPtr->type);
    SWAP_CARD16 (strmPtr->uOrder);
    SWAP_CARD16 (strmPtr->vOrder);
    SWAP_CARD32 (strmPtr->numUknots);
    SWAP_CARD32 (strmPtr->numVknots);
    SWAP_CARD16 (strmPtr->mPts);
    SWAP_CARD16 (strmPtr->nPts);
    SWAP_CARD32 (strmPtr->numLists);
}



ErrorCode
SWAP_FUNC_PREFIX(PEXCellArray) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexCellArray	*strmPtr;
{
    int i;
    CARD16 *pc;

    SWAP_COORD3D (strmPtr->point1);
    SWAP_COORD3D (strmPtr->point2);
    SWAP_COORD3D (strmPtr->point3);

    for (i=0, pc=(CARD16 *)(strmPtr+1); i<(strmPtr->dx * strmPtr->dy); i++, pc++)
	SWAP_CARD16((*pc));

    SWAP_CARD32 (strmPtr->dx);
    SWAP_CARD32 (strmPtr->dy);
}

ErrorCode
SWAP_FUNC_PREFIX(PEXCellArray2D) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexCellArray2D	*strmPtr;
{
    int i;
    CARD16 *pc;

    SWAP_COORD2D (strmPtr->point1);
    SWAP_COORD2D (strmPtr->point2);

    for (i=0, pc=(CARD16 *)(strmPtr+1); i<(strmPtr->dx * strmPtr->dy); i++, pc++)
	SWAP_CARD16((*pc));

    SWAP_CARD32 (strmPtr->dx);
    SWAP_CARD32 (strmPtr->dy);
}

ErrorCode
SWAP_FUNC_PREFIX(PEXExtCellArray) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexExtCellArray	*strmPtr;
{
    CARD32 i;
    unsigned char *ptr;

    for (   i=0, ptr = (unsigned char *)(strmPtr+1);
	    i < strmPtr->dx * strmPtr->dy;
	    i++) {
	ptr = SwapColour(swapPtr, (pexColour *)ptr, strmPtr->colourType);
    }

    SWAP_COLOUR_TYPE (strmPtr->colourType);
    SWAP_COORD3D (strmPtr->point1);
    SWAP_COORD3D (strmPtr->point2);
    SWAP_COORD3D (strmPtr->point3);
    SWAP_CARD32 (strmPtr->dx);
    SWAP_CARD32 (strmPtr->dy);

}

ErrorCode
SWAP_FUNC_PREFIX(PEXGdp) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexGdp	*strmPtr;
{
    pexCoord3D *pc = (pexCoord3D *)(strmPtr+1);
    SWAP_CARD32 (strmPtr->gdpId);
    SWAP_CARD32 (strmPtr->numBytes);

    SwapCoord3DList(swapPtr, pc, strmPtr->numPoints);

    SWAP_CARD32 (strmPtr->numPoints);
}

ErrorCode
SWAP_FUNC_PREFIX(PEXGdp2D) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexGdp2D	*strmPtr;
{
    pexCoord2D *pc = (pexCoord2D *)(strmPtr+1);

    SWAP_CARD32 (strmPtr->gdpId);
    SWAP_CARD32 (strmPtr->numBytes);

    SwapCoord2DList(swapPtr, pc, strmPtr->numPoints);

    SWAP_CARD32 (strmPtr->numPoints);
}

ErrorCode
SWAP_FUNC_PEX_PFX(Text) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexText	*strmPtr;
{
    SWAP_COORD3D (strmPtr->origin);
    SWAP_VECTOR3D (strmPtr->vector1);
    SWAP_VECTOR3D (strmPtr->vector2);
    SWAP_FUNC_PREFIX(SwapMonoEncoding) (swapPtr, (pexMonoEncoding *)(strmPtr+1),
					(CARD32)(strmPtr->numEncodings));
    SWAP_CARD16 (strmPtr->numEncodings);
}

ErrorCode
SWAP_FUNC_PEX_PFX(Text2D) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexText2D	*strmPtr;
{
    SWAP_COORD2D (strmPtr->origin);
    SWAP_FUNC_PREFIX(SwapMonoEncoding) (swapPtr, (pexMonoEncoding *)(strmPtr+1),
					(CARD32)(strmPtr->numEncodings));
    SWAP_CARD16 (strmPtr->numEncodings);

}

ErrorCode
SWAP_FUNC_PEX_PFX(AnnotationText) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexAnnotationText	*strmPtr;
{
    SWAP_COORD3D (strmPtr->origin);
    SWAP_COORD3D (strmPtr->offset);
    SWAP_FUNC_PREFIX(SwapMonoEncoding) (swapPtr, (pexMonoEncoding *)(strmPtr+1),
					(CARD32)(strmPtr->numEncodings));
    SWAP_CARD16 (strmPtr->numEncodings);

}

ErrorCode
SWAP_FUNC_PEX_PFX(AnnotationText2D) (swapPtr, strmPtr)
pexSwap	*   swapPtr;
pexAnnotationText2D *strmPtr;
{
    SWAP_COORD2D (strmPtr->origin);
    SWAP_COORD2D (strmPtr->offset);
    SWAP_FUNC_PREFIX(SwapMonoEncoding) (swapPtr, (pexMonoEncoding *)(strmPtr+1),
					(CARD32)(strmPtr->numEncodings));
    SWAP_CARD16 (strmPtr->numEncodings);

}

ErrorCode
SWAP_FUNC_PEX_PFX(ParaSurfCharacteristics) (swapPtr, strmPtr)
pexSwap			    *swapPtr;
pexParaSurfCharacteristics *strmPtr;
{
    SWAP_CARD16 (strmPtr->length);

    switch (strmPtr->characteristics) {
	case PEXPSCNone:
	case PEXPSCImpDep:
	    break;

	case PEXPSCIsoCurves: {
	    pexPSC_IsoparametricCurves *ptr =
			    (pexPSC_IsoparametricCurves *)(strmPtr+1);
	    SWAP_CARD16(ptr->placementType);
	    SWAP_CARD16(ptr->numUcurves);
	    SWAP_CARD16(ptr->numVcurves);
	    break;
	}

	case PEXPSCMcLevelCurves:
	case PEXPSCWcLevelCurves: {
	    pexPSC_LevelCurves *ptr = (pexPSC_LevelCurves *)(strmPtr+1);
	    PEXFLOAT *pc = (PEXFLOAT *)(ptr+1);
	    CARD16 i;
	    SWAP_COORD3D (ptr->origin);
	    SWAP_VECTOR3D (ptr->direction);
	    for (i=0; i<ptr->numberIntersections; i++, pc++) {
		SWAP_FLOAT(*pc);
	    }
	    SWAP_CARD16 (ptr->numberIntersections);
	    break;
	}
    }

    SWAP_INT16 (strmPtr->characteristics);
}

ErrorCode
SWAP_FUNC_PREFIX(PEXNoop) (swapPtr, strmPtr)
pexSwap	*swapPtr;
pexNoop	*strmPtr;
{
}
