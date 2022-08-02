/* $XConsortium: WrBitF.c,v 1.13 94/04/17 20:21:32 rws Exp $ */
/* $XFree86: xc/lib/X11/WrBitF.c,v 3.1 1996/04/15 11:15:50 dawes Exp $ */
/*

Copyright (c) 1987  X Consortium

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

#include "Xlibint.h"
#include <X11/Xos.h>
#include "Xutil.h"
#include <stdio.h>

#define ERR_RETURN 0

static char *Format_Image(image, resultsize)
XImage *image;
int *resultsize;
{
  register int x, c, b;
  register char *ptr;
  int y;
  char *data;
  int width, height;
  int bytes_per_line;

  width = image->width;
  height = image->height;

  bytes_per_line = (width+7)/8;
  *resultsize = bytes_per_line * height;           /* Calculate size of data */

  data = (char *) Xmalloc( *resultsize );           /* Get space for data */
  if (!data)
    return(ERR_RETURN);

  /*
   * The slow but robust brute force method of converting the image:
   */
  ptr = data;
  c = 0; b=1;
  for (y=0; y<height; y++) {
    for (x=0; x<width;) {
      if (XGetPixel(image, x, y))
	c |= b;
      b <<= 1;
      if (!(++x & 7)) {
	*(ptr++)=c;
	c=0; b=1;
      }
    }
    if (x & 7) {
      *(ptr++)=c;
      c=0; b=1;
    }
  }

  return(data);
}
   
#define BYTES_PER_OUTPUT_LINE 12

#if NeedFunctionPrototypes
int XWriteBitmapFile(
     Display *display,
     _Xconst char *filename,
     Pixmap bitmap,
     unsigned int width,
     unsigned int height,
     int x_hot,
     int y_hot)
#else
int XWriteBitmapFile(display, filename, bitmap, width, height, x_hot, y_hot)
     Display *display;
     char *filename;
     Pixmap bitmap;
     unsigned int width, height;
     int x_hot, y_hot;
#endif
{
  char *data, *ptr;
  int size, byte;
  int c;
  XImage *image;
  FILE *stream;
  char *name;

  if (!(name = strrchr(filename, '/')))
    name = (char *)filename;
  else
    name++;

#ifdef __EMX__
  filename = (char*)__XOS2RedirRoot(filename);
#endif
  if (!(stream = fopen(filename, "w")))
    return(BitmapOpenFailed);

  /* Convert bitmap to an image */
  image = XGetImage(display, bitmap, 0,0,width, height, 1L, XYPixmap);
  if (!image) {
    fclose(stream);
    return(4); /* XXX spec does not say what to return */
  }

  /* Get standard format for data */
  data = Format_Image(image, &size);
  XDestroyImage(image);
  if (!data) {
    fclose(stream);
    return(BitmapNoMemory);
  }

  /* Write out standard header */
  fprintf(stream, "#define %s_width %d\n", name, width);
  fprintf(stream, "#define %s_height %d\n", name, height);
  if (x_hot != -1) {
    fprintf(stream, "#define %s_x_hot %d\n", name, x_hot);
    fprintf(stream, "#define %s_y_hot %d\n", name, y_hot);
  }

  /* Print out the data itself */
  fprintf(stream, "static unsigned char %s_bits[] = {", name);
  for (byte=0, ptr=data; byte<size; byte++, ptr++) {
    if (!byte)
      fprintf(stream, "\n   ");
    else if (!(byte % BYTES_PER_OUTPUT_LINE))
      fprintf(stream, ",\n   ");
    else
      fprintf(stream, ", ");
    c = *ptr;
    if (c<0)
      c += 256;
    fprintf(stream, "0x%02x", c);
  }
  fprintf(stream, "};\n");

  Xfree(data);
  fclose(stream);
  return(BitmapSuccess);
}
