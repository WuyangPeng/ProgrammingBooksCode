/* $XConsortium: InitOutput.c /main/17 1996/12/02 10:20:41 lehors $ */
/* $XFree86: xc/programs/Xserver/hw/vfb/InitOutput.c,v 3.5 1997/01/12 10:41:03 dawes Exp $ */
/*

Copyright (c) 1993  X Consortium

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

#ifdef WIN32
#include <X11/Xwinsock.h>
#endif
#include <stdio.h>
#include "X11/X.h"
#define NEED_EVENTS
#include "X11/Xproto.h"
#include "X11/Xos.h"
#include "scrnintstr.h"
#include "servermd.h"
#define PSZ 8
#include "cfb.h"
#include "mibstore.h"
#include "colormapst.h"
#include "gcstruct.h"
#include "input.h"
#include "mipointer.h"
#include <sys/types.h>
#ifdef HAS_MMAP
#include <sys/mman.h>
#ifndef MAP_FILE
#define MAP_FILE 0
#endif
#endif /* HAS_MMAP */
#include <sys/stat.h>
#include <errno.h>
#ifndef WIN32
#include <sys/param.h>
#endif
#include <X11/XWDFile.h>
#ifdef HAS_SHM
#include <sys/ipc.h>
#include <sys/shm.h>
#endif /* HAS_SHM */
#include "dix.h"
#include "miline.h"

extern char *display;

#define VFB_DEFAULT_WIDTH  1280
#define VFB_DEFAULT_HEIGHT 1024
#define VFB_DEFAULT_DEPTH  8
#define VFB_DEFAULT_WHITEPIXEL 0
#define VFB_DEFAULT_BLACKPIXEL 1
#define VFB_DEFAULT_LINEBIAS 0
#define XWD_WINDOW_NAME_LEN 60

typedef struct
{
    int scrnum;
    int width;
    int paddedWidth;
    int height;
    int depth;
    int bitsPerPixel;
    int sizeInBytes;
    int ncolors;
    char *pfbMemory;
    XWDColor *pXWDCmap;
    XWDFileHeader *pXWDHeader;
    Pixel blackPixel;
    Pixel whitePixel;
    unsigned int lineBias;

#ifdef HAS_MMAP
    int mmap_fd;
    char mmap_file[MAXPATHLEN];
#endif

#ifdef HAS_SHM
    int shmid;
#endif
} vfbScreenInfo, *vfbScreenInfoPtr;

static int vfbNumScreens;
static vfbScreenInfo vfbScreens[MAXSCREENS];
static Bool vfbPixmapDepths[33];
static char *pfbdir = NULL;
typedef enum { NORMAL_MEMORY_FB, SHARED_MEMORY_FB, MMAPPED_FILE_FB } fbMemType;
static fbMemType fbmemtype = NORMAL_MEMORY_FB;
static char needswap = 0;
static int lastScreen = -1;

#define swapcopy16(_dst, _src) \
    if (needswap) { CARD16 _s = _src; cpswaps(_s, _dst); } \
    else _dst = _src;

#define swapcopy32(_dst, _src) \
    if (needswap) { CARD32 _s = _src; cpswapl(_s, _dst); } \
    else _dst = _src;


static void
vfbInitializePixmapDepths()
{
    int i;
    vfbPixmapDepths[1] = TRUE; /* always need bitmaps */
    for (i = 2; i <= 32; i++)
	vfbPixmapDepths[i] = FALSE;
}

static void
vfbInitializeDefaultScreens()
{
    int i;

    for (i = 0; i < MAXSCREENS; i++)
    {
	vfbScreens[i].scrnum = i;
	vfbScreens[i].width  = VFB_DEFAULT_WIDTH;
	vfbScreens[i].height = VFB_DEFAULT_HEIGHT;
	vfbScreens[i].depth  = VFB_DEFAULT_DEPTH;
	vfbScreens[i].blackPixel = VFB_DEFAULT_BLACKPIXEL;
	vfbScreens[i].whitePixel = VFB_DEFAULT_WHITEPIXEL;
	vfbScreens[i].lineBias = VFB_DEFAULT_LINEBIAS;
	vfbScreens[i].pfbMemory = NULL;
    }
    vfbNumScreens = 1;
}

