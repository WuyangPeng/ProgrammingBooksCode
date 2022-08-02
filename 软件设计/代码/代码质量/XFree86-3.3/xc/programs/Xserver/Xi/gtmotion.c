/* $TOG: gtmotion.c /main/12 1997/04/04 09:10:45 barstow $ */ /*ALLOC-FIX*/




/* $XFree86: xc/programs/Xserver/Xi/gtmotion.c,v 3.2.4.1 1997/05/03 09:44:56 dawes Exp $ */

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

/***********************************************************************
 *
 * Request to get the motion history from an extension device.
 *
 */

#define	 NEED_EVENTS
#define	 NEED_REPLIES
#include "X.h"				/* for inputstr.h    */
#include "Xproto.h"			/* Request macro     */
#include "inputstr.h"			/* DeviceIntPtr	     */
#include "XI.h"
#include "XIproto.h"
#include "extnsionst.h"
#include "extinit.h"			/* LookupDeviceIntRec */
#include "exevents.h"
#include "exglobals.h"

#include "gtmotion.h"

/***********************************************************************
 *
 * Swap the request if server and client have different byte ordering.
 *
 */

int
SProcXGetDeviceMotionEvents(client)
register ClientPtr client;
    {
    register char n;

    REQUEST(xGetDeviceMotionEventsReq);
    swaps(&stuff->length, n);
    REQUEST_SIZE_MATCH(xGetDeviceMotionEventsReq);
    swapl(&stuff->start, n);
    swapl(&stuff->stop, n);
    return(ProcXGetDeviceMotionEvents(client));
    }

/****************************************************************************
 *
 * Get the motion history for an extension pointer devices.
 *
 */

int
ProcXGetDeviceMotionEvents(client)
    ClientPtr client;
{
    INT32 *coords = NULL, *bufptr;
    xGetDeviceMotionEventsReply rep;
    unsigned long i;
    int     num_events, axes, size, tsize;
    unsigned long nEvents;
    DeviceIntPtr dev;
    TimeStamp start, stop;
    int	length = 0;
    ValuatorClassPtr 	v;

    REQUEST(xGetDeviceMotionEventsReq);

    REQUEST_SIZE_MATCH(xGetDeviceMotionEventsReq);
    dev = LookupDeviceIntRec (stuff->deviceid);
    if (dev == NULL)
	{
	SendErrorToClient(client, IReqCode, X_GetDeviceMotionEvents, 0, 
	    BadDevice);
	return Success;
	}
    v = dev->valuator;
    if (v==NULL || v->numAxes == 0)
	{
	SendErrorToClient(client, IReqCode, X_GetDeviceMotionEvents, 0, 
	    BadMatch);
	return Success;
	}
    if (dev->valuator->motionHintWindow)
	MaybeStopDeviceHint(dev, client);
    axes = v->numAxes;
    rep.repType = X_Reply;
    rep.RepType = X_GetDeviceMotionEvents;
    rep.sequenceNumber = client->sequence;
    rep.nEvents = 0;
    rep.axes = axes;
    rep.mode = v->mode & DeviceMode;
    rep.length = 0;
    start = ClientTimeToServerTime(stuff->start);
    stop = ClientTimeToServerTime(stuff->stop);
    if (CompareTimeStamps(start, stop) == LATER ||
	CompareTimeStamps(start, currentTime) == LATER)
	{
    	WriteReplyToClient(client, sizeof(xGetDeviceMotionEventsReply), &rep);
        return Success;
	}
    if (CompareTimeStamps(stop, currentTime) == LATER)
        stop = currentTime;
    num_events = v->numMotionEvents;
    if (num_events)
    {
	size = sizeof(Time) + (axes * sizeof (INT32));
	tsize = num_events * size;
	coords = (INT32 *) ALLOCATE_LOCAL(tsize);
	if (!coords)
	    {
	    SendErrorToClient(client, IReqCode, X_GetDeviceMotionEvents, 0, 
	        BadAlloc);
	    return Success;
	    }
	rep.nEvents = (v->GetMotionProc) (
		dev, (xTimecoord *)coords, /* XXX */
		start.milliseconds, stop.milliseconds, (ScreenPtr)NULL);
    }
    if (rep.nEvents > 0)
	{
        length = (rep.nEvents * size +3) >> 2;
        rep.length = length;
	}
    nEvents = rep.nEvents;
    WriteReplyToClient(client, sizeof(xGetDeviceMotionEventsReply), &rep);
    if (nEvents)
        {
	if (client->swapped)
	    {
    	    register 	char n;

	    bufptr = coords;
	    for (i=0; i<nEvents * (axes+1); i++)
		{
    		swapl(bufptr, n);
		bufptr++;
		}
	    }
	WriteToClient(client, length * 4, (char *)coords);
        }
    if (coords)
	DEALLOCATE_LOCAL(coords);
    return Success;
}

/***********************************************************************
 *
 * This procedure writes the reply for the XGetDeviceMotionEvents function,
 * if the client and server have a different byte ordering.
 *
 */

void
SRepXGetDeviceMotionEvents (client, size, rep)
    ClientPtr	client;
    int		size;
    xGetDeviceMotionEventsReply	*rep;
    {
    register char n;

    swaps(&rep->sequenceNumber, n);
    swapl(&rep->length, n);
    swapl(&rep->nEvents, n);
    WriteToClient(client, size, (char *)rep);
    }
