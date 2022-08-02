/* $XConsortium: BitmapP.h,v 1.13 94/04/17 20:23:41 rws Exp $ */
/*

Copyright (c) 1989  X Consortium

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

/*
 * Author:  Davor Matic, MIT X Consortium
 */



#ifndef _BitmapP_h
#define _BitmapP_h

#include "Bitmap.h"
#include <X11/Xaw/SimpleP.h>

typedef struct {
    Atom           *targets;
    Cardinal        num_targets;
    BWRequestRec   *requests;
    Cardinal        num_requests;
    BWRequestRec   *request[100];
  
} BitmapClassPart;

/* Full class record declaration */
typedef struct _BitmapClassRec {
  CoreClassPart          core_class;
  SimpleClassPart        simple_class;
  BitmapClassPart        bitmap_class;
} BitmapClassRec;

extern BitmapClassRec bitmapClassRec;

/**********/
struct _BWRequestRec {
  char       *name;
  int         status_size;
  void      (*engage)();
  XtPointer   engage_client_data;
  void      (*terminate)();
  XtPointer   terminate_client_data;
  void      (*remove)();
  XtPointer   remove_client_data;
} ;

typedef struct {
  Position from_x, from_y,
           to_x, to_y;
} BWArea;

typedef struct {
    BWRequestRec *request;
    XtPointer     status;
    Boolean       trap;
    XtPointer     call_data;
} BWRequestStack;

typedef struct {
    XImage   *image, *buffer;
    XPoint    hot;
    Position  at_x, at_y;
    Boolean   fold;
    Boolean   grid;
    Boolean   changed;
} BWZoom;

typedef struct {
    Boolean   own;
    Boolean   limbo;
} BWSelection;

/* New fields for the Bitmap widget record */
typedef struct {
  /* resources */
  Pixel            foreground_pixel;
  Pixel            highlight_pixel;
  Pixel            frame_pixel;
  Pixmap           stipple;
  Boolean          stippled;
  Boolean          proportional;
  Boolean          grid;
  Dimension        grid_tolerance;
  Pixmap           dashes;
  Boolean          dashed;
  Boolean          axes;
  Boolean          resize;
  Dimension        margin, squareW, squareH, width, height;
  XPoint           hot;
  int              button_function[5];
  String           filename, basename;
  /* private state */
  String           size;
  Position         horizOffset, vertOffset;
  void           (*notify)();
  BWRequestStack  *request_stack;
  Cardinal         cardinal, current;
  /*Boolean          trapping;*/
  XImage          *image, *buffer, *storage;
  XPoint           buffer_hot;
  BWArea           mark, buffer_mark;
  GC               drawing_gc;
  GC               highlighting_gc;
  GC               frame_gc;
  GC               axes_gc;
  Boolean          changed;
  Boolean          fold;
  Boolean          zooming;
  BWZoom           zoom;
  XtPointer        *value;
  char             status[80];
  BWSelection      selection;
  Boolean          stipple_change_expose_event;
} BitmapPart;

/* Full instance record declaration */
typedef struct _BitmapRec {
  CorePart      core;
  SimplePart    simple;
  BitmapPart    bitmap;
} BitmapRec;

/* Private functions */

#define Length(width, height)\
        (((int)(width) + 7) / 8 * (height))

#define InBitmapX(BW, x)\
	(Position)(min((Position)((Dimension)(max(BW->bitmap.horizOffset,x)  -\
				   BW->bitmap.horizOffset) /\
				   BW->bitmap.squareW), BW->bitmap.width - 1))
    
#define InBitmapY(BW, y)\
	(Position)(min((Position)((Dimension)(max(BW->bitmap.vertOffset, y)  -\
				   BW->bitmap.vertOffset) /\
				   BW->bitmap.squareH), BW->bitmap.height - 1))
    
#define InWindowX(BW, x)\
	(Position) (BW->bitmap.horizOffset + ((x) * BW->bitmap.squareW))

#define InWindowY(BW, y)\
	(Position) (BW->bitmap.vertOffset + ((y) * BW->bitmap.squareH))
     
#define GetPixmap(BW, image)\
    XCreateBitmapFromData(XtDisplay(BW), XtWindow(BW),\
			  image->data, image->width, image->height)


#define QuerySet(x, y) (((x) != NotSet) && ((y) != NotSet))

#define bit int

#define QueryZero(x, y) (((x) == 0) || ((y) == 0))

#define Swap(x, y) {Position t; t = x; x = y; y = t;}

#define QuerySwap(x, y) if(x > y) Swap(x, y)

#define QueryInBitmap(BW, x, y)\
  (((x) >= 0) && ((x) < BW->bitmap.image->width) &&\
   ((y) >= 0) && ((y) < BW->bitmap.image->height))

#define Value(BW, button)   (BW->bitmap.button_function[button - 1])

#define CreateCleanData(length) XtCalloc(length, sizeof(char))
XImage *CreateBitmapImage();
void DestroyBitmapImage();

#endif /* _BitmapP_h */
