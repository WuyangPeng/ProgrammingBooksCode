/* $XConsortium: xkbSwap.c /main/9 1996/02/02 14:39:39 kaleb $ */
/* $XFree86: xc/programs/Xserver/xkb/xkbSwap.c,v 3.0 1996/08/25 14:14:04 dawes Exp $ */
/************************************************************
Copyright (c) 1993 by Silicon Graphics Computer Systems, Inc.

Permission to use, copy, modify, and distribute this
software and its documentation for any purpose and without
fee is hereby granted, provided that the above copyright
notice appear in all copies and that both that copyright
notice and this permission notice appear in supporting
documentation, and that the name of Silicon Graphics not be 
used in advertising or publicity pertaining to distribution 
of the software without specific prior written permission.
Silicon Graphics makes no representation about the suitability 
of this software for any purpose. It is provided "as is"
without any express or implied warranty.

SILICON GRAPHICS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS 
SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY 
AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL SILICON
GRAPHICS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, 
DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE 
OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
THE USE OR PERFORMANCE OF THIS SOFTWARE.

********************************************************/

#include "stdio.h"
#include "X.h"
#define	NEED_EVENTS
#define	NEED_REPLIES
#include "Xproto.h"
#include "misc.h"
#include "inputstr.h"
#include "XKBsrv.h"
#include "XKBstr.h"
#include "extnsionst.h"

#if NeedFunctionPrototypes
#define	PROC_EXTERN(pfunc)	extern int pfunc(ClientPtr)
#else
#define	PROC_EXTERN(pfunc)	extern int pfunc()
#endif

PROC_EXTERN(ProcXkbUseExtension);
PROC_EXTERN(ProcXkbSelectEvents);
PROC_EXTERN(ProcXkbBell);
PROC_EXTERN(ProcXkbGetState);
PROC_EXTERN(ProcXkbLatchLockState);
PROC_EXTERN(ProcXkbGetControls);
PROC_EXTERN(ProcXkbSetControls);
PROC_EXTERN(ProcXkbGetMap);
PROC_EXTERN(ProcXkbSetMap);
PROC_EXTERN(ProcXkbGetCompatMap);
PROC_EXTERN(ProcXkbSetCompatMap);
PROC_EXTERN(ProcXkbGetIndicatorState);
PROC_EXTERN(ProcXkbGetIndicatorMap);
PROC_EXTERN(ProcXkbSetIndicatorMap);
PROC_EXTERN(ProcXkbGetNamedIndicator);
PROC_EXTERN(ProcXkbSetNamedIndicator);
PROC_EXTERN(ProcXkbGetNames);
PROC_EXTERN(ProcXkbSetNames);
PROC_EXTERN(ProcXkbGetGeometry);
PROC_EXTERN(ProcXkbSetGeometry);
PROC_EXTERN(ProcXkbPerClientFlags);
PROC_EXTERN(ProcXkbListComponents);
PROC_EXTERN(ProcXkbGetKbdByName);
PROC_EXTERN(ProcXkbGetDeviceInfo);
PROC_EXTERN(ProcXkbSetDeviceInfo);
PROC_EXTERN(ProcXkbSetDebuggingFlags);

	/*
	 * REQUEST SWAPPING
	 */
static int
#if NeedFunctionPrototypes
SProcXkbUseExtension(ClientPtr client)
#else
SProcXkbUseExtension(client)
    ClientPtr client;
