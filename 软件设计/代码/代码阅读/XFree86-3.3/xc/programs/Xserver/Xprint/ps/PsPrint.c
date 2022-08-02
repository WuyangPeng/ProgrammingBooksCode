/* $XConsortium: PsPrint.c /main/4 1996/12/30 16:38:45 kaleb $ */
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
**    *  File:		PsPrint.c
**    *
**    *  Contents:	Print extension code of Ps driver
**    *
**    *  Created By:	Roger Helmendach (Liberty Systems)
**    *
**    *  Copyright:	Copyright 1996 X Consortium, Inc.
**    *
**    *********************************************************
** 
********************************************************************/
/* $XFree86: xc/programs/Xserver/Xprint/ps/PsPrint.c,v 1.4 1996/12/31 07:06:32 dawes Exp $ */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <X11/Xprotostr.h>

#define NEED_EVENTS
#include "Xproto.h"
#undef NEED_EVENTS

#include "Ps.h"

#include "windowstr.h"
#include "attributes.h"
#include "Oid.h"

int
PsStartJob(
  XpContextPtr pCon,
  Bool         sendClientData,
  ClientPtr    client)
{
  PsContextPrivPtr  pConPriv = 
      (PsContextPrivPtr)pCon->devPrivates[PsContextPrivateIndex].ptr;
  char             *jobHeader;
  CARD16            width, height;
  char              s[20];

  /* 
   * Create a temporary file to store the printer output.
   */
  if (!XpOpenTmpFile("w", &pConPriv->jobFileName, &pConPriv->pJobFile))
      return BadAlloc;

/*
 * Write the job header to the job file.
 */

  pConPriv->pPsOut = PsOut_BeginFile(pConPriv->pJobFile);

  return Success;
}



/* I thought about making this following code into a set of routines
   or using a goto, or something, but in the end decided not to,
   because the plain old listing here makes the logic clearer. */
int
PsEndJob(
  XpContextPtr pCon,
  Bool         cancel)
{
  int r;
  struct stat buffer;
  int error;

  PsContextPrivPtr priv =
    (PsContextPrivPtr)pCon->devPrivates[PsContextPrivateIndex].ptr;

  if (cancel == True) {
    if (priv->getDocClient != (ClientPtr) NULL) {
      (void) XpFinishDocData( priv->getDocClient );

      priv->getDocClient = NULL;
      priv->getDocBufSize = 0;
    }

    /* job is cancelled - do we really care if we're out of space? */
    (void) fclose(priv->pJobFile);
    priv->pJobFile = NULL;

    unlink(priv->jobFileName);
    xfree(priv->jobFileName);
    priv->jobFileName = (char *)NULL;

    return Success;
  }
    
  /*
   * Append any trailing information here
   */
  PsOut_EndFile(priv->pPsOut, 0);
  
  /* this is where we find out if we're out of space */
  error = (fclose(priv->pJobFile) == EOF);
  priv->pJobFile = NULL;

  /* status to the client if we have ran out of space on the disk or 
     some other resource problem with the temporary file... */
  if (error) {
    if (priv->getDocClient != (ClientPtr) NULL) {
      (void) XpFinishDocData( priv->getDocClient );

      priv->getDocClient = NULL;
      priv->getDocBufSize = 0;
    }

    unlink(priv->jobFileName);
    xfree(priv->jobFileName);
    priv->jobFileName = (char *)NULL;

    return BadAlloc;
  }
    
  /* we have finished without incident & no cancel */

  if (priv->getDocClient != NULL && priv->getDocBufSize > 0) {
    FILE *file;

    file = fopen(priv->jobFileName, "r");
    if (!file || (fstat(fileno(file), &buffer) < 0))
	r = BadAlloc;
    else
	r = XpSendDocumentData(priv->getDocClient, file, buffer.st_size,
			       priv->getDocBufSize);
    if (file)
	fclose(file);

    (void) XpFinishDocData(priv->getDocClient);

    priv->getDocClient = NULL;
    priv->getDocBufSize = 0;
  }
  else {
      XpSubmitJob(priv->jobFileName, pCon);

      r = Success;
  }

  unlink(priv->jobFileName);
  xfree(priv->jobFileName);
  priv->jobFileName = (char *)NULL;

  return r;
}

/* StartPage 
 */
