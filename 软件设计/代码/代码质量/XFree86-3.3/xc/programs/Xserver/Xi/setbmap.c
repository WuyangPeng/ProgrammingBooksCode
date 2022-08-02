/* $XConsortium: setbmap.c,v 1.8 94/04/17 20:33:21 rws Exp $ */
/* $XFree86: xc/programs/Xserver/Xi/setbmap.c,v 3.0 1996/03/29 22:14:00 dawes Exp $ */

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
 * Request to change the button mapping of an extension device.
 *
 */

#define	 NEED_EVENTS
#define	 NEED_REPLIES
#define IsOn(ptr, bit) \
	(((BYTE *) (ptr))[(bit)>>3] & (1 << ((bit) & 7)))

#include "X.h"				/* for inputstr.h    */
#include "Xproto.h"			/* Request macro     */
#include "inputstr.h"			/* DeviceIntPtr	     */
#include "XI.h"
#include "XIproto.h"
#include "exevents.h"
#include "extnsionst.h"
#include "extinit.h"			/* LookupDeviceIntRec */
#include "exglobals.h"

#include "setbmap.h"

/***********************************************************************
 *
 * This procedure changes the button mapping.
 *
 */

int
SProcXSetDeviceButtonMapping(client)
    register ClientPtr client;
    {
    register char n;

    REQUEST(xSetDeviceButtonMappingReq);
    swaps(&stuff->length, n);
    return(ProcXSetDeviceButtonMapping(client));
    }

/***********************************************************************
 *
 * This procedure lists the input devices available to the server.
 *
 */

int
ProcXSetDeviceButtonMapping (client)
    register ClientPtr client;
    {
    int					ret;
    xSetDeviceButtonMappingReply	rep;
    DeviceIntPtr dev;

    REQUEST(xSetDeviceButtonMappingReq);
    REQUEST_AT_LEAST_SIZE(xSetDeviceButtonMappingReq);

    if (stuff->length != (sizeof(xSetDeviceButtonMappingReq) + 
	stuff->map_length + 3)>>2)
	{
	SendErrorToClient(client, IReqCode, X_SetDeviceButtonMapping, 0, 
		BadLength);
	return Success;
	}

    rep.repType = X_Reply;
    rep.RepType = X_SetDeviceButtonMapping;
    rep.length = 0;
    rep.sequenceNumber = client->sequence;
    rep.status = MappingSuccess;

    dev = LookupDeviceIntRec (stuff->deviceid);
    if (dev == NULL)
	{
	SendErrorToClient(client, IReqCode, X_SetDeviceButtonMapping, 0, 
		BadDevice);
	return Success;
	}

    ret = SetButtonMapping (client, dev, stuff->map_length, (BYTE *)&stuff[1]);

    if (ret == BadValue || ret == BadMatch)
	{
	SendErrorToClient(client, IReqCode, X_SetDeviceButtonMapping, 0, 
		ret);
	return Success;
	}
    else
	{
	rep.status = ret;
	WriteReplyToClient(client, sizeof(xSetDeviceButtonMappingReply), &rep);
	}

    if (ret != MappingBusy)
        SendDeviceMappingNotify(MappingPointer, 0, 0, dev);
    return Success;
    }

/***********************************************************************
 *
 * This procedure writes the reply for the XSetDeviceButtonMapping function,
 * if the client and server have a different byte ordering.
 *
 */

void
SRepXSetDeviceButtonMapping (client, size, rep)
    ClientPtr	client;
    int		size;
    xSetDeviceButtonMappingReply	*rep;
    {
    register char n;

    swaps(&rep->sequenceNumber, n);
    swapl(&rep->length, n);
    WriteToClient(client, size, (char *)rep);
    }
