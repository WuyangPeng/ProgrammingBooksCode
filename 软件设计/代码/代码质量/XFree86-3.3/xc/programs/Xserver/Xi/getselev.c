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

/* $XConsortium: getselev.c,v 1.12 94/04/17 20:33:13 rws Exp $ */
/* $XFree86: xc/programs/Xserver/Xi/getselev.c,v 3.2 1996/04/15 11:18:48 dawes Exp $ */

/***********************************************************************
 *
 * Extension function to get the current selected events for a given window.
 *
 */

#define	 NEED_EVENTS
#define	 NEED_REPLIES
#include "X.h"				/* for inputstr.h    */
#include "Xproto.h"			/* Request macro     */
#include "XI.h"
#include "XIproto.h"
#include "inputstr.h"			/* DeviceIntPtr	     */
#include "windowstr.h"			/* window struct     */
#include "extnsionst.h"
#include "extinit.h"			/* LookupDeviceIntRec */
#include "exglobals.h"
#include "swaprep.h"

#include "getprop.h"
#include "getselev.h"

/***********************************************************************
 *
 * This procedure gets the current selected extension events.
 *
 */

int
SProcXGetSelectedExtensionEvents(client)
    register ClientPtr client;
    {
    register char n;

    REQUEST(xGetSelectedExtensionEventsReq);
    swaps(&stuff->length, n);
    REQUEST_SIZE_MATCH(xGetSelectedExtensionEventsReq);
    swapl(&stuff->window, n);
    return(ProcXGetSelectedExtensionEvents(client));
    }

/***********************************************************************
 *
 * This procedure gets the current device select mask,
 * if the client and server have a different byte ordering.
 *
 */

int
ProcXGetSelectedExtensionEvents(client)
    register ClientPtr client;
    {
    int					i;
    int					total_length = 0;
    xGetSelectedExtensionEventsReply	rep;
    WindowPtr				pWin;
    XEventClass				*buf;
    XEventClass				*tclient;
    XEventClass				*aclient;
    OtherInputMasks			*pOthers;
    InputClientsPtr			others;

    REQUEST(xGetSelectedExtensionEventsReq);
    REQUEST_SIZE_MATCH(xGetSelectedExtensionEventsReq);

    rep.repType = X_Reply;
    rep.RepType = X_GetSelectedExtensionEvents;
    rep.length = 0;
    rep.sequenceNumber = client->sequence;
    rep.this_client_count = 0;
    rep.all_clients_count = 0;

    if (!(pWin = LookupWindow(stuff->window, client)))
        {
	SendErrorToClient(client, IReqCode, X_GetSelectedExtensionEvents, 0, 
		BadWindow);
	return Success;
        }

    if ((pOthers = wOtherInputMasks(pWin)) != 0)
	{
	for (others = pOthers->inputClients; others; others=others->next)
	    for (i=0; i<EMASKSIZE; i++)
		tclient = ClassFromMask (NULL, others->mask[i], i, 
		    &rep.all_clients_count, COUNT);

	for (others = pOthers->inputClients; others; others=others->next)
	    if (SameClient(others, client))
		{
		for (i=0; i<EMASKSIZE; i++)
		    tclient = ClassFromMask (NULL, others->mask[i], i, 
			&rep.this_client_count, COUNT);
		break;
		}

	total_length = (rep.all_clients_count + rep.this_client_count) * 
	    sizeof (XEventClass);
	rep.length = (total_length + 3) >> 2;
	buf = (XEventClass *) xalloc (total_length);

	tclient = buf;
	aclient = buf + rep.this_client_count;
	if (others)
	    for (i=0; i<EMASKSIZE; i++)
		tclient = ClassFromMask (tclient, others->mask[i], i, NULL, CREATE);

	for (others = pOthers->inputClients; others; others=others->next)
	    for (i=0; i<EMASKSIZE; i++)
		aclient = ClassFromMask (aclient, others->mask[i], i, NULL, CREATE);
	}

    WriteReplyToClient (client, sizeof(xGetSelectedExtensionEventsReply), &rep);

    if (total_length)
	{
	client->pSwapReplyFunc = (ReplySwapPtr) Swap32Write;
	WriteSwappedDataToClient( client, total_length, buf);
	xfree (buf);
	}
    return Success;
    }

/***********************************************************************
 *
 * This procedure writes the reply for the XGetSelectedExtensionEvents function,
 * if the client and server have a different byte ordering.
 *
 */

void
SRepXGetSelectedExtensionEvents (client, size, rep)
    ClientPtr	client;
    int		size;
    xGetSelectedExtensionEventsReply	*rep;
    {
    register char n;

    swaps(&rep->sequenceNumber, n);
    swapl(&rep->length, n);
    swaps(&rep->this_client_count, n);
    swaps(&rep->all_clients_count, n);
    WriteToClient(client, size, (char *)rep);
    }