static int
vfbBitsPerPixel(depth)
    int depth;
{
    if (depth == 1) return 1;
    else if (depth <= 8) return 8;
    else if (depth <= 16) return 16;
    else return 32;
}

void
ddxGiveUp()
{
    int i;

    /* clean up the framebuffers */

    switch (fbmemtype)
    {
#ifdef HAS_MMAP
    case MMAPPED_FILE_FB: 
	for (i = 0; i < vfbNumScreens; i++)
	{
	    if (-1 == unlink(vfbScreens[i].mmap_file))
	    {
		perror("unlink");
		ErrorF("unlink %s failed, errno %d",
		       vfbScreens[i].mmap_file, errno);
	    }
	}
	break;
#endif /* HAS_MMAP */
	
#ifdef HAS_SHM
    case SHARED_MEMORY_FB:
	for (i = 0; i < vfbNumScreens; i++)
	{
	    if (-1 == shmdt((char *)vfbScreens[i].pXWDHeader))
	    {
		perror("shmdt");
		ErrorF("shmdt failed, errno %d", errno);
	    }
	}
	break;
#endif /* HAS_SHM */
	
    case NORMAL_MEMORY_FB:
	for (i = 0; i < vfbNumScreens; i++)
	{
	    Xfree(vfbScreens[i].pXWDHeader);
	}
	break;
    }
}

void
AbortDDX()
{
    ddxGiveUp();
}

void
OsVendorInit()
{
}

void
OsVendorFatalError()
{
}

void
ddxUseMsg()
{
    ErrorF("-screen scrn WxHxD     set screen's width, height, depth\n");
    ErrorF("-pixdepths list-of-int support given pixmap depths\n");
    ErrorF("-linebias n            adjust thin line pixelization\n");
    ErrorF("-blackpixel n          pixel value for black\n");
    ErrorF("-whitepixel n          pixel value for white\n");

#ifdef HAS_MMAP
    ErrorF("-fbdir directory       put framebuffers in mmap'ed files in directory\n");
#endif

#ifdef HAS_SHM
    ErrorF("-shmem                 put framebuffers in shared memory\n");
#endif
}

