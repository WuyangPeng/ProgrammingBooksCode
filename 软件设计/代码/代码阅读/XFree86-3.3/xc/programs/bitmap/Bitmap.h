/* $XConsortium: Bitmap.h,v 1.12 94/04/17 20:23:40 rws Exp $ */
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


#ifndef _Bitmap_h
#define _Bitmap_h

/****************************************************************
 *
 * Bitmap widget
 *
 ****************************************************************/

#include <X11/Xaw/Simple.h>

/* Resources:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		------------- 
 background	     Background		Pixel		XtDefaultBackground
 foreground          Foredround         Pixel           XtDefaultForeground
 highlight           Highlight          Pixel           XtDefaultForeground
 frame               Frame              Pixel           XtDefaultForeground
 border		     BorderColor	Pixel		XtDefaultForeground
 borderWidth	     BorderWidth	Dimension	1
 mappedWhenManaged   MappedWhenManaged	Boolean		True
 resize              Resize             Boolean         True
 sensitive	     Sensitive		Boolean		True
 width		     Width		Dimension	0
 height		     Height		Dimension	0
 size                Size               String          32x32
 squareWidht         SquareWidht        Dimension       16
 squareHeight        SquareHeight       Dimension       16
 x		     Position		Position	320
 y		     Position		Position	320
 xHot                XHot               Position        NotSet
 yHot                YHot               Position        NotSet
 margin              Margin             Dimension       16
 grid                Grid               Boolean         True
 gridTolerance       GridTolerance      Dimension       8
 dashed              Dashed             Boolean         True
 dashes              Dashes             Bitmap          XtUnspecifiedPixmap
 stippled            Stippled           Boolean         True
 stipple             Sripple            Bitmap          XtUnspecifiedPixmap
 proportional        Proportional       Boolean         True
 axes                Axes               Boolean         True
 button1Function     Button1Function    ButtonFunction  Set  
 button2Function     Button2Function    ButtonFunction  Invert
 button3Function     Button3Function    ButtonFunction  Clear
 button4Function     Button4Function    ButtonFunction  Invert
 button5Function     Button5Function    ButtonFunction  Invert
 filename            Filename           String          None
 basename            Basename           String          None
*/

/* define any special resource names here that are not in <X11/StringDefs.h> */

#define XtNbitmapResource "bitmapResource"
#define XtNstipple "stipple"
#define XtNstippled "stippled"
#define XtNdashes "dashes"
#define XtNdashed "dashed"
#define XtNgrid "grid"
#define XtNgridTolerance "gridTolerance"
#define XtNaxes "axes"
#define XtNbitmapSize "bitmapSize"
#define XtNsize "size"
#define XtNsquareWidth "squareWidth"
#define XtNsquareHeight "squareHeight"
#define XtNxHot "xHot"
#define XtNyHot "yHot"
#define XtNbutton1Function "button1Function"
#define XtNbutton2Function "button2Function"
#define XtNbutton3Function "button3Function"
#define XtNbutton4Function "button4Function"
#define XtNbutton5Function "button5Function"
#define XtNfilename "filename"
#define XtNbasename "basename"
#define XtNmouseForeground "mouseForeground"
#define XtNmouseBackground "mouseBackground"
#define XtNframe "frame"
#define XtNmargin "margin"
#define XtNproportional "proportional"

#define XtCBitmapResource "BitmapResource"
#define XtCHighlight "Highlight"
#define XtCStipple "Stipple"
#define XtCStippled "Stippled"
#define XtCDashes "Dashes"
#define XtCDashed "Dashed"
#define XtCGrid "Grid"
#define XtCGridTolerance "GridTolerance"
#define XtCAxes "Axes"
#define XtBitmapSize "BitmapSize"
#define XtCSize "Size"
#define XtCSquareWidth "SquareWidth"
#define XtCSquareHeight "SquareHeight"
#define XtCXHot "XHot"
#define XtCYHot "YHot"
#define XtCButton1Function "Button1Function"
#define XtCButton2Function "Button2Function"
#define XtCButton3Function "Button3Function"
#define XtCButton4Function "Button4Function"
#define XtCButton5Function "Button5Function"
#define XtCFilename "Filename"
#define XtCBasename "Basename"
#define XtCFrame "Frame"
#ifndef XtCMargin
#define XtCMargin "Margin"
#endif
#define XtCProportional "Proportional"

