/* $XConsortium: imLcLkup.c,v 1.7 95/06/07 22:41:51 kaleb Exp $ */
/******************************************************************

              Copyright 1992 by Fuji Xerox Co., Ltd.
              Copyright 1992, 1994  by FUJITSU LIMITED

Permission to use, copy, modify, distribute, and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and
that both that copyright notice and this permission notice appear
in supporting documentation, and that the name of Fuji Xerox,
FUJITSU LIMITED not be used in advertising or publicity pertaining
to distribution of the software without specific, written prior
permission.  Fuji Xerox, FUJITSU LIMITED  make no representations
about the suitability of this software for any purpose.
It is provided "as is" without express or implied warranty.

FUJI XEROX, FUJITSU LIMITED DISCLAIM ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL FUJI XEROX, 
FUJITSU LIMITED BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA
OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.

  Author: Kazunori Nishihara   Fuji Xerox
          Takashi Fujiwara     FUJITSU LIMITED 
                               fujiwara@a80.tech.yk.fujitsu.co.jp

******************************************************************/

#include <stdio.h>
#include <X11/Xatom.h>
#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include "Xlibint.h"
#include "Xlcint.h"
#include "Ximint.h"

Public int
_XimLocalMbLookupString(xic, ev, buffer, bytes, keysym, status)
    XIC		 xic;
    XKeyEvent	*ev;
    char	*buffer;
    int		 bytes;
    KeySym	 *keysym;
    Status	 *status;
{
    Xic		 ic = (Xic)xic;
    int		 ret;

    if(ev->type != KeyPress) {
	if(status) *status = XLookupNone;
	return(0);
    }
    if(ev->keycode == 0) { /* Composed Event */
	ret = strlen(ic->private.local.composed->mb);
	if(ret > bytes) {
	    if(status) *status = XBufferOverflow;
	    return(ret);
	}
	memcpy(buffer, ic->private.local.composed->mb, ret);
	if(keysym) *keysym = ic->private.local.composed->ks;
	if (ret > 0) {
	    if(keysym && *keysym != NoSymbol) {
		if(status) *status = XLookupBoth;
	    } else {
		if(status) *status = XLookupChars;
	    }
	} else {
	    if(keysym && *keysym != NoSymbol) {
		if(status) *status = XLookupKeySym;
	    } else {
		if(status) *status = XLookupNone;
	    }
	}
	return (ret);
    } else { /* Throughed Event */
	ret = _XimLookupMBText(ic, ev, (unsigned char *)buffer, bytes, keysym,
			       NULL);
	if(ret > 0) {
	    if(keysym && *keysym != NoSymbol) {
		if(status) *status = XLookupBoth;
	    } else {
		if(status) *status = XLookupChars;
	    }
	} else {
	    if(keysym && *keysym != NoSymbol) {
		if(status) *status = XLookupKeySym;
	    } else {
		if(status) *status = XLookupNone;
	    }
	}
    }
    return (ret);
}

Public int
_XimLocalWcLookupString(xic, ev, buffer, wlen, keysym, status)
    XIC		  xic;
    XKeyEvent	 *ev;
    wchar_t	 *buffer;
    int		  wlen;
    KeySym	 *keysym;
    Status	 *status;
{
    Xic		 ic = (Xic)xic;
    int		 ret;

    if(ev->type != KeyPress) {
	if(status) *status = XLookupNone;
	return(0);
    }
    if(ev->keycode == 0) { /* Composed Event */
	ret = _Xwcslen(ic->private.local.composed->wc);
	if(ret > wlen) {
	    if(status) *status = XBufferOverflow;
	    return (ret);
	}
	memcpy((char *)buffer, (char *)ic->private.local.composed->wc,
	       ret * sizeof(wchar_t));
	if(keysym) *keysym = ic->private.local.composed->ks;
	if (ret > 0) {
	    if(keysym && *keysym != NoSymbol) {
		if(status) *status = XLookupBoth;
	    } else {
		if(status) *status = XLookupChars;
	    }
	} else {
	    if(keysym && *keysym != NoSymbol) {
		if(status) *status = XLookupKeySym;
	    } else {
		if(status) *status = XLookupNone;
	    }
	}
	return (ret);
    } else { /* Throughed Event */
	ret = _XimLookupWCText(ic, ev, buffer, wlen, keysym, NULL);
	if(ret > 0) {
	    if(keysym && *keysym != NoSymbol) {
		if(status) *status = XLookupBoth;
	    } else {
		if(status) *status = XLookupChars;
	    }
	} else {
	    if(keysym && *keysym != NoSymbol) {
		if(status) *status = XLookupKeySym;
	    } else {
		if(status) *status = XLookupNone;
	    }
	}
    }
    return (ret);
}

#ifndef MAXINT
#define MAXINT		(~((unsigned int)1 << (8 * sizeof(int)) - 1))
#endif /* !MAXINT */