int
ddxProcessArgument (argc, argv, i)
    int argc;
    char *argv[];
    int i;
{
    static Bool firstTime = TRUE;

    if (firstTime)
    {
	vfbInitializeDefaultScreens();
	vfbInitializePixmapDepths();
        firstTime = FALSE;
    }

    if (strcmp (argv[i], "-screen") == 0)	/* -screen n WxHxD */
    {
	int screenNum;
	if (i + 2 >= argc) UseMsg();
	screenNum = atoi(argv[i+1]);
	if (screenNum < 0 || screenNum >= MAXSCREENS)
	{
	    ErrorF("Invalid screen number %d\n", screenNum);
	    UseMsg();
	}
	if (3 != sscanf(argv[i+2], "%dx%dx%d",
			&vfbScreens[screenNum].width,
			&vfbScreens[screenNum].height,
			&vfbScreens[screenNum].depth))
	{
	    ErrorF("Invalid screen configuration %s\n", argv[i+2]);
	    UseMsg();
	}

	if (screenNum >= vfbNumScreens)
	    vfbNumScreens = screenNum + 1;
	lastScreen = screenNum;
	return 3;
    }

    if (strcmp (argv[i], "-pixdepths") == 0)	/* -pixdepths list-of-depth */
    {
	int depth, ret = 1;

	if (++i >= argc) UseMsg();
	while ((i < argc) && (depth = atoi(argv[i++])) != 0)
	{
	    if (depth < 0 || depth > 32)
	    {
		ErrorF("Invalid pixmap depth %d\n", depth);
		UseMsg();
	    }
	    vfbPixmapDepths[depth] = TRUE;
	    ret++;
	}
	return ret;
    }

    if (strcmp (argv[i], "-blackpixel") == 0)	/* -blackpixel n */
    {
	Pixel pix;
	if (++i >= argc) UseMsg();
	pix = atoi(argv[i]);
	if (-1 == lastScreen)
	{
	    int i;
	    for (i = 0; i < MAXSCREENS; i++)
	    {
		vfbScreens[i].blackPixel = pix;
	    }
	}
	else
	{
	    vfbScreens[lastScreen].blackPixel = pix;
	}
	return 2;
    }

    if (strcmp (argv[i], "-whitepixel") == 0)	/* -whitepixel n */
    {
	Pixel pix;
	if (++i >= argc) UseMsg();
	pix = atoi(argv[i]);
	if (-1 == lastScreen)
	{
	    int i;
	    for (i = 0; i < MAXSCREENS; i++)
	    {
		vfbScreens[i].whitePixel = pix;
	    }
	}
	else
	{
	    vfbScreens[lastScreen].whitePixel = pix;
	}
	return 2;
    }

    if (strcmp (argv[i], "-linebias") == 0)	/* -linebias n */
    {
	unsigned int linebias;
	if (++i >= argc) UseMsg();
	linebias = atoi(argv[i]);
	if (-1 == lastScreen)
	{
	    int i;
	    for (i = 0; i < MAXSCREENS; i++)
	    {
		vfbScreens[i].lineBias = linebias;
	    }
	}
	else
	{
	    vfbScreens[lastScreen].lineBias = linebias;
	}
	return 2;
    }

#ifdef HAS_MMAP
    if (strcmp (argv[i], "-fbdir") == 0)	/* -fbdir directory */
    {
	if (++i >= argc) UseMsg();
	pfbdir = argv[i];
	fbmemtype = MMAPPED_FILE_FB;
	return 2;
    }
#endif /* HAS_MMAP */

#ifdef HAS_SHM
    if (strcmp (argv[i], "-shmem") == 0)	/* -shmem */
    {
	fbmemtype = SHARED_MEMORY_FB;
	return 1;
    }
#endif

    return 0;
}

#ifdef DDXTIME /* from ServerOSDefines */
CARD32
GetTimeInMillis()
{
    struct timeval  tp;

    X_GETTIMEOFDAY(&tp);
    return(tp.tv_sec * 1000) + (tp.tv_usec / 1000);
}
#endif


static Bool
vfbMultiDepthCreateGC(pGC)
    GCPtr   pGC;
{
    switch (vfbBitsPerPixel(pGC->depth))
    {
    case 1:  return mfbCreateGC (pGC);
    case 8:  return cfbCreateGC (pGC);
    case 16: return cfb16CreateGC (pGC);
    case 32: return cfb32CreateGC (pGC);
    default: return FALSE;
    }
}

static void
vfbMultiDepthGetSpans(pDrawable, wMax, ppt, pwidth, nspans, pdstStart)
    DrawablePtr		pDrawable;	/* drawable from which to get bits */
    int			wMax;		/* largest value of all *pwidths */
    register DDXPointPtr ppt;		/* points to start copying from */
    int			*pwidth;	/* list of number of bits to copy */
    int			nspans;		/* number of scanlines to copy */
    char		*pdstStart;	/* where to put the bits */
{
    switch (pDrawable->bitsPerPixel) {
    case 1:
	mfbGetSpans(pDrawable, wMax, ppt, pwidth, nspans, pdstStart);
	break;
    case 8:
	cfbGetSpans(pDrawable, wMax, ppt, pwidth, nspans, pdstStart);
	break;
    case 16:
	cfb16GetSpans(pDrawable, wMax, ppt, pwidth, nspans, pdstStart);
	break;
    case 32:
	cfb32GetSpans(pDrawable, wMax, ppt, pwidth, nspans, pdstStart);
	break;
    }
    return;
}

