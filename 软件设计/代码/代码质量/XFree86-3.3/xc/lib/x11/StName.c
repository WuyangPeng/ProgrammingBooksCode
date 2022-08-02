/* $XConsortium: StName.c /main/9 1996/10/22 14:23:18 kaleb $ */
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

#include <X11/Xlibint.h>
#include <X11/Xatom.h>

#if NeedFunctionPrototypes
XStoreName (
    register Display *dpy,
    Window w,
    _Xconst char *name)
#else
XStoreName (dpy, w, name)
    register Display *dpy;
    Window w;
    char *name;
#endif
{
    return XChangeProperty(dpy, w, XA_WM_NAME, XA_STRING, 
			   8, PropModeReplace, (unsigned char *)name,
			   name ? strlen(name) : 0);
}

#if NeedFunctionPrototypes
XSetIconName (
    register Display *dpy,
    Window w,
    _Xconst char *icon_name)
#else
XSetIconName (dpy, w, icon_name)
    register Display *dpy;
    Window w;
    char *icon_name;
#endif
{
    return XChangeProperty(dpy, w, XA_WM_ICON_NAME, XA_STRING, 
			   8, PropModeReplace, (unsigned char *)icon_name,
			   icon_name ? strlen(icon_name) : 0);
}
