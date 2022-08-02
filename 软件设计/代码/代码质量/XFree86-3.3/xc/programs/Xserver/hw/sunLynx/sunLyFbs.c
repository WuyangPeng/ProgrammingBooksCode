/* $XConsortium: sunLyFbs.c /main/1 1996/10/31 14:20:48 kaleb $ */



/* $XFree86: xc/programs/Xserver/hw/sunLynx/sunLyFbs.c,v 3.2 1996/12/27 06:51:37 dawes Exp $ */

/*
 * This is sunFbs.c modified for LynxOS
 * Copyright 1996 by Thomas Mueller
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Thomas Mueller not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Thomas Mueller makes no representations
 * about the suitability of this software for any purpose.  It is provided
 * "as is" without express or implied warranty.
 *
 * THOMAS MUELLER DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THOMAS MUELLER BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 */

/*
Copyright (c) 1990, 1993  X Consortium

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

/************************************************************
Copyright 1987 by Sun Microsystems, Inc. Mountain View, CA.

                    All Rights Reserved

Permission  to  use,  copy,  modify,  and  distribute   this
software  and  its documentation for any purpose and without
fee is hereby granted, provided that the above copyright no-
tice  appear  in all copies and that both that copyright no-
tice and this permission notice appear in  supporting  docu-
mentation,  and  that the names of Sun or X Consortium
not be used in advertising or publicity pertaining to 
distribution  of  the software  without specific prior 
written permission. Sun and X Consortium make no 
representations about the suitability of this software for 
any purpose. It is provided "as is" without any express or 
implied warranty.

SUN DISCLAIMS ALL WARRANTIES WITH REGARD TO  THIS  SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FIT-
NESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL SUN BE  LI-
ABLE  FOR  ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,  DATA  OR
PROFITS,  WHETHER  IN  AN  ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
THE USE OR PERFORMANCE OF THIS SOFTWARE.

********************************************************/

/*
 * Copyright (c) 1987 by the Regents of the University of California
 * Copyright (c) 1987 by Adam de Boor, UC Berkeley
 *
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any purpose and without
 * fee is hereby granted, provided that the above copyright
 * notice appear in all copies.  The University of California
 * makes no representations about the suitability of this
 * software for any purpose.  It is provided "as is" without
 * express or implied warranty.
 */

/****************************************************************/
/* Modified from  sunCG4C.c for X11R3 by Tom Jarmolowski	*/
/****************************************************************/

#include "sun.h"
#include <smem.h>

int sunScreenIndex;

static unsigned long generation = 0;

#if NeedFunctionPrototypes
pointer sunMemoryMap (
    size_t	len,
    off_t	off,
    int		fd,
    char	*name
    )
#else
pointer sunMemoryMap (len, off, fd, name)
    size_t	len;
    off_t	off;
    int		fd;
    char	*name;
#endif
{
    int		pagemask, mapsize;
    caddr_t	addr;
    pointer	mapaddr;

    pagemask = getpagesize() - 1;
    mapsize = ((int) len + pagemask) & ~pagemask;
    addr = 0;

    mapaddr = smem_create(name, (char *)off, mapsize, SM_READ|SM_WRITE);
    if (mapaddr == (pointer) -1) {
	Error ("mapping frame buffer memory");
	(void) close (fd);
	mapaddr = (pointer) NULL;
    }
    return mapaddr;
}

#if NeedFunctionPrototypes
Bool sunScreenAllocate (
    ScreenPtr	pScreen)
#else
Bool sunScreenAllocate (pScreen)
    ScreenPtr	pScreen;
#endif
{
    sunScreenPtr    pPrivate;
    extern int AllocateScreenPrivateIndex();

    if (generation != serverGeneration)
    {
	sunScreenIndex = AllocateScreenPrivateIndex();
	if (sunScreenIndex < 0)
	    return FALSE;
	generation = serverGeneration;
    }
    pPrivate = (sunScreenPtr) xalloc (sizeof (sunScreenRec));
    if (!pPrivate)
	return FALSE;

    pScreen->devPrivates[sunScreenIndex].ptr = (pointer) pPrivate;
    return TRUE;
}

#if NeedFunctionPrototypes
Bool sunSaveScreen (
    ScreenPtr	pScreen,
    int		on)
#else
Bool sunSaveScreen (pScreen, on)
    ScreenPtr	pScreen;
    int		on;
#endif
{
    int		state;

    if (on != SCREEN_SAVER_FORCER)
    {
	if (on == SCREEN_SAVER_ON)
	    state = 0;
	else
	    state = 1;
	(void) sunIoctl(&sunFbs[pScreen->myNum], FBIOSVIDEO, &state);
    }
    return( TRUE );
}