static void
vfbMultiDepthGetImage(pDrawable, sx, sy, w, h, format, planeMask, pdstLine)
    DrawablePtr pDrawable;
    int		sx, sy, w, h;
    unsigned int format;
    unsigned long planeMask;
    char	*pdstLine;
{
    switch (pDrawable->bitsPerPixel)
    {
    case 1:
	mfbGetImage(pDrawable, sx, sy, w, h, format, planeMask, pdstLine);
	break;
    case 8:
	cfbGetImage(pDrawable, sx, sy, w, h, format, planeMask, pdstLine);
	break;
    case 16:
	cfb16GetImage(pDrawable, sx, sy, w, h, format, planeMask, pdstLine);
	break;
    case 32:
	cfb32GetImage(pDrawable, sx, sy, w, h, format, planeMask, pdstLine);
	break;
    }
}

static ColormapPtr InstalledMaps[MAXSCREENS];

static int
vfbListInstalledColormaps(pScreen, pmaps)
    ScreenPtr	pScreen;
    Colormap	*pmaps;
{
    /* By the time we are processing requests, we can guarantee that there
     * is always a colormap installed */
    *pmaps = InstalledMaps[pScreen->myNum]->mid;
    return (1);
}


static void
vfbInstallColormap(pmap)
    ColormapPtr	pmap;
{
    int index = pmap->pScreen->myNum;
    ColormapPtr oldpmap = InstalledMaps[index];

    if (pmap != oldpmap)
    {
	int entries;
	XWDFileHeader *pXWDHeader;
	XWDColor *pXWDCmap;
	VisualPtr pVisual;
	Pixel *     ppix;
	xrgb *      prgb;
	xColorItem *defs;
	int i;

	if(oldpmap != (ColormapPtr)None)
	    WalkTree(pmap->pScreen, TellLostMap, (char *)&oldpmap->mid);
	/* Install pmap */
	InstalledMaps[index] = pmap;
	WalkTree(pmap->pScreen, TellGainedMap, (char *)&pmap->mid);

	entries = pmap->pVisual->ColormapEntries;
	pXWDHeader = vfbScreens[pmap->pScreen->myNum].pXWDHeader;
	pXWDCmap = vfbScreens[pmap->pScreen->myNum].pXWDCmap;
	pVisual = pmap->pVisual;

	swapcopy32(pXWDHeader->visual_class, pVisual->class);
	swapcopy32(pXWDHeader->red_mask, pVisual->redMask);
	swapcopy32(pXWDHeader->green_mask, pVisual->greenMask);
	swapcopy32(pXWDHeader->blue_mask, pVisual->blueMask);
	swapcopy32(pXWDHeader->bits_per_rgb, pVisual->bitsPerRGBValue);
	swapcopy32(pXWDHeader->colormap_entries, pVisual->ColormapEntries);

	ppix = (Pixel *)ALLOCATE_LOCAL(entries * sizeof(Pixel));
	prgb = (xrgb *)ALLOCATE_LOCAL(entries * sizeof(xrgb));
	defs = (xColorItem *)ALLOCATE_LOCAL(entries * sizeof(xColorItem));

	for (i = 0; i < entries; i++)  ppix[i] = i;
	/* XXX truecolor */
	QueryColors(pmap, entries, ppix, prgb);

	for (i = 0; i < entries; i++) { /* convert xrgbs to xColorItems */
	    defs[i].pixel = ppix[i] & 0xff; /* change pixel to index */
	    defs[i].red = prgb[i].red;
	    defs[i].green = prgb[i].green;
	    defs[i].blue = prgb[i].blue;
	    defs[i].flags =  DoRed|DoGreen|DoBlue;
	}
	(*pmap->pScreen->StoreColors)(pmap, entries, defs);

	DEALLOCATE_LOCAL(ppix);
	DEALLOCATE_LOCAL(prgb);
	DEALLOCATE_LOCAL(defs);
    }
}

