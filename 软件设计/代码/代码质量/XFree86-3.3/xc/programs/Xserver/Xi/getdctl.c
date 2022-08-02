/* $XConsortium: getdctl.c,v 1.4 94/04/17 20:33:09 rws Exp $ */
/* $XFree86: xc/programs/Xserver/Xi/getdctl.c,v 3.1 1996/03/29 22:13:17 dawes Exp $ */

/************************************************************

Copyright (c) 1989  X Consortium

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

Copyright (c) 1989 by Hewlett-Packard Company, Palo Alto, California.

			All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the name of Hewlett-Packard not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.

HEWLETT-PACKARD DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
HEWLETT-PACKARD BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

********************************************************/

/********************************************************************
 *
 *  Get Device control attributes for an extension device.
 *
 */

#define	 NEED_EVENTS			/* for inputstr.h    */
#define	 NEED_REPLIES
#include "X.h"				/* for inputstr.h    */
#include "Xproto.h"			/* Request macro     */
#include "inputstr.h"			/* DeviceIntPtr	     */
#include "XI.h"
#include "XIproto.h"
#include "extnsionst.h"
#include "extinit.h"			/* LookupDeviceIntRec */
#include "exglobals.h"

#include "getdctl.h"

/***********************************************************************
 *
 * This procedure gets the control attributes for an extension device,
 * for clients on machines with a different byte ordering than the server.
 *
 */

int
SProcXGetDeviceControl(client)
    register ClientPtr client;
    {
    register char n;

    REQUEST(xGetDeviceControlReq);
    swaps(&stuff->length, n);
    REQUEST_SIZE_MATCH(xGetDeviceControlReq);
    swaps(&stuff->control, n);
    return(ProcXGetDeviceControl(client));
    }

/***********************************************************************
 *
 * Get the state of the specified device control.
 *
 */

int
ProcXGetDeviceControl(client)
    ClientPtr client;
    {
    int	total_length = 0;
    char *buf, *savbuf;
    register DeviceIntPtr dev;
    xGetDeviceControlReply rep;

    REQUEST(xGetDeviceControlReq);
    REQUEST_SIZE_MATCH(xGetDeviceControlReq);

    dev = LookupDeviceIntRec (stuff->deviceid);
    if (dev == NULL)
	{
	SendErrorToClient (client, IReqCode, X_GetDeviceControl, 0, 
		BadDevice);
	return Success;
	}

    rep.repType = X_Reply;
    rep.RepType = X_GetDeviceControl;
    rep.length = 0;
    rep.sequenceNumber = client->sequence;

    switch (stuff->control)
	{
	case DEVICE_RESOLUTION:
	    if (!dev->valuator)
		{
		SendErrorToClient (client, IReqCode, X_GetDeviceControl, 0, 
		    BadMatch);
		return Success;
		}
	    total_length = sizeof (xDeviceResolutionState) +
		(3 * sizeof(int) * dev->valuator->numAxes);
	    break;
	default:
	    SendErrorToClient (client, IReqCode, X_GetDeviceControl, 0, 
		BadValue);
	    return Success;
	}

    buf = (char *) xalloc (total_length);
    if (!buf)
	{
	SendErrorToClient(client, IReqCode, X_GetDeviceControl, 0, 
		BadAlloc);
	return Success;
	}
    savbuf=buf;

    switch (stuff->control)
	{
	case DEVICE_RESOLUTION:
	    CopySwapDeviceResolution(client, dev->valuator, buf,
		total_length);
	    break;
	default:
	    break;
	}

    rep.length = (total_length+3) >> 2;
    WriteReplyToClient(client, sizeof(xGetDeviceControlReply), &rep);
    WriteToClient(client, total_length, savbuf);
    xfree (savbuf);
    return Success;
    }

/***********************************************************************
 *
 * This procedure copies DeviceResolution data, swapping if necessary.
 *
 */

void
CopySwapDeviceResolution (client, v, buf, length)
    ClientPtr 		client;
    ValuatorClassPtr	v;
    char 		*buf;
    int			length;
    {
    register char 	n;
    AxisInfoPtr	a;
    xDeviceResolutionState *r;
    int i, *iptr;

    r = (xDeviceResolutionState *) buf;
    r->control = DEVICE_RESOLUTION;
    r->length =  length;
    r->num_valuators =  v->numAxes;
    buf += sizeof (xDeviceResolutionState);
    iptr = (int *) buf;
    for (i=0,a=v->axes; i<v->numAxes; i++,a++)
	*iptr++ = a->resolution;
    for (i=0,a=v->axes; i<v->numAxes; i++,a++)
	*iptr++ = a->min_resolution;
    for (i=0,a=v->axes; i<v->numAxes; i++,a++)
	*iptr++ = a->max_resolution;
    if (client->swapped)
	{
	swaps (&r->control,n);
	swaps (&r->length,n);
	swapl (&r->num_valuators,n);
	iptr = (int *) buf;
	for (i=0; i < (3 * v->numAxes); i++,iptr++)
	    {
	    swapl (iptr,n);
	    }
	}
    }

/***********************************************************************
 *
 * This procedure writes the reply for the xGetDeviceControl function,
 * if the client and server have a different byte ordering.
 *
 */

void
SRepXGetDeviceControl (client, size, rep)
    ClientPtr	client;
    int		size;
    xGetDeviceControlReply	*rep;
    {
    register char n;

    swaps(&rep->sequenceNumber, n);
    swapl(&rep->length, n);
    WriteToClient(client, size, (char *)rep);
    }