static Bool closeScreen (i, pScreen)
    int		i;
    ScreenPtr	pScreen;
{
    SetupScreen(pScreen);
    Bool    ret;
    struct fbcmap sunCmap;
    unsigned char color;

    (void) OsSignal (SIGIO, SIG_IGN);
    sunDisableCursor (pScreen);
    pScreen->CloseScreen = pPrivate->CloseScreen;
    ret = (*pScreen->CloseScreen) (i, pScreen);
    (void) (*pScreen->SaveScreen) (pScreen, SCREEN_SAVER_OFF);
    /* probably this doesn't belong here: restore black&white cmap */
    sunCmap.count = 1;
    sunCmap.index = 0;
    sunCmap.red = sunCmap.green = sunCmap.blue = &color;
    color = 0xff;
    (void) sunIoctl(&sunFbs[pScreen->myNum], FBIOPUTCMAP, &sunCmap);
    sunCmap.index = 0xff;
    color = 0;
    (void) sunIoctl(&sunFbs[pScreen->myNum], FBIOPUTCMAP, &sunCmap);
    xfree ((pointer) pPrivate);
    return ret;
}

#if NeedFunctionPrototypes
Bool sunScreenInit (
    ScreenPtr	pScreen)
#else
Bool sunScreenInit (pScreen)
    ScreenPtr	pScreen;
#endif
{
    SetupScreen(pScreen);
    extern void   sunBlockHandler();
    extern void   sunWakeupHandler();
    static ScreenPtr autoRepeatScreen;
    extern miPointerScreenFuncRec   sunPointerScreenFuncs;

    pPrivate->installedMap = 0;
    pPrivate->CloseScreen = pScreen->CloseScreen;
    pScreen->CloseScreen = closeScreen;
    pScreen->SaveScreen = sunSaveScreen;
#ifdef XKB
    if (noXkbExtension) {
#endif
    /*
     *	Block/Unblock handlers
     */
    if (sunAutoRepeatHandlersInstalled == FALSE) {
	autoRepeatScreen = pScreen;
	sunAutoRepeatHandlersInstalled = TRUE;
    }

    if (pScreen == autoRepeatScreen) {
        pScreen->BlockHandler = sunBlockHandler;
        pScreen->WakeupHandler = sunWakeupHandler;
    }
#ifdef XKB
    } else {
       /* this works around a weird behaviour on LynxOS 2.4.0:
        * usually we have no problems using true SIGIO driven mouse input
        * as it is used on the other UN*X Suns. On LynxOS we have a
        * strange behaviour upon the very first server startup after a 
        * reboot. We won't get SIGIOs from the mouse device. The mouse
        * will only move if we get SIGIOs from the keyboard.
        * The solution (for now) is to use a WakeupHandler and
        * poll the mouse file descriptor.
        */
        pScreen->WakeupHandler = sunWakeupHandler;
    }
#endif
    if (!sunCursorInitialize (pScreen))
	miDCInitialize (pScreen, &sunPointerScreenFuncs);
    return TRUE;
}

#if NeedFunctionPrototypes
Bool sunInitCommon (
    int		scrn,
    ScreenPtr	pScrn,
    off_t	offset,
    Bool	(*init1)(),
    void	(*init2)(),
    Bool	(*cr_cm)(),
    Bool	(*save)(),
    int		fb_off)
#else
Bool sunInitCommon (scrn, pScrn, offset, init1, init2, cr_cm, save, fb_off)
    int		scrn;
    ScreenPtr	pScrn;
    off_t	offset;
    Bool	(*init1)();
    void	(*init2)();
    Bool	(*cr_cm)();
    Bool	(*save)();
    int		fb_off;
#endif
{
    unsigned char*	fb = sunFbs[scrn].fbuf;
    unsigned char*	dac = sunFbs[scrn].ramdac;

    if (!sunScreenAllocate (pScrn))
	return FALSE;
    if (!fb) {
	if ((fb = sunMemoryMap ((size_t) sunFbs[scrn].info.fb_size, 
			     (unsigned long)offset + 0x00800000UL,
			     sunFbs[scrn].fd, "FB")) == NULL)
	    return FALSE;
	sunFbs[scrn].fbuf = fb;
	if (!dac)
	{
	    unsigned long dacoffset;

	    if (ioctl(sunFbs[scrn].fd, TIO_QUERYRAMDAC, &dacoffset) < 0)
    	        FatalError("can't query DAC addr\n");
	    if ((dac = sunMemoryMap((size_t) sunFbs[scrn].info.fb_cmsize * 3,
	    		(unsigned long)offset + dacoffset,
	    		sunFbs[scrn].fd, "DAC")) == NULL)
	    	return FALSE;

	    sunFbs[scrn].ramdac = dac;
	}
    }
    /* mfbScreenInit() or cfbScreenInit() */
    if (!(*init1)(pScrn, fb + fb_off,
	    sunFbs[scrn].info.fb_width,
	    sunFbs[scrn].info.fb_height,
	    monitorResolution, monitorResolution,
	    sunFbs[scrn].info.fb_width,
	    sunFbs[scrn].info.fb_depth))
	    return FALSE;
    /* sunCGScreenInit() if cfb... */
    if (init2)
	(*init2)(pScrn);
    if (!sunScreenInit(pScrn))
	return FALSE;
    (void) (*save) (pScrn, SCREEN_SAVER_OFF);
    return (*cr_cm)(pScrn);
}