static void
vfbUninstallColormap(pmap)
    ColormapPtr	pmap;
{
    ColormapPtr curpmap = InstalledMaps[pmap->pScreen->myNum];

    if(pmap == curpmap)
    {
	if (pmap->mid != pmap->pScreen->defColormap)
	{
	    curpmap = (ColormapPtr) LookupIDByType(pmap->pScreen->defColormap,
						   RT_COLORMAP);
	    (*pmap->pScreen->InstallColormap)(curpmap);
	}
    }
}

static void
vfbStoreColors(pmap, ndef, pdefs)
    ColormapPtr pmap;
    int         ndef;
    xColorItem  *pdefs;
{
    XWDColor *pXWDCmap;
    int i;

    if (pmap != InstalledMaps[pmap->pScreen->myNum]) return;

    pXWDCmap = vfbScreens[pmap->pScreen->myNum].pXWDCmap;

    if ((pmap->pVisual->class | DynamicClass) == DirectColor)
	return;

    for (i = 0; i < ndef; i++)
    {
	if (pdefs[i].flags & DoRed)
	    swapcopy16(pXWDCmap[pdefs[i].pixel].red, pdefs[i].red);
	if (pdefs[i].flags & DoGreen)
	    swapcopy16(pXWDCmap[pdefs[i].pixel].green, pdefs[i].green);
	if (pdefs[i].flags & DoBlue)
	    swapcopy16(pXWDCmap[pdefs[i].pixel].blue, pdefs[i].blue);
    }
}

static Bool
vfbSaveScreen(pScreen, on)
    ScreenPtr pScreen;
    int on;
{
    return TRUE;
}

#ifdef HAS_MMAP

/* this flushes any changes to the screens out to the mmapped file */
static void
vfbBlockHandler(blockData, pTimeout, pReadmask)
    pointer   blockData;
    OSTimePtr pTimeout;
    pointer   pReadmask;
{
    int i;

    for (i = 0; i < vfbNumScreens; i++)
    {
#ifdef MS_ASYNC
	if (-1 == msync((caddr_t)vfbScreens[i].pXWDHeader,
			(size_t)vfbScreens[i].sizeInBytes, MS_ASYNC))
#else
	/* silly NetBSD and who else? */
	if (-1 == msync((caddr_t)vfbScreens[i].pXWDHeader,
			(size_t)vfbScreens[i].sizeInBytes))
#endif
	{
	    perror("msync");
	    ErrorF("msync failed, errno %d", errno);
	}
    }
}


static void
vfbWakeupHandler(blockData, result, pReadmask)
    pointer blockData;
    int     result;
    pointer pReadmask;
{
}


static void
vfbAllocateMmappedFramebuffer(pvfb)
    vfbScreenInfoPtr pvfb;
{
#define DUMMY_BUFFER_SIZE 65536
    char dummyBuffer[DUMMY_BUFFER_SIZE];
    int currentFileSize, writeThisTime;

    sprintf(pvfb->mmap_file, "%s/Xvfb_screen%d", pfbdir, pvfb->scrnum);
    if (-1 == (pvfb->mmap_fd = open(pvfb->mmap_file, O_CREAT|O_RDWR, 0666)))
    {
	perror("open");
	ErrorF("open %s failed, errno %d", pvfb->mmap_file, errno);
	return;
    }

    /* Extend the file to be the proper size */

    bzero(dummyBuffer, DUMMY_BUFFER_SIZE);
    for (currentFileSize = 0;
	 currentFileSize < pvfb->sizeInBytes;
	 currentFileSize += writeThisTime)
    {
	writeThisTime = min(DUMMY_BUFFER_SIZE,
			    pvfb->sizeInBytes - currentFileSize);
	if (-1 == write(pvfb->mmap_fd, dummyBuffer, writeThisTime))
	{
	    perror("write");
	    ErrorF("write %s failed, errno %d", pvfb->mmap_file, errno);
	    return;
	}
    }

    /* try to mmap the file */

    pvfb->pXWDHeader = (XWDFileHeader *)mmap((caddr_t)NULL, pvfb->sizeInBytes,
				    PROT_READ|PROT_WRITE,
				    MAP_FILE|MAP_SHARED,
				    pvfb->mmap_fd, 0);
    if (-1 == (int)pvfb->pXWDHeader)
    {
	perror("mmap");
	ErrorF("mmap %s failed, errno %d", pvfb->mmap_file, errno);
	pvfb->pXWDHeader = NULL;
	return;
    }

    if (!RegisterBlockAndWakeupHandlers(vfbBlockHandler, vfbWakeupHandler,
					NULL))
    {
	pvfb->pXWDHeader = NULL;
    }
}
#endif /* HAS_MMAP */