#define XtRButtonFunction "ButtonFunction"

/* bitmap defines */

#define NotSet   -1
#define Clear     0
#define Set       1
#define Invert    2
#define Highlight 3
#define On        True
#define Off       False

#define XtClear "clear"
#define XtSet "set"
#define XtInvert "invert"

#define MarkRequest "MarkRequest"
#define StoreRequest "StoreRequest"
#define RestoreRequest "RestoreRequest"
#define CopyRequest "CopyRequest"
#define MoveRequest "MoveRequest"
#define PointRequest "PointRequest"
#define LineRequest "LineRequest"
#define CurveRequest "CurveRequest"
#define RectangleRequest "RectangleRequest"
#define FilledRectangleRequest "FilledRectangleRequest"
#define CircleRequest "CircleRequest"
#define FilledCircleRequest "FilledCircleRequest"
#define FloodFillRequest "FloodFillRequest"
#define HotSpotRequest "HotSpotRequest"
#define ZoomInRequest "ZoomInRequest"
#define PasteRequest "PasteRequest"
#define ImmediateCopyRequest "ImmediateCopyRequest"
#define ImmediateMoveRequest "ImmediateMoveRequest"

/* bitmap exports */

extern Boolean BWEngageRequest();
extern Boolean BWTreminateRequest();

extern void BWClearAll();
extern void BWSetAll();
extern void BWInvertAll();
extern void BWUp();
extern void BWDown();
extern void BWLeft();
extern void BWRight();
extern void BWRotateRight();
extern void BWRotateLeft();
extern void BWSwitchGrid();
extern void BWGrid();
extern void BWSwitchDashed();
extern void BWDashed();
extern void BWSwitchAxes();
extern void BWAxes();
extern void BWDrawSquare();
extern void BWDrawLine();
extern void BWDrawRectangle();
extern void BWDrawFilledRectangle();
extern void BWDrawCircle();
extern void BWDrawFilledCircle();
extern void BWFloodFill();
extern void BWMark();
extern void BWMarkAll();
extern void BWUnmark();
extern void BWSelect();
extern void BWUnmark();
extern void BWStore();
extern void BWStoreToBuffer();
extern void BWUndo();
extern void BWResize();
extern void BWClip();
extern void BWUnclip();
extern void BWGrabSelection();
extern void BWRequestSelection();
extern void BWSetChanged();
extern Boolean BWQueryChanged();
extern int BWReadFile();
extern int BWWriteFile();
extern String BWUnparseStatus();
extern String BWGetFilename();
extern String BWGetBasename();
extern void BWChangeBasename();
extern void BWRemoveAllRequests();
extern void BWClearHotSpot();
extern Boolean BWQueryMarked();
extern void BWFold();
extern void BWClear();
extern void BWSet();
extern void BWInvert();
extern void BWFlipHoriz();
extern void BWFlipVert();
extern void BWClearMarked();
extern Boolean BWAddRequest();
extern void BWChangeNotify();
extern Pixmap BWGetUnzoomedPixmap();
extern void BWClearChanged();
extern Boolean BWQueryStored();
extern Boolean BWQueryStippled();
extern void BWSwitchStippled();
extern void BWRedrawMark();
extern Boolean BWQueryAxes();
extern void BWHighlightAxes();
extern void BWChangedFilename();
extern String BWGetFilepath();
extern void BWZoomOut();
extern void BWZoomMarked();
extern void BWRescale();
extern Boolean BWQueryZooming();
extern void BWRedrawGrid();
extern void BWRedrawSquares();
extern void BWRedrawHotSpot();
extern Boolean BWQueryGrid();
extern Boolean BWQueryDashed();
extern Boolean BWQueryProportional();
extern void BWSwitchProportional();
extern void BWDrawGrid();
extern void BWChangeFilename();
extern Boolean BWParseSize();

typedef struct _BWRequestRec BWRequestRec;
typedef char *BWRequest;

/* declare specific BitmapWidget class and instance datatypes */

typedef struct _BitmapClassRec *BitmapWidgetClass;
typedef struct _BitmapRec      *BitmapWidget;
/* declare the class constant */

extern WidgetClass bitmapWidgetClass;

#endif /* _Bitmap_h */