int
PsStartPage(
  XpContextPtr pCon,
  WindowPtr    pWin)
{
  int                iorient, iplex, icount, ires;
  unsigned short     iwd, iht;
  char               *count;
  register WindowPtr pChild;
  PsContextPrivPtr   pConPriv =
     (PsContextPrivPtr)pCon->devPrivates[PsContextPrivateIndex].ptr;
  PsWindowPrivPtr    pWinPriv =
     (PsWindowPrivPtr)pWin->devPrivates[PsWindowPrivateIndex].ptr;
  char               s[80];
  xEvent event;
  XpOid              orient, plex;

/*
 * Put a pointer to the context in the window private structure
 */
  pWinPriv->validContext = 1;
  pWinPriv->context      = pCon;

 /*
  *  Get the orientation
  */
  orient = XpGetContentOrientation(pCon);
  switch (orient) {
  case xpoid_val_content_orientation_landscape:
      iorient = 1;
      break;
  case xpoid_val_content_orientation_reverse_portrait:
      iorient = 2;
      break;
  case xpoid_val_content_orientation_reverse_landscape:
      iorient = 3;
      break;
  case xpoid_val_content_orientation_portrait:
  default:
      iorient = 0;
      break;
  }

  /*
   *  Get the count
   */
  count = XpGetOneAttribute(pCon, XPDocAttr, "copy-count");
  if( count )
  {
      int ii = sscanf(count, "%d", &icount);
      if( ii!=1 ) icount = 1;
  }
  else icount = 1;

  /*
   *  Get the plex
   */
  plex = XpGetPlex(pCon);
  if (plex == xpoid_val_plex_duplex) iplex = 1;
  else if (plex == xpoid_val_plex_tumble) iplex = 2;
  else                                 iplex = 0;

  /*
   *  Get the resolution and media size
   */
  ires = XpGetResolution(pCon);
  XpGetMediumDimensions(pCon, &iwd, &iht);

  /*
   *  Start the page
   */
  PsOut_BeginPage(pConPriv->pPsOut, iorient, icount, iplex, ires,
		  (int)iwd, (int)iht);

  return Success;
}


/*
 * EndPage:
 *
 * Write page trailer to page file
 * Write page file to job file
 */
int
PsEndPage(
  XpContextPtr pCon,
  WindowPtr    pWin)
{
  PsWindowPrivPtr    pWinPriv =
     (PsWindowPrivPtr)pWin->devPrivates[PsWindowPrivateIndex].ptr;
  PsContextPrivPtr pConPriv =
    (PsContextPrivPtr)pCon->devPrivates[PsContextPrivateIndex].ptr;

  PsOut_EndPage(pConPriv->pPsOut);

  pWinPriv->validContext = 0;
  pWinPriv->context      = NULL;

  /* status to the client if we have ran out of space on the disk or 
     some other resource problem with the temporary file... */
/*  if (ferror(pConPriv->pJobFile)) return BadAlloc; */

  return Success;
}

/*
 * The PsStartDoc() and PsEndDoc() functions serve basically as NOOP
 * placeholders.  This driver doesn't deal with the notion of multiple
 * documents per page.
 */

int
PsStartDoc(XpContextPtr pCon)
{
  return Success;
}

int
PsEndDoc(
  XpContextPtr pCon,
  Bool         cancel)
{
  return Success;
}

/*
 * PsDocumentData()
 *
 * Hand any pre-generated PDL down to the spool files, formatting it
 * as necessary to fit the given window.
 */

int
PsDocumentData(
  XpContextPtr  pCon,
  DrawablePtr   pDraw,
  char         *pData,
  int           len_data,
  char         *pFmt,
  int		len_fmt,
  char         *pOpt,
  int		len_opt,
  ClientPtr	client)
{
    PsContextPrivPtr cPriv;
    PsOutPtr psOut;

    if (len_fmt != 12 || !strcmp(pFmt, "PostScript 2") || len_opt)
	return BadValue;
    cPriv = pCon->devPrivates[PsContextPrivateIndex].ptr;
    psOut = cPriv->pPsOut;

    if (pDraw)
	PsOut_BeginFrame(psOut, 0, 0, pDraw->x, pDraw->y,
			 pDraw->width, pDraw->height);
    PsOut_RawData(psOut, pData, len_data);
    if (pDraw)
	PsOut_EndFrame(psOut);

    return Success;
}

/*
 *
 * PsGetDocumentData()
 *
 * This function allows the driver to send the generated PS back to
 * the client.
 */

int
PsGetDocumentData(
  XpContextPtr pCon,
  ClientPtr    client,
  int          maxBufferSize)
{
  PsContextPrivPtr pPriv = (PsContextPrivPtr)
    pCon->devPrivates[PsContextPrivateIndex].ptr;

  pPriv->getDocClient = client;
  pPriv->getDocBufSize = maxBufferSize;

  return Success;
}