#ifdef HAS_SHM
static void
vfbAllocateSharedMemoryFramebuffer(pvfb)
    vfbScreenInfoPtr pvfb;
{
    /* create the shared memory segment */

    pvfb->shmid = shmget(IPC_PRIVATE, pvfb->sizeInBytes, IPC_CREAT|0777);
    if (pvfb->shmid < 0)
    {
	perror("shmget");
	ErrorF("shmget %d bytes failed, errno %d", pvfb->sizeInBytes, errno);
	return;
    }

    /* try to attach it */

    pvfb->pXWDHeader = (XWDFileHeader *)shmat(pvfb->shmid, 0, 0);
    if (-1 == (int)pvfb->pXWDHeader)
    {
	perror("shmat");
	ErrorF("shmat failed, errno %d", errno);
	pvfb->pXWDHeader = NULL; 
	return;
    }

    ErrorF("screen %d shmid %d\n", pvfb->scrnum, pvfb->shmid);
}
#endif /* HAS_SHM */

static char *
vfbAllocateFramebufferMemory(pvfb)
    vfbScreenInfoPtr pvfb;
{
    if (pvfb->pfbMemory) return pvfb->pfbMemory; /* already done */

    if (pvfb->bitsPerPixel == 1)
	pvfb->sizeInBytes = (pvfb->paddedWidth * pvfb->height);
    else
	pvfb->sizeInBytes = pvfb->paddedWidth * pvfb->height *
			    (pvfb->bitsPerPixel/8);

    /* Calculate how many entries in colormap.  This is rather bogus, because
     * the visuals haven't even been set up yet, but we need to know because we
     * have to allocate space in the file for the colormap.  The number 10
     * below comes from the MAX_PSEUDO_DEPTH define in cfbcmap.c.
     */

    if (pvfb->depth <= 10)
    { /* single index colormaps */
	pvfb->ncolors = 1 << pvfb->depth;
    }
    else
    { /* decomposed colormaps */
	int nplanes_per_color_component = pvfb->depth / 3;
	if (pvfb->depth % 3) nplanes_per_color_component++;
	pvfb->ncolors = 1 << nplanes_per_color_component;
    }

    /* add extra bytes for XWDFileHeader, window name, and colormap */

    pvfb->sizeInBytes += SIZEOF(XWDheader) + XWD_WINDOW_NAME_LEN +
		    pvfb->ncolors * SIZEOF(XWDColor);

    pvfb->pXWDHeader = NULL; 
    switch (fbmemtype)
    {
#ifdef HAS_MMAP
    case MMAPPED_FILE_FB:  vfbAllocateMmappedFramebuffer(pvfb); break;
#endif

#ifdef HAS_SHM
    case SHARED_MEMORY_FB: vfbAllocateSharedMemoryFramebuffer(pvfb); break;
#endif

    case NORMAL_MEMORY_FB:
	pvfb->pXWDHeader = (XWDFileHeader *)Xalloc(pvfb->sizeInBytes);
	break;
    }

    if (pvfb->pXWDHeader)
    {
	pvfb->pXWDCmap = (XWDColor *)((char *)pvfb->pXWDHeader
				+ SIZEOF(XWDheader) + XWD_WINDOW_NAME_LEN);
	pvfb->pfbMemory = (char *)(pvfb->pXWDCmap + pvfb->ncolors);
	return pvfb->pfbMemory;
    }
    else
	return NULL;
}


