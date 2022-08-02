/* $XConsortium: AllPlanes.c,v 11.18 94/04/17 20:18:32 rws Exp $ */
/*

Copyright (c) 1986  X Consortium

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

*/

#define NEED_REPLIES
#include "Xlibint.h"

Status XAllocColorPlanes(dpy, cmap, contig, pixels, ncolors, nreds, ngreens, 
                         nblues, rmask, gmask, bmask)
register Display *dpy;
Colormap cmap;
Bool contig;
unsigned long *pixels; /* LISTofCARD32 */ /* RETURN */
int ncolors;
int nreds, ngreens, nblues;
unsigned long *rmask, *gmask, *bmask; /* CARD32 */ /* RETURN */
{
    xAllocColorPlanesReply rep;
    Status status;
    register xAllocColorPlanesReq *req;

    LockDisplay(dpy);
    GetReq(AllocColorPlanes,req);

    req->cmap = cmap;
    req->colors = ncolors;
    req->red = nreds;
    req->green = ngreens;
    req->blue = nblues;
    req->contiguous = contig;

    status = _XReply(dpy, (xReply *)&rep, 0, xFalse);


    if (status) {
	*rmask = rep.redMask;
	*gmask = rep.greenMask;
	*bmask = rep.blueMask;

	/* sizeof(CARD32) = 4 */
	_XRead32 (dpy, (char *) pixels, (long)(ncolors * 4));
    }

    UnlockDisplay(dpy);
    SyncHandle();
    return(status);
}    