Public int
_XimLcctstombs(xim, from, from_len, to, to_len, state)
    XIM		 xim;
    char	*from;
    int		 from_len;
    char	*to;
    int		 to_len;
    Status	*state;
{
    Xim		 im = (Xim)xim;
    XlcConv	 conv = im->private.local.ctom_conv;
    int		 from_left;
    int		 to_left;
    int		 from_savelen;
    int		 to_savelen;
    int		 from_cnvlen;
    int		 to_cnvlen;
    char	*from_buf;
    char	*to_buf;
    Status	 tmp_state;

    if (!state)
	state = &tmp_state;

    if (!conv || !from || !from_len) {
	*state = XLookupNone;
	return 0;
    }

    if (to && to_len) {
	from_left = from_len;
	to_left = to_len;
	from_cnvlen = 0;
	to_cnvlen = 0;
	for (;;) {
	    from_savelen = from_left;
	    to_savelen = to_left;
	    from_buf = &from[from_cnvlen];
	    to_buf = &to[to_cnvlen];
	    if (_XlcConvert(conv, (XPointer *)&from_buf, &from_left,
				 (XPointer *)&to_buf, &to_left, NULL, 0) < 0) {
		*state = XLookupNone;
		return 0;
	    }
	    from_cnvlen += (from_savelen - from_left);
	    to_cnvlen += (to_savelen - to_left);
	    if (from_left == 0) {
		if (to_cnvlen > 0) {
		    *state = XLookupChars;
		} else {
		    *state = XLookupNone;
		}
		return to_cnvlen;
	    }
	    if (to_left == 0)
		break;
	}
    }

    from_left = from_len;
    from_cnvlen = 0;
    to_cnvlen = 0;
    to_buf = NULL;
    for (;;) {
	from_savelen = from_left;
	to_left = MAXINT;
	from_buf = &from[from_cnvlen];
	if (_XlcConvert(conv, (XPointer *)&from_buf, &from_left,
				 (XPointer *)&to_buf, &to_left, NULL, 0) < 0) {
	    *state = XLookupNone;
	    return 0;
	}
	from_cnvlen += (from_savelen - from_left);
	to_cnvlen += (MAXINT - to_left);
	if (from_left == 0) {
	    if (to_cnvlen > 0)
		*state = XBufferOverflow;
	    else
		*state = XLookupNone;
	    break;
	}
    }
    return to_cnvlen;
}

Public int
_XimLcctstowcs(xim, from, from_len, to, to_len, state)
    XIM		 xim;
    char	*from;
    int		 from_len;
    wchar_t	*to;
    int		 to_len;
    Status	*state;
{
    Xim		 im = (Xim)xim;
    XlcConv	 conv = im->private.local.ctow_conv;
    int		 from_left;
    int		 to_left;
    int		 from_savelen;
    int		 to_savelen;
    int		 from_cnvlen;
    int		 to_cnvlen;
    char	*from_buf;
    wchar_t	*to_buf;
    Status	 tmp_state;

    if (!state)
	state = &tmp_state;

    if (!conv || !from || !from_len) {
	*state = XLookupNone;
	return 0;
    }

    if (to && to_len) {
	from_left = from_len;
	to_left = to_len;
	from_cnvlen = 0;
	to_cnvlen = 0;
	for (;;) {
	    from_savelen = from_left;
	    to_savelen = to_left;
	    from_buf = &from[from_cnvlen];
	    to_buf = &to[to_cnvlen];
	    if (_XlcConvert(conv, (XPointer *)&from_buf, &from_left,
				 (XPointer *)&to_buf, &to_left, NULL, 0) < 0) {
		*state = XLookupNone;
		return 0;
	    }
	    from_cnvlen += (from_savelen - from_left);
	    to_cnvlen += (to_savelen - to_left);
	    if (from_left == 0) {
		if (to_cnvlen > 0) {
		    *state = XLookupChars;
		} else {
		    *state = XLookupNone;
		}
		return to_cnvlen;
	    }
	    if (to_left == 0)
		break;
	}
    }
		
    from_left = from_len;
    from_cnvlen = 0;
    to_cnvlen = 0;
    to_buf = (wchar_t *)NULL;
    for (;;) {
	from_savelen = from_left;
	to_left = MAXINT;
	from_buf = &from[from_cnvlen];
	if (_XlcConvert(conv, (XPointer *)&from_buf, &from_left,
				 (XPointer *)&to_buf, &to_left, NULL, 0) < 0) {
	    *state = XLookupNone;
	    return 0;
	}
	from_cnvlen += (from_savelen - from_left);
	to_cnvlen += (MAXINT - to_left);
	if (from_left == 0) {
	    if (to_cnvlen > 0)
		*state = XBufferOverflow;
	    else
		*state = XLookupNone;
	    break;
	}
    }
    return to_cnvlen;
}
