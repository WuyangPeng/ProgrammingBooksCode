/* $XConsortium: events.c,v 1.6 94/12/19 16:57:13 mor Exp $ */

/*

Copyright (c) 1993, 1994  X Consortium

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from the X Consortium.

*/

#define NEED_EVENTS   /* so xEvent will get pulled in */
#include "XIElibint.h"


Status
_XieColorAllocEvent (display, host, wire)

Display		*display;
XEvent		*host;
xEvent		*wire;

{
    XieColorAllocEvent	     *host_event = (XieColorAllocEvent *) host;
    xieColorAllocEvn	     *wire_event = (xieColorAllocEvn *) wire;

    host_event->type                  = wire_event->event & 0x7f;
    host_event->serial                = wire_event->sequenceNum;
    host_event->send_event            = (wire_event->event & 0x80) != 0;
    host_event->display               = display;
    host_event->name_space            = wire_event->instanceNameSpace;
    host_event->time                  = wire_event->time;
    host_event->flo_id                = wire_event->instanceFloID;
    host_event->src                   = wire_event->src;
    host_event->elem_type             = wire_event->type;
    host_event->color_list            = wire_event->colorList;
    host_event->color_alloc_technique = wire_event->colorAllocTechnique;
    host_event->color_alloc_data      = wire_event->data;

    return (True);
}


Status
_XieDecodeNotifyEvent (display, host, wire)

Display		*display;
XEvent		*host;
xEvent		*wire;

{
    XieDecodeNotifyEvent     *host_event = (XieDecodeNotifyEvent *) host;
    xieDecodeNotifyEvn	     *wire_event = (xieDecodeNotifyEvn *) wire;

    host_event->type             = wire_event->event & 0x7f;
    host_event->serial           = wire_event->sequenceNum;
    host_event->send_event       = (wire_event->event & 0x80) != 0;
    host_event->display          = display;
    host_event->name_space       = wire_event->instanceNameSpace;
    host_event->time             = wire_event->time;
    host_event->flo_id           = wire_event->instanceFloID;
    host_event->src              = wire_event->src;
    host_event->elem_type        = wire_event->type;
    host_event->decode_technique = wire_event->decodeTechnique;
    host_event->aborted          = wire_event->aborted;
    host_event->band_number      = wire_event->bandNumber;
    host_event->width		 = wire_event->width;
    host_event->height		 = wire_event->height;

    return (True);
}


Status
_XieExportAvailableEvent (display, host, wire)

Display		*display;
XEvent		*host;
xEvent		*wire;

{
    XieExportAvailableEvent  *host_event = (XieExportAvailableEvent *) host;
    xieExportAvailableEvn    *wire_event = (xieExportAvailableEvn *) wire;

    host_event->type       = wire_event->event & 0x7f;
    host_event->serial     = wire_event->sequenceNum;
    host_event->send_event = (wire_event->event & 0x80) != 0;
    host_event->display    = display;
    host_event->name_space = wire_event->instanceNameSpace;
    host_event->time       = wire_event->time;
    host_event->flo_id     = wire_event->instanceFloID;
    host_event->src        = wire_event->src;
    host_event->elem_type  = wire_event->type;
    host_event->band_number = wire_event->bandNumber;
    host_event->data[0]    = wire_event->data0;
    host_event->data[1]    = wire_event->data1;
    host_event->data[2]    = wire_event->data2;

    return (True);
}


Status
_XieImportObscuredEvent (display, host, wire)

Display		*display;
XEvent		*host;
xEvent		*wire;

{
    XieImportObscuredEvent   *host_event = (XieImportObscuredEvent *) host;
    xieImportObscuredEvn     *wire_event = (xieImportObscuredEvn *) wire;

    host_event->type       = wire_event->event & 0x7f;
    host_event->serial     = wire_event->sequenceNum;
    host_event->send_event = (wire_event->event & 0x80) != 0;
    host_event->display    = display;
    host_event->name_space = wire_event->instanceNameSpace;
    host_event->time       = wire_event->time;
    host_event->flo_id     = wire_event->instanceFloID;
    host_event->src        = wire_event->src;
    host_event->elem_type  = wire_event->type;
    host_event->window     = wire_event->window;
    host_event->x	   = wire_event->x;
    host_event->y	   = wire_event->y;
    host_event->width	   = wire_event->width;
    host_event->height	   = wire_event->height;

    return (True);
}


Status
_XiePhotofloDoneEvent (display, host, wire)

Display		*display;
XEvent		*host;
xEvent		*wire;

{
    XiePhotofloDoneEvent     *host_event = (XiePhotofloDoneEvent *) host;
    xiePhotofloDoneEvn	     *wire_event = (xiePhotofloDoneEvn *) wire;

    host_event->type       = wire_event->event & 0x7f;
    host_event->serial     = wire_event->sequenceNum;
    host_event->send_event = (wire_event->event & 0x80) != 0;
    host_event->display    = display;
    host_event->name_space = wire_event->instanceNameSpace;
    host_event->time       = wire_event->time;
    host_event->flo_id     = wire_event->instanceFloID;
    host_event->outcome    = wire_event->outcome;

    return (True);
}
