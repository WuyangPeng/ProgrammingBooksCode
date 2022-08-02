/* $XConsortium: PProcess.c /main/4 1996/09/25 20:28:56 lehors $ */
/*

Copyright (C) 1996 X Consortium

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Soft-
ware"), to deal in the Software without restriction, including without
limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to
whom the Software is furnished to do so, subject to the following condi-
tions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABIL-
ITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT
SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABIL-
ITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization from
the X Consortium.

*/

#include "RxPlugin.h"
#include "XUrls.h"

/***********************************************************************
 * Process the given RxParams and make the RxReturnParams
 ***********************************************************************/
int
RxpProcessParams(PluginInstance* This, RxParams *in, RxReturnParams *out)
{
    /* init return struture */
    memset(out, 0, sizeof(RxReturnParams));
    out->x_ui_lbx = RxUndef;
    out->x_print_lbx = RxUndef;

    out->action = in->action;
    if (in->embedded != RxUndef)
	out->embedded = RxTrue; /* we do support embbeding! */
    else
	out->embedded = RxUndef;

    out->width = in->width;
    out->height = in->height;	

    if (in->ui[0] == XUI) {	/* X display needed */
        out->ui = GetXUrl(RxpXnestDisplay(This->display_num), NULL);

	if (in->x_ui_lbx != RxUndef)
	    out->x_ui_lbx = RxFalse; /* we do not support LBX */
	else
	    out->x_ui_lbx = RxUndef;
    }

    if (in->print[0] == XPrint)	{ /* XPrint server needed */
        out->print = NULL;

	if (in->x_print_lbx != RxUndef)
	    out->x_print_lbx = RxFalse; /* we do not support LBX */
	else
	    out->x_print_lbx = RxUndef;
    }
    return 0;
}