#endif
{
register int n;

    REQUEST(xkbUseExtensionReq);

    swaps(&stuff->length,n);
    REQUEST_SIZE_MATCH(xkbUseExtensionReq);
    swaps(&stuff->wantedMajor,n);
    swaps(&stuff->wantedMinor,n);
    return ProcXkbUseExtension(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbSelectEvents(ClientPtr client)
#else
SProcXkbSelectEvents(client)
    ClientPtr client;
#endif
{
register int n;

    REQUEST(xkbSelectEventsReq);

    swaps(&stuff->length,n);
    REQUEST_AT_LEAST_SIZE(xkbSelectEventsReq);
    swaps(&stuff->deviceSpec,n);
    swaps(&stuff->affectWhich,n);
    swaps(&stuff->clear,n);
    swaps(&stuff->selectAll,n);
    swaps(&stuff->affectMap,n);
    swaps(&stuff->map,n);
    if (stuff->affectWhich&(~XkbMapNotifyMask)!=0)  {
	union {
	    BOOL	*b;
	    CARD8	*c8;
	    CARD16	*c16;
	    CARD32	*c32;
	} from;
	register unsigned bit,ndx,maskLeft,dataLeft,size;

	from.c8= (CARD8 *)&stuff[1];
	dataLeft= (stuff->length*4)-SIZEOF(xkbSelectEventsReq);
	maskLeft= (stuff->affectWhich&(~XkbMapNotifyMask));
	for (ndx=0,bit=1; (maskLeft!=0); ndx++, bit<<=1) {
	    if (((bit&maskLeft)==0)||(ndx==XkbMapNotify))
		continue;
	    maskLeft&= ~bit;
	    if ((stuff->selectAll&bit)||(stuff->clear&bit))
		continue;
	    switch (ndx) {
		case XkbNewKeyboardNotify:
		case XkbStateNotify:
		case XkbNamesNotify:
		case XkbAccessXNotify:
		case XkbExtensionDeviceNotify:
		    size= 2;
		    break;
		case XkbControlsNotify:
		case XkbIndicatorStateNotify:
		case XkbIndicatorMapNotify:
		    size= 4;
		    break;
		case XkbBellNotify:
		case XkbActionMessage:
		case XkbCompatMapNotify:
		    size= 1;
		    break;
		default:
		    client->errorValue = _XkbErrCode2(0x1,bit);
		    return BadValue;
	    }
	    if (dataLeft<(size*2))
		return BadLength;
	    if (size==2) {
		swaps(&from.c16[0],n);
		swaps(&from.c16[1],n);
	    }
	    else if (size==4) {
		swapl(&from.c32[0],n);
		swapl(&from.c32[1],n);
	    }
	    else {
		size= 2;
	    }
	    from.c8+= (size*2);
	    dataLeft-= (size*2);
	}
	if (dataLeft>2) {
	    ErrorF("Extra data (%d bytes) after SelectEvents\n",dataLeft);
	    return BadLength;
	}
    }
    return ProcXkbSelectEvents(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbBell(ClientPtr client)
#else
SProcXkbBell(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbBellReq);

    swaps(&stuff->length,n);
    REQUEST_SIZE_MATCH(xkbBellReq);
    swaps(&stuff->deviceSpec,n);
    swaps(&stuff->bellClass,n);
    swaps(&stuff->bellID,n);
    swapl(&stuff->name,n);
    swapl(&stuff->window,n);
    swaps(&stuff->pitch,n);
    swaps(&stuff->duration,n);
    return ProcXkbBell(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbGetState(ClientPtr client)
#else
SProcXkbGetState(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbGetStateReq);

    swaps(&stuff->length,n);
    REQUEST_SIZE_MATCH(xkbGetStateReq);
    swaps(&stuff->deviceSpec,n);
    return ProcXkbGetState(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbLatchLockState(ClientPtr client)
#else
SProcXkbLatchLockState(client)
    ClientPtr client;
#endif
{
register int 	n;

    REQUEST(xkbLatchLockStateReq);

    swaps(&stuff->length,n);
    REQUEST_SIZE_MATCH(xkbLatchLockStateReq);
    swaps(&stuff->deviceSpec,n);
    swaps(&stuff->groupLatch,n);
    return ProcXkbLatchLockState(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbGetControls(ClientPtr client)
#else
SProcXkbGetControls(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbGetControlsReq);

    swaps(&stuff->length,n);
    REQUEST_SIZE_MATCH(xkbGetControlsReq);
    swaps(&stuff->deviceSpec,n);
    return ProcXkbGetControls(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbSetControls(ClientPtr client)
#else
SProcXkbSetControls(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbSetControlsReq);

    swaps(&stuff->length,n);
    REQUEST_SIZE_MATCH(xkbSetControlsReq);
    swaps(&stuff->deviceSpec,n);
    swaps(&stuff->affectInternalVMods,n);
    swaps(&stuff->internalVMods,n);
    swaps(&stuff->affectIgnoreLockVMods,n);
    swaps(&stuff->ignoreLockVMods,n);
    swaps(&stuff->axOptions,n);
    swapl(&stuff->affectEnabledCtrls,n);
    swapl(&stuff->enabledCtrls,n);
    swapl(&stuff->changeCtrls,n);
    swaps(&stuff->repeatDelay,n);
    swaps(&stuff->repeatInterval,n);
    swaps(&stuff->slowKeysDelay,n);
    swaps(&stuff->debounceDelay,n);
    swaps(&stuff->mkDelay,n);
    swaps(&stuff->mkInterval,n);
    swaps(&stuff->mkTimeToMax,n);
    swaps(&stuff->mkMaxSpeed,n);
    swaps(&stuff->mkCurve,n);
    swaps(&stuff->axTimeout,n);
    swapl(&stuff->axtCtrlsMask,n);
    swapl(&stuff->axtCtrlsValues,n);
    swaps(&stuff->axtOptsMask,n);
    swaps(&stuff->axtOptsValues,n);
    return ProcXkbSetControls(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbGetMap(ClientPtr client)
#else
SProcXkbGetMap(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbGetMapReq);

    swaps(&stuff->length,n);
    REQUEST_SIZE_MATCH(xkbGetMapReq);
    swaps(&stuff->deviceSpec,n);
    swaps(&stuff->full,n);
    swaps(&stuff->partial,n);
    swaps(&stuff->virtualMods,n);
    return ProcXkbGetMap(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbSetMap(ClientPtr client)
#else
SProcXkbSetMap(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbSetMapReq);

    swaps(&stuff->length,n);
    REQUEST_AT_LEAST_SIZE(xkbSetMapReq);
    swaps(&stuff->deviceSpec,n);
    swaps(&stuff->present,n);
    swaps(&stuff->flags,n);
    swaps(&stuff->totalSyms,n);
    swaps(&stuff->totalActs,n);
    swaps(&stuff->virtualMods,n);
    return ProcXkbSetMap(client);
}


static int
#if NeedFunctionPrototypes
SProcXkbGetCompatMap(ClientPtr client)
#else
SProcXkbGetCompatMap(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbGetCompatMapReq);

    swaps(&stuff->length,n);
    REQUEST_SIZE_MATCH(xkbGetCompatMapReq);
    swaps(&stuff->deviceSpec,n);
    swaps(&stuff->firstSI,n);
    swaps(&stuff->nSI,n);
    return ProcXkbGetCompatMap(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbSetCompatMap(ClientPtr client)
#else
SProcXkbSetCompatMap(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbSetCompatMapReq);

    swaps(&stuff->length,n);
    REQUEST_AT_LEAST_SIZE(xkbSetCompatMapReq);
    swaps(&stuff->deviceSpec,n);
    swaps(&stuff->firstSI,n);
    swaps(&stuff->nSI,n);
    return ProcXkbSetCompatMap(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbGetIndicatorState(ClientPtr client)
#else
SProcXkbGetIndicatorState(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbGetIndicatorStateReq);

    swaps(&stuff->length,n);
    REQUEST_SIZE_MATCH(xkbGetIndicatorStateReq);
    swaps(&stuff->deviceSpec,n);
    return ProcXkbGetIndicatorState(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbGetIndicatorMap(ClientPtr client)
#else
SProcXkbGetIndicatorMap(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbGetIndicatorMapReq);

    swaps(&stuff->length,n);
    REQUEST_SIZE_MATCH(xkbGetIndicatorMapReq);
    swaps(&stuff->deviceSpec,n);
    swapl(&stuff->which,n);
    return ProcXkbGetIndicatorMap(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbSetIndicatorMap(ClientPtr client)
#else
SProcXkbSetIndicatorMap(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbSetIndicatorMapReq);

    swaps(&stuff->length,n);
    REQUEST_AT_LEAST_SIZE(xkbSetIndicatorMapReq);
    swaps(&stuff->deviceSpec,n);
    swapl(&stuff->which,n);
    return ProcXkbSetIndicatorMap(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbGetNamedIndicator(ClientPtr client)
#else
SProcXkbGetNamedIndicator(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbGetNamedIndicatorReq);

    swaps(&stuff->length,n);
    REQUEST_SIZE_MATCH(xkbGetNamedIndicatorReq);
    swaps(&stuff->deviceSpec,n);
    swaps(&stuff->ledClass,n);
    swaps(&stuff->ledID,n);
    swapl(&stuff->indicator,n);
    return ProcXkbGetNamedIndicator(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbSetNamedIndicator(ClientPtr client)
#else
SProcXkbSetNamedIndicator(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbSetNamedIndicatorReq);

    swaps(&stuff->length,n);
    REQUEST_SIZE_MATCH(xkbSetNamedIndicatorReq);
    swaps(&stuff->deviceSpec,n);
    swaps(&stuff->ledClass,n);
    swaps(&stuff->ledID,n);
    swapl(&stuff->indicator,n);
    swaps(&stuff->virtualMods,n);
    swapl(&stuff->ctrls,n);
    return ProcXkbSetNamedIndicator(client);
}


static int
#if NeedFunctionPrototypes
SProcXkbGetNames(ClientPtr client)
#else
SProcXkbGetNames(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbGetNamesReq);

    swaps(&stuff->length,n);
    REQUEST_SIZE_MATCH(xkbGetNamesReq);
    swaps(&stuff->deviceSpec,n);
    swapl(&stuff->which,n);
    return ProcXkbGetNames(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbSetNames(ClientPtr client)
#else
SProcXkbSetNames(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbSetNamesReq);

    swaps(&stuff->length,n);
    REQUEST_AT_LEAST_SIZE(xkbSetNamesReq);
    swaps(&stuff->deviceSpec,n);
    swaps(&stuff->virtualMods,n);
    swapl(&stuff->which,n);
    swapl(&stuff->indicators,n);
    swaps(&stuff->totalKTLevelNames,n);
    return ProcXkbSetNames(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbGetGeometry(ClientPtr client)
#else
SProcXkbGetGeometry(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbGetGeometryReq);

    swaps(&stuff->length,n);
    REQUEST_SIZE_MATCH(xkbGetGeometryReq);
    swaps(&stuff->deviceSpec,n);
    swapl(&stuff->name,n);
    return ProcXkbGetGeometry(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbSetGeometry(ClientPtr client)
#else
SProcXkbSetGeometry(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbSetGeometryReq);

    swaps(&stuff->length,n);
    REQUEST_AT_LEAST_SIZE(xkbSetGeometryReq);
    swaps(&stuff->deviceSpec,n);
    swapl(&stuff->name,n);
    swaps(&stuff->widthMM,n);
    swaps(&stuff->heightMM,n);
    swaps(&stuff->nProperties,n);
    swaps(&stuff->nColors,n);
    swaps(&stuff->nDoodads,n);
    swaps(&stuff->nKeyAliases,n);
    return ProcXkbSetGeometry(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbPerClientFlags(ClientPtr client)
#else
SProcXkbPerClientFlags(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbPerClientFlagsReq);

    swaps(&stuff->length,n);
    REQUEST_SIZE_MATCH(xkbPerClientFlagsReq);
    swaps(&stuff->deviceSpec,n);
    swapl(&stuff->change,n);
    swapl(&stuff->value,n);
    swapl(&stuff->ctrlsToChange,n);
    swapl(&stuff->autoCtrls,n);
    swapl(&stuff->autoCtrlValues,n);
    return ProcXkbPerClientFlags(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbListComponents(ClientPtr client)
#else
SProcXkbListComponents(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbListComponentsReq);

    swaps(&stuff->length,n);
    REQUEST_AT_LEAST_SIZE(xkbListComponentsReq);
    swaps(&stuff->deviceSpec,n);
    swaps(&stuff->maxNames,n);
    return ProcXkbListComponents(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbGetKbdByName(ClientPtr client)
#else
SProcXkbGetKbdByName(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbGetKbdByNameReq);

    swaps(&stuff->length,n);
    REQUEST_AT_LEAST_SIZE(xkbGetKbdByNameReq);
    swaps(&stuff->deviceSpec,n);
    swaps(&stuff->want,n);
    swaps(&stuff->need,n);
    return ProcXkbGetKbdByName(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbGetDeviceInfo(ClientPtr client)
#else
SProcXkbGetDeviceInfo(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbGetDeviceInfoReq);

    swaps(&stuff->length,n);
    REQUEST_SIZE_MATCH(xkbGetDeviceInfoReq);
    swaps(&stuff->deviceSpec,n);
    swaps(&stuff->wanted,n);
    swaps(&stuff->ledClass,n);
    swaps(&stuff->ledID,n);
    return ProcXkbGetDeviceInfo(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbSetDeviceInfo(ClientPtr client)
#else
SProcXkbSetDeviceInfo(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbSetDeviceInfoReq);

    swaps(&stuff->length,n);
    REQUEST_AT_LEAST_SIZE(xkbSetDeviceInfoReq);
    swaps(&stuff->deviceSpec,n);
    swaps(&stuff->change,n);
    swaps(&stuff->nDeviceLedFBs,n);
    return ProcXkbSetDeviceInfo(client);
}

static int
#if NeedFunctionPrototypes
SProcXkbSetDebuggingFlags(ClientPtr client)
#else
SProcXkbSetDebuggingFlags(client)
    ClientPtr client;
#endif
{
register int	n;

    REQUEST(xkbSetDebuggingFlagsReq);

    swaps(&stuff->length,n);
    REQUEST_AT_LEAST_SIZE(xkbSetDebuggingFlagsReq);
    swapl(&stuff->affectFlags,n);
    swapl(&stuff->flags,n);
    swapl(&stuff->affectCtrls,n);
    swapl(&stuff->ctrls,n);
    swaps(&stuff->msgLength,n);
    return ProcXkbSetDebuggingFlags(client);
}

int
#if NeedFunctionPrototypes
SProcXkbDispatch (ClientPtr client)
#else
SProcXkbDispatch (client)
    ClientPtr client;
#endif
{
    REQUEST(xReq);
    switch (stuff->data)
    {
    case X_kbUseExtension:
	return SProcXkbUseExtension(client);
    case X_kbSelectEvents:
	return SProcXkbSelectEvents(client);
    case X_kbBell:
	return SProcXkbBell(client);
    case X_kbGetState:
	return SProcXkbGetState(client);
    case X_kbLatchLockState:
	return SProcXkbLatchLockState(client);
    case X_kbGetControls:
	return SProcXkbGetControls(client);
    case X_kbSetControls:
	return SProcXkbSetControls(client);
    case X_kbGetMap:
	return SProcXkbGetMap(client);
    case X_kbSetMap:
	return SProcXkbSetMap(client);
    case X_kbGetCompatMap:
	return SProcXkbGetCompatMap(client);
    case X_kbSetCompatMap:
	return SProcXkbSetCompatMap(client);
    case X_kbGetIndicatorState:
	return SProcXkbGetIndicatorState(client);
    case X_kbGetIndicatorMap:
	return SProcXkbGetIndicatorMap(client);
    case X_kbSetIndicatorMap:
	return SProcXkbSetIndicatorMap(client);
    case X_kbGetNamedIndicator:
	return SProcXkbGetNamedIndicator(client);
    case X_kbSetNamedIndicator:
	return SProcXkbSetNamedIndicator(client);
    case X_kbGetNames:
	return SProcXkbGetNames(client);
    case X_kbSetNames:
	return SProcXkbSetNames(client);
    case X_kbGetGeometry:
	return SProcXkbGetGeometry(client);
    case X_kbSetGeometry:
	return SProcXkbSetGeometry(client);
    case X_kbPerClientFlags:
	return SProcXkbPerClientFlags(client);
    case X_kbListComponents:
	return SProcXkbListComponents(client);
    case X_kbGetKbdByName:
	return SProcXkbGetKbdByName(client);
    case X_kbGetDeviceInfo:
	return SProcXkbGetDeviceInfo(client);
    case X_kbSetDeviceInfo:
	return SProcXkbSetDeviceInfo(client);
    case X_kbSetDebuggingFlags:
	return SProcXkbSetDebuggingFlags(client);
    default:
	return BadRequest;
    }
}