static void
vfbWriteXWDFileHeader(pScreen)
    ScreenPtr pScreen;
{
    vfbScreenInfoPtr pvfb = &vfbScreens[pScreen->myNum];
    XWDFileHeader *pXWDHeader = pvfb->pXWDHeader;
    char hostname[XWD_WINDOW_NAME_LEN];
    VisualPtr	pVisual;
    unsigned long swaptest = 1;
    int i;

    needswap = *(char *) &swaptest;

    pXWDHeader->header_size = (char *)pvfb->pXWDCmap - (char *)pvfb->pXWDHeader;
    pXWDHeader->file_version = XWD_FILE_VERSION;

    pXWDHeader->pixmap_format = ZPixmap;
    pXWDHeader->pixmap_depth = pvfb->depth;
    pXWDHeader->pixmap_height = pXWDHeader->window_height = pvfb->height;
    pXWDHeader->xoffset = 0;
    pXWDHeader->byte_order = IMAGE_BYTE_ORDER;
    pXWDHeader->bitmap_bit_order = BITMAP_BIT_ORDER;
#ifndef INTERNAL_VS_EXTERNAL_PADDING
    pXWDHeader->pixmap_width = pXWDHeader->window_width = pvfb->width;
    pXWDHeader->bitmap_unit = BITMAP_SCANLINE_UNIT;
    pXWDHeader->bitmap_pad = BITMAP_SCANLINE_PAD;
#else
    pXWDHeader->pixmap_width = pXWDHeader->window_width = pvfb->paddedWidth;
    pXWDHeader->bitmap_unit = BITMAP_SCANLINE_UNIT_PROTO;
    pXWDHeader->bitmap_pad = BITMAP_SCANLINE_PAD_PROTO;
#endif
    pXWDHeader->bits_per_pixel = pvfb->bitsPerPixel;
    pXWDHeader->bytes_per_line = pvfb->paddedWidth;
    pXWDHeader->ncolors = pvfb->ncolors;

    /* visual related fields are written when colormap is installed */

    pXWDHeader->window_x = pXWDHeader->window_y = 0;
    pXWDHeader->window_bdrwidth = 0;

    /* write xwd "window" name: Xvfb hostname:server.screen */

    if (-1 == gethostname(hostname, sizeof(hostname)))
	hostname[0] = 0;
    else
	hostname[XWD_WINDOW_NAME_LEN-1] = 0;
    sprintf((char *)(pXWDHeader+1), "Xvfb %s:%s.%d", hostname, display,
	    pScreen->myNum);

    /* write colormap pixel slot values */

    for (i = 0; i < pvfb->ncolors; i++)
    {
	pvfb->pXWDCmap[i].pixel = i;
    }

    /* byte swap to most significant byte first */

    if (needswap)
    {
	SwapLongs((CARD32 *)pXWDHeader, SIZEOF(XWDheader)/4);
	for (i = 0; i < pvfb->ncolors; i++)
	{
	    register char n;
	    swapl(&pvfb->pXWDCmap[i].pixel, n);
	}
    }
}


static Bool
vfbCursorOffScreen (ppScreen, x, y)
    ScreenPtr   *ppScreen;
    int         *x, *y;
{
    return FALSE;
}

static void
vfbCrossScreen (pScreen, entering)
    ScreenPtr   pScreen;
    Bool        entering;
{
}

static miPointerScreenFuncRec vfbPointerCursorFuncs =
{
    vfbCursorOffScreen,
    vfbCrossScreen,
    miPointerWarpCursor
};

