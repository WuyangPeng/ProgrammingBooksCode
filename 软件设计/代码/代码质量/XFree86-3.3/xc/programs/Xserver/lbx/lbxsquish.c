/* $XConsortium: lbxsquish.c /main/5 1996/12/15 21:26:30 rws $ */
/*
 * Copyright 1994 Network Computing Devices, Inc.
 * Copyright 1996 X Consortium, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name Network Computing Devices, Inc. not be
 * used in advertising or publicity pertaining to distribution of this
 * software without specific, written prior permission.
 *
 * THIS SOFTWARE IS PROVIDED `AS-IS'.  NETWORK COMPUTING DEVICES, INC.,
 * DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING WITHOUT
 * LIMITATION ALL IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, OR NONINFRINGEMENT.  IN NO EVENT SHALL NETWORK
 * COMPUTING DEVICES, INC., BE LIABLE FOR ANY DAMAGES WHATSOEVER, INCLUDING
 * SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES, INCLUDING LOSS OF USE, DATA,
 * OR PROFITS, EVEN IF ADVISED OF THE POSSIBILITY THEREOF, AND REGARDLESS OF
 * WHETHER IN AN ACTION IN CONTRACT, TORT OR NEGLIGENCE, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */
#define NEED_REPLIES
#define NEED_EVENTS
#include "X.h"
#include "Xproto.h"
#include "Xos.h"
#include "misc.h"
#include "lbxserve.h"
#define _XLBX_SERVER_
#include "lbxstr.h"

/* handles server-side protocol squishing */

static char lbxevdelta[] = {
    0,
    0,
    sz_xEvent - lbxsz_KeyButtonEvent,
    sz_xEvent - lbxsz_KeyButtonEvent,
    sz_xEvent - lbxsz_KeyButtonEvent,
    sz_xEvent - lbxsz_KeyButtonEvent,
    sz_xEvent - lbxsz_KeyButtonEvent,   
    sz_xEvent - lbxsz_EnterLeaveEvent,
    sz_xEvent - lbxsz_EnterLeaveEvent,
    sz_xEvent - lbxsz_FocusEvent,
    sz_xEvent - lbxsz_FocusEvent,
    sz_xEvent - lbxsz_KeymapEvent,
    sz_xEvent - lbxsz_ExposeEvent,
    sz_xEvent - lbxsz_GfxExposeEvent,
    sz_xEvent - lbxsz_NoExposeEvent,
    sz_xEvent - lbxsz_VisibilityEvent,
    sz_xEvent - lbxsz_CreateNotifyEvent,
    sz_xEvent - lbxsz_DestroyNotifyEvent,
    sz_xEvent - lbxsz_UnmapNotifyEvent,
    sz_xEvent - lbxsz_MapNotifyEvent,
    sz_xEvent - lbxsz_MapRequestEvent,
    sz_xEvent - lbxsz_ReparentEvent,
    sz_xEvent - lbxsz_ConfigureNotifyEvent,
    sz_xEvent - lbxsz_ConfigureRequestEvent,
    sz_xEvent - lbxsz_GravityEvent,
    sz_xEvent - lbxsz_ResizeRequestEvent,
    sz_xEvent - lbxsz_CirculateEvent,
    sz_xEvent - lbxsz_CirculateEvent,
    sz_xEvent - lbxsz_PropertyEvent,
    sz_xEvent - lbxsz_SelectionClearEvent,
    sz_xEvent - lbxsz_SelectionRequestEvent,
    sz_xEvent - lbxsz_SelectionNotifyEvent,
    sz_xEvent - lbxsz_ColormapEvent,
    sz_xEvent - lbxsz_ClientMessageEvent,
    sz_xEvent - lbxsz_MappingNotifyEvent
};

static char lbxevpad[] = {
    0,
    0,
    lbxsz_KeyButtonEvent - lbxupsz_KeyButtonEvent,
    lbxsz_KeyButtonEvent - lbxupsz_KeyButtonEvent,
    lbxsz_KeyButtonEvent - lbxupsz_KeyButtonEvent,
    lbxsz_KeyButtonEvent - lbxupsz_KeyButtonEvent,
    lbxsz_KeyButtonEvent - lbxupsz_KeyButtonEvent,   
    lbxsz_EnterLeaveEvent - lbxupsz_EnterLeaveEvent,
    lbxsz_EnterLeaveEvent - lbxupsz_EnterLeaveEvent,
    lbxsz_FocusEvent - lbxupsz_FocusEvent,
    lbxsz_FocusEvent - lbxupsz_FocusEvent,
    lbxsz_KeymapEvent - lbxupsz_KeymapEvent,
    lbxsz_ExposeEvent - lbxupsz_ExposeEvent,
    lbxsz_GfxExposeEvent - lbxupsz_GfxExposeEvent,
    lbxsz_NoExposeEvent - lbxupsz_NoExposeEvent,
    lbxsz_VisibilityEvent - lbxupsz_VisibilityEvent,
    lbxsz_CreateNotifyEvent - lbxupsz_CreateNotifyEvent,
    lbxsz_DestroyNotifyEvent - lbxupsz_DestroyNotifyEvent,
    lbxsz_UnmapNotifyEvent - lbxupsz_UnmapNotifyEvent,
    lbxsz_MapNotifyEvent - lbxupsz_MapNotifyEvent,
    lbxsz_MapRequestEvent - lbxupsz_MapRequestEvent,
    lbxsz_ReparentEvent - lbxupsz_ReparentEvent,
    lbxsz_ConfigureNotifyEvent - lbxupsz_ConfigureNotifyEvent,
    lbxsz_ConfigureRequestEvent - lbxupsz_ConfigureRequestEvent,
    lbxsz_GravityEvent - lbxupsz_GravityEvent,
    lbxsz_ResizeRequestEvent - lbxupsz_ResizeRequestEvent,
    lbxsz_CirculateEvent - lbxupsz_CirculateEvent,
    lbxsz_CirculateEvent - lbxupsz_CirculateEvent,
    lbxsz_PropertyEvent - lbxupsz_PropertyEvent,
    lbxsz_SelectionClearEvent - lbxupsz_SelectionClearEvent,
    lbxsz_SelectionRequestEvent - lbxupsz_SelectionRequestEvent,
    lbxsz_SelectionNotifyEvent - lbxupsz_SelectionNotifyEvent,
    lbxsz_ColormapEvent - lbxupsz_ColormapEvent,
    lbxsz_ClientMessageEvent - lbxupsz_ClientMessageEvent,
    lbxsz_MappingNotifyEvent - lbxupsz_MappingNotifyEvent
};

int
LbxSquishEvent(buf)
    char *buf;
{
    int delta = lbxevdelta[((xEvent *)buf)->u.u.type];
    int pad = lbxevpad[((xEvent *)buf)->u.u.type];

    if (delta)
	memmove(buf + delta, buf, sz_xEvent - delta);
    if (pad) {
	buf += sz_xEvent;
	while (--pad >= 0)
	    *--buf = 0;
    }
    return delta;
}