static Bool
vfbScreenInit(index, pScreen, argc, argv)
    int index;
    ScreenPtr pScreen;
    int argc;
    char ** argv;
{
    vfbScreenInfoPtr pvfb = &vfbScreens[index];
    int dpix = 100, dpiy = 100;
    int ret;
    char *pbits;

    pvfb->paddedWidth = PixmapBytePad(pvfb->width, pvfb->depth);
    pvfb->bitsPerPixel = vfbBitsPerPixel(pvfb->depth);
    pbits = vfbAllocateFramebufferMemory(pvfb);
    if (!pbits) return FALSE;

    switch (pvfb->bitsPerPixel)
    {
    case 1:
	ret = mfbScreenInit(pScreen, pbits, pvfb->width, pvfb->height,
			    dpix, dpiy, pvfb->paddedWidth * 8);
	break;
    case 8:
	ret = cfbScreenInit(pScreen, pbits, pvfb->width, pvfb->height,
			    dpix, dpiy, pvfb->paddedWidth);
	break;
    case 16:
	ret = cfb16ScreenInit(pScreen, pbits, pvfb->width, pvfb->height,
			      dpix, dpiy, pvfb->paddedWidth);
	break;
    case 32:
	ret = cfb32ScreenInit(pScreen, pbits, pvfb->width, pvfb->height,
			      dpix, dpiy, pvfb->paddedWidth);
	break;
    default:
	return FALSE;
    }

    if (!ret) return FALSE;

    pScreen->CreateGC = vfbMultiDepthCreateGC;
    pScreen->GetImage = vfbMultiDepthGetImage;
    pScreen->GetSpans = vfbMultiDepthGetSpans;

    pScreen->InstallColormap = vfbInstallColormap;
    pScreen->UninstallColormap = vfbUninstallColormap;
    pScreen->ListInstalledColormaps = vfbListInstalledColormaps;

    pScreen->SaveScreen = vfbSaveScreen;
    pScreen->StoreColors = vfbStoreColors;

    miDCInitialize(pScreen, &vfbPointerCursorFuncs);

    vfbWriteXWDFileHeader(pScreen);

    pScreen->blackPixel = pvfb->blackPixel;
    pScreen->whitePixel = pvfb->whitePixel;

    if (pvfb->bitsPerPixel == 1)
    {
	ret = mfbCreateDefColormap(pScreen);
    }
    else
    {
	ret = cfbCreateDefColormap(pScreen);
    }

    miSetZeroLineBias(pScreen, pvfb->lineBias);

    return ret;

} /* end vfbScreenInit */


void
InitOutput(screenInfo, argc, argv)
    ScreenInfo *screenInfo;
    int argc;
    char **argv;
{
    int i;
    int NumFormats = 0;
    FILE *pf = stderr;

    /* initialize pixmap formats */

    /* must have a pixmap depth to match every screen depth */
    for (i = 0; i < vfbNumScreens; i++)
    {
	vfbPixmapDepths[vfbScreens[i].depth] = TRUE;
    }

    for (i = 1; i <= 32; i++)
    {
	if (vfbPixmapDepths[i])
	{
	    if (NumFormats >= MAXFORMATS)
		FatalError ("MAXFORMATS is too small for this server\n");
	    screenInfo->formats[NumFormats].depth = i;
	    screenInfo->formats[NumFormats].bitsPerPixel = vfbBitsPerPixel(i);
	    screenInfo->formats[NumFormats].scanlinePad = BITMAP_SCANLINE_PAD;
	    NumFormats++;
	}
    }

    screenInfo->imageByteOrder = IMAGE_BYTE_ORDER;
    screenInfo->bitmapScanlineUnit = BITMAP_SCANLINE_UNIT;
    screenInfo->bitmapScanlinePad = BITMAP_SCANLINE_PAD;
    screenInfo->bitmapBitOrder = BITMAP_BIT_ORDER;
    screenInfo->numPixmapFormats = NumFormats;

    /* initialize screens */

    for (i = 0; i < vfbNumScreens; i++)
    {
	if (-1 == AddScreen(vfbScreenInit, argc, argv))
	{
	    FatalError("Couldn't add screen %d", i);
	}
    }

} /* end InitOutput */

#ifdef DPMSExtension
#if NeedFunctionPrototypes
void DPMSSet(CARD16 level)
#else
void DPMSSet(level)
     CARD16 level;
#endif
{
    return;
}

Bool DPMSSupported()
{
    return FALSE;
}
#endif

/* this is just to get the server to link on AIX */
#ifdef AIXV3
int SelectWaitTime = 10000; /* usec */
#endif
