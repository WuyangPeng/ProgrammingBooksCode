#include "srgplocal.h"
#include <math.h>
#include <string.h>

#define TURN_OFF_RUBBER_ECHO_IF_ANY \
   SRGP__disableLocatorRubberEcho()

#define TURN_ON_RUBBER_ECHO_IF_ANY \
   SRGP__enableLocatorRubberEcho()




#ifdef THINK_C
static Rect r;

#define DONT_DRAW  -1   /* must match srgp_attrib.c */


#define SET_PORT_FOR_FRAME_GENRE() \
if (srgp__curActiveCanvasSpec.transfermode_frame == DONT_DRAW) return; else { \
   PenMode (srgp__curActiveCanvasSpec.transfermode_frame); \
   PenPat (srgp__curActiveCanvasSpec.pat_frame); }

#define SET_PORT_FOR_FILL_GENRE() \
if (srgp__curActiveCanvasSpec.transfermode_fill == DONT_DRAW) return; else { \
   PenMode (srgp__curActiveCanvasSpec.transfermode_fill); \
   PenPat (srgp__curActiveCanvasSpec.pat_fill); }

#endif



/** Functions creating geometric data
**/

point SRGP_defPoint (int x, int y)
{
   point pt;

   pt.x = x;
   pt.y = y;
   return pt;
}

rectangle SRGP_defRectangle (int left_x, int bottom_y, int right_x, int top_y)
{
   rectangle rect;

   rect.bottom_left.x = left_x;
   rect.bottom_left.y = bottom_y;
   rect.top_right.x = right_x;
   rect.top_right.y = top_y;
   return rect;
}




/** AUDIO
**/

void
SRGP_beep()
{
#ifdef X11
   XBell (srgpx__display, 0);
#endif
#ifdef THINK_C
   SysBeep(30);
#endif
#ifdef _Windows
	MessageBeep(0);
#endif
}





/** POINTS
**/

void
SRGP_pointCoord (int x, int y)
{
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_pointCoord: %d,%d\n", x,y);
	  srgp_check_system_state();
	  LeaveIfNonFatalErr();
   }

   TURN_OFF_RUBBER_ECHO_IF_ANY;
#ifdef X11
   XDrawPoint
	  (srgpx__display,
	   srgp__curActiveCanvasSpec.drawable.xid,
	   srgp__curActiveCanvasSpec.gc_frame,
	   x, FIXED(y));
#endif
#ifdef THINK_C
   SET_PORT_FOR_FRAME_GENRE();
   MoveTo(x,FIXED(y));
   Line(0,0);
#endif

#ifdef _Windows
	{
	HDC hdc;

	hdc = GetDC (srgp__canvasTable[0].drawable.win);
	MoveTo (hdc, x, FIXED(y));
	LineTo (hdc, x+1, FIXED(y));
	ReleaseDC(srgp__canvasTable[0].drawable.win, hdc);
	}
#endif

   TURN_ON_RUBBER_ECHO_IF_ANY;
}

void
SRGP_point (point pt)
{
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_point: %d,%d\n", ExplodePt(pt));
   }

   PUSH_TRACE;
   SRGP_pointCoord (pt.x, pt.y);
   POP_TRACE;
}

void
SRGP_polyPoint (int vertex_count, point *vertices)
{

   register int i;

   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_polyPoint  %d 0x%x\n",
		   vertex_count, vertices);
	  srgp_check_system_state();
	  srgp_check_polymarker_list_size(vertex_count);
	  LeaveIfNonFatalErr();
   }

   TURN_OFF_RUBBER_ECHO_IF_ANY;

#ifdef X11
   for (i=0; i<vertex_count; i++) {
	  Xformat_vertices[i].x = vertices[i].x;
	  Xformat_vertices[i].y = FIXED(vertices[i].y);
   }
   XDrawPoints
	  (srgpx__display,
	   srgp__curActiveCanvasSpec.drawable.xid,
	   srgp__curActiveCanvasSpec.gc_frame,
	   Xformat_vertices, vertex_count, CoordModeOrigin);
#endif

#ifdef THINK_C
   PUSH_TRACE;
   for (i=0; i<vertex_count; i++)
	  SRGP_pointCoord (vertices[i].x, FIXED(vertices[i].y));
   POP_TRACE;
#endif

#ifdef _Windows
   PUSH_TRACE;
   for (i=0; i<vertex_count; i++)
	  SRGP_pointCoord (vertices[i].x, vertices[i].y);
   POP_TRACE;
#endif

   TURN_ON_RUBBER_ECHO_IF_ANY;
}


void
SRGP_polyPointCoord (int vertex_count, int *x_coords, int *y_coords)
{
   register int i;

   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_polyPointCoord  %d 0x%x,0x%x\n",
		  vertex_count, x_coords, y_coords);
	  srgp_check_system_state();
	  srgp_check_polymarker_list_size(vertex_count);
	  LeaveIfNonFatalErr();
   }

   TURN_OFF_RUBBER_ECHO_IF_ANY;

#ifdef X11
   for (i=0; i < vertex_count; i++) {
	  Xformat_vertices[i].x = x_coords[i];
	  Xformat_vertices[i].y = FIXED(y_coords[i]);
   }
   XDrawPoints
	  (srgpx__display,
	   srgp__curActiveCanvasSpec.drawable.xid,
	   srgp__curActiveCanvasSpec.gc_frame,
	   Xformat_vertices, vertex_count, CoordModeOrigin);
#endif

#ifdef THINK_C
   PUSH_TRACE;
   for (i=0; i<vertex_count; i++)
	  SRGP_pointCoord (x_coords[i], FIXED(y_coords[i]));
   POP_TRACE;
#endif

#ifdef _Windows
   PUSH_TRACE;
   for (i=0; i<vertex_count; i++)
	  SRGP_pointCoord (x_coords[i], y_coords[i]);
   POP_TRACE;
#endif

   TURN_ON_RUBBER_ECHO_IF_ANY;
}




/** MARKERS
**/

#ifdef FOO
extern int srgp__marker_radius;  /* found in marker.c */
static int linewidthtemp, saveLineWidth;
#endif

/* <not done> */
static void
GetReadyToPaintMarkers (void)
{
/*
   TURN_OFF_RUBBER_ECHO_IF_ANY;
   PUSH_TRACE;

   srgp__marker_radius = srgp__curActiveCanvasSpec.attributes.marker_size >> 1;

#ifdef THINK_C
   SET_PORT_FOR_FRAME_GENRE();
#endif

   saveLineWidth = srgp__curActiveCanvasSpec.attributes.line_width;
   SRGP_setLineWidth
	  (((linewidthtemp=(srgp__marker_radius>>3))==0)?1:linewidthtemp);
*/
}


/* <not done> */
static void
FinishPaintingMarkers (void)
{
/*
   SRGP_setLineWidth (saveLineWidth);

   POP_TRACE;
   TURN_ON_RUBBER_ECHO_IF_ANY;
*/
}


/* <not done> */
void
SRGP_markerCoord (int x, int y)
{
/*
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_markerCoord: %d,%d\n", x,y);
	  srgp_check_system_state();
	  LeaveIfNonFatalErr();
   }

   GetReadyToPaintMarkers();
   switch (srgp__curActiveCanvasSpec.attributes.marker_style) {
	case MARKER_CIRCLE: SRGP__drawCircleMarker (x,y); break;
	case MARKER_SQUARE: SRGP__drawSquareMarker (x,y); break;
	case MARKER_X: SRGP__drawXMarker (x,y); break;
   }
   FinishPaintingMarkers();
*/
}


/* <not done> */
void
SRGP_marker (point pt)
{
/*
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_marker: %d,%d\n", pt.x, pt.y);
	  srgp_check_system_state();
	  LeaveIfNonFatalErr();
   }

   GetReadyToPaintMarkers();
   switch (srgp__curActiveCanvasSpec.attributes.marker_style) {
	case MARKER_CIRCLE: SRGP__drawCircleMarker (pt.x,pt.y); break;
	case MARKER_SQUARE: SRGP__drawSquareMarker (pt.x,pt.y); break;
	case MARKER_X: SRGP__drawXMarker (pt.x,pt.y); break;
   }
   FinishPaintingMarkers();
*/
}


/* <not done> */
void
SRGP_polyMarker (int vertex_count, point *vertices)
{
/*
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_polyMarker: %d  %lx\n",
		  vertex_count, vertices);
	  srgp_check_polymarker_list_size(vertex_count);
	  srgp_check_system_state();
	  LeaveIfNonFatalErr();
   }

   GetReadyToPaintMarkers();
   while (vertex_count--) {
	  switch (srgp__curActiveCanvasSpec.attributes.marker_style) {
	   case MARKER_CIRCLE:
	 SRGP__drawCircleMarker (vertices->x,vertices->y); break;
	   case MARKER_SQUARE:
	 SRGP__drawSquareMarker (vertices->x,vertices->y); break;
	   case MARKER_X:
	 SRGP__drawXMarker (vertices->x,vertices->y); break;
	  }
	  vertices++;
   }
   FinishPaintingMarkers();
*/
}


/* <not done> */
void
SRGP_polyMarkerCoord (int vertex_count, int *xlist, int *ylist)
{
/*
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_polyMarkerCoord: %d  %lx %lx\n",
		  vertex_count, xlist, ylist);
	  srgp_check_polymarker_list_size(vertex_count);
	  srgp_check_system_state();
	  LeaveIfNonFatalErr();
   }

   GetReadyToPaintMarkers();
   while (vertex_count--) {
	  switch (srgp__curActiveCanvasSpec.attributes.marker_style) {
	   case MARKER_CIRCLE: SRGP__drawCircleMarker (*xlist, *ylist); break;
	   case MARKER_SQUARE: SRGP__drawSquareMarker (*xlist, *ylist); break;
	   case MARKER_X: SRGP__drawXMarker (*xlist, *ylist); break;
	  }
	  xlist++; ylist++;
   }
   FinishPaintingMarkers();
*/
}



/** LINES
X11 handles dashes, etc. itself.
Macintosh & Windows:  we must simulate all line styles other than
continuous.
**/


#ifdef THINK_C
typedef void (*voidfuncptr)();
static int xpresent, ypresent;
static boolean off;


static void plotdash (int x, int y, int s)
{
   int j = s % 10;
   off = (j < 5);
   if ( ! off) {
	  MoveTo (x, y);
	  LineTo (x, y);
   }
}


static void plotdot (int x, int y, int s)
{
   int j = s % 7;
   off = (j < 5);
   if ( ! off ) {
	  MoveTo (x, y);
	  LineTo (x, y);
   }
}



static void plotdotdash (int x, int y, int s)
{
   int j = s % 15;
   off = (j < 4) || ((j > 5) && (j < 9));
   if ( ! off) {
	  MoveTo (x, y);
	  LineTo (x, y);
   }
}


static void LS_MOVETO (int x, int y)   /*Already Mac coordinates*/
{
   xpresent = x;
   ypresent = y;
   MoveTo (xpresent, ypresent);
}


static void LS_LINETO_difficult
   (int xnew, int ynew,
	voidfuncptr plot_with_line_style)
{
   register long_step, short_step, ax, di, bp, si, temp, x, y;

   long_step = 1;
   short_step = 1;
   bp = xnew - xpresent;
   if (bp < 0)
	  {
	 long_step = -1;
	 bp = -bp;
	  };
   ax = ynew - ypresent;
   if (ax < 0)
	  {
	 short_step = -1;
	 ax = -ax;
	  };
   x = xpresent;
   y = ypresent;
   if (ax <= bp)
	  {
	 di = bp>>1;
	 si = 0;
	 do {
		plot_with_line_style (x, y, si);
		x += long_step;
		di += ax;
		if (di >= bp)
		   {
		  di -= bp;
		  y += short_step;
		   }
	 }
	 while ((++si) <= bp);
	  }
   else
	  {
	 temp = ax;
	 ax = bp;
	 bp = temp;
	 temp = short_step;
	 short_step = long_step;
	 long_step = temp;
	 di = (bp>>1);
	 si = 0;
	 do {
		plot_with_line_style (x, y, si);
		y += long_step;
		di += ax;
		if (di >= bp)
		   {
		  di -= bp;
		  x += short_step;
		   }
	 }
	 while ((++si) <= bp);
	  }
};


static void LS_LINETO (int xnew, int ynew)
{
   if (srgp__curActiveCanvasSpec.attributes.line_style == CONTINUOUS)
	  LineTo (xnew, ynew);
   else {
	  if (xnew == xpresent)
	 PenSize (srgp__curActiveCanvasSpec.attributes.line_width, 1);
	  else if (ynew == ypresent)
	 PenSize (1, srgp__curActiveCanvasSpec.attributes.line_width);
	  else if (abs(ynew - ypresent) < abs(xnew - xpresent))
	 PenSize (1, srgp__curActiveCanvasSpec.attributes.line_width);
	  else
	 PenSize (srgp__curActiveCanvasSpec.attributes.line_width, 1);

	  switch (srgp__curActiveCanvasSpec.attributes.line_style) {
	   case DASHED:
	 LS_LINETO_difficult (xnew, ynew, plotdash); break;
	   case DOTTED:
	 LS_LINETO_difficult (xnew, ynew, plotdot); break;
	   case DOT_DASHED:
	 LS_LINETO_difficult (xnew, ynew, plotdotdash); break;
	  }
   }
   xpresent = xnew;
   ypresent = ynew;
}

#endif

#ifdef _Windows
typedef void (*voidfuncptr)();
static int xpresent, ypresent;
static boolean off;


static void plotdash (HDC hdc, int x, int y, int s)
{
   int j = s % 10;
   off = (j < 5);
   if (off)
	  MoveTo (hdc, x, y);
   else
	  LineTo (hdc, x, y);
}


static void plotdot (HDC hdc, int x, int y, int s)
{
   int j = s % 7;
   off = (j < 5);
   if (off)
	  MoveTo (hdc, x, y);
   else
	  LineTo (hdc, x, y);
}



static void plotdotdash (HDC hdc, int x, int y, int s)
{
   int j = s % 15;
   off = (j < 4) || ((j > 5) && (j < 9));
   if (off)
	  MoveTo (hdc, x, y);
   else
	  LineTo (hdc, x, y);
}


static void LS_MOVETO (HDC hdc, int x, int y)   /*Already Win coordinates*/
{
   xpresent = x;
   ypresent = y;
   MoveTo (hdc, xpresent, ypresent);
}


static void LS_LINETO_difficult
   (HDC hdc, int xnew, int ynew,
	voidfuncptr plot_with_line_style)
{
   register long_step, short_step, ax, di, bp, si, temp, x, y;

   long_step = 1;
   short_step = 1;
   bp = xnew - xpresent;
   if (bp < 0)
	  {
	 long_step = -1;
	 bp = -bp;
	  };
   ax = ynew - ypresent;
   if (ax < 0)
	  {
	 short_step = -1;
	 ax = -ax;
	  };
   x = xpresent;
   y = ypresent;
   if (ax <= bp)
	  {
	 di = bp>>1;
	 si = 0;
	 do {
		plot_with_line_style (hdc, x, y, si);
		x += long_step;
		di += ax;
		if (di >= bp)
		   {
		  di -= bp;
		  y += short_step;
		   }
	 }
	 while ((++si) <= bp);
	  }
   else
	  {
	 temp = ax;
	 ax = bp;
	 bp = temp;
	 temp = short_step;
	 short_step = long_step;
	 long_step = temp;
	 di = (bp>>1);
	 si = 0;
	 do {
		plot_with_line_style (hdc, x, y, si);
		y += long_step;
		di += ax;
		if (di >= bp)
		   {
		  di -= bp;
		  x += short_step;
		   }
	 }
	 while ((++si) <= bp);
	  }
};


static void LS_LINETO (HDC hdc, int xnew, int ynew)
{
   if (srgp__curActiveCanvasSpec.attributes.line_style == CONTINUOUS)
	  LineTo (hdc, xnew, ynew);
   else {
	  switch (srgp__curActiveCanvasSpec.attributes.line_style) {
	   case DASHED:
	 LS_LINETO_difficult (hdc, xnew, ynew, plotdash); break;
	   case DOTTED:
	 LS_LINETO_difficult (hdc, xnew, ynew, plotdot); break;
	   case DOT_DASHED:
	 LS_LINETO_difficult (hdc, xnew, ynew, plotdotdash); break;
	  }
   }
   xpresent = xnew;
   ypresent = ynew;
}

#endif

void
SRGP_lineCoord (int x1, int y1, int x2, int y2)
{
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_lineCoord: %d,%d --> %d,%d\n", x1,y1,x2,y2);
	  srgp_check_system_state();
	  LeaveIfNonFatalErr();
   }

   TURN_OFF_RUBBER_ECHO_IF_ANY;
#ifdef X11
   XDrawLine
	  (srgpx__display,
	   srgp__curActiveCanvasSpec.drawable.xid,
	   srgp__curActiveCanvasSpec.gc_frame,
	   x1, FIXED(y1), x2, FIXED(y2));
#endif
#ifdef THINK_C
   SET_PORT_FOR_FRAME_GENRE();
   LS_MOVETO (x1,FIXED(y1));
   LS_LINETO (x2,FIXED(y2));
#endif
#ifdef _Windows
	{
	HDC hdc;

	hdc = GetDC (srgp__canvasTable[0].drawable.win);
	LS_MOVETO (hdc,x1,FIXED(y1));
	LS_LINETO (hdc,x2,FIXED(y2));
	SRGP_pointCoord (x2, y2);
	ReleaseDC(srgp__canvasTable[0].drawable.win,hdc);
	}
#endif
   TURN_ON_RUBBER_ECHO_IF_ANY;
}

void
SRGP_line (point pt1, point pt2)
{
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_line: %d,%d --> %d,%d\n", ExplodePt(pt1), ExplodePt(pt2));
   }

   PUSH_TRACE;
   SRGP_lineCoord (pt1.x, pt1.y,  pt2.x, pt2.y);
   POP_TRACE;
}



/** RECTANGLES
**/

void
SRGP_rectangleCoord (int left_x, int bottom_y, int right_x, int top_y)
{
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_rectangleCoord: (%d,%d)->(%d,%d)\n",
		  left_x, bottom_y, right_x, top_y);
	  srgp_check_system_state();
	  srgp_check_rectangle (left_x, bottom_y, right_x, top_y);
	  LeaveIfNonFatalErr();
   }
   TURN_OFF_RUBBER_ECHO_IF_ANY;
#ifdef X11
   XDrawRectangle
	  (srgpx__display,
	   srgp__curActiveCanvasSpec.drawable.xid,
	   srgp__curActiveCanvasSpec.gc_frame,
	   left_x, FIXED(top_y),
	   (right_x-left_x),
	   (top_y-bottom_y));
#endif
#ifdef THINK_C
   SET_PORT_FOR_FRAME_GENRE();
   r = FIXED_RECT(left_x, bottom_y, right_x, top_y);
   if (srgp__curActiveCanvasSpec.attributes.line_style == CONTINUOUS)
	  FrameRect (&r);
   else {
	  r.bottom -= srgp__curActiveCanvasSpec.attributes.line_width;
	  r.right -= srgp__curActiveCanvasSpec.attributes.line_width;
	  LS_MOVETO (r.left, r.bottom);
	  LS_LINETO (r.right, r.bottom);
	  LS_LINETO (r.right, r.top);
	  LS_LINETO (r.left, r.top);
	  LS_LINETO (r.left, r.bottom);
   }
#endif
#ifdef _Windows
	{
	HDC hdc;
	HBRUSH hBrush;

	hdc = GetDC (srgp__canvasTable[0].drawable.win);
	hBrush = SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
	Rectangle(hdc, left_x, FIXED(top_y), right_x+1, FIXED(bottom_y)+1);
	DeleteObject(SelectObject(hdc,hBrush));
	ReleaseDC(srgp__canvasTable[0].drawable.win, hdc);
	}
#endif
   TURN_ON_RUBBER_ECHO_IF_ANY;
}

void
SRGP_rectangle (rectangle rect)
{
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_rectangle: (%d,%d)->(%d,%d)\n", ExplodeRect(rect));
   }

   PUSH_TRACE;
   SRGP_rectangleCoord
	  (rect.bottom_left.x, rect.bottom_left.y,
	   rect.top_right.x, rect.top_right.y);
   POP_TRACE;
}

void
SRGP_rectanglePt (point bottom_left, point top_right)
{
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_rectanglePt: (%d,%d)->(%d,%d)\n",
		  ExplodePt(bottom_left), ExplodePt(top_right));
   }

   PUSH_TRACE;
   SRGP_rectangleCoord
	  (bottom_left.x, bottom_left.y,
	   top_right.x, top_right.y);
   POP_TRACE;
}


/** FRAMED POLYGONS
**/

void
SRGP_polyLine (int vertex_count, point *vertices)
{
   register int i;

   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_polyLine  %d 0x%x\n", vertex_count, vertices);
	  srgp_check_system_state();
	  srgp_check_polyline_list_size(vertex_count);
	  LeaveIfNonFatalErr();
   }

   TURN_OFF_RUBBER_ECHO_IF_ANY;
#ifdef X11
   for (i=0; i < vertex_count; i++) {
	  Xformat_vertices[i].x = vertices[i].x;
	  Xformat_vertices[i].y = FIXED(vertices[i].y);
   }
   XDrawLines
	  (srgpx__display,
	   srgp__curActiveCanvasSpec.drawable.xid,
	   srgp__curActiveCanvasSpec.gc_frame,
	   Xformat_vertices, vertex_count, CoordModeOrigin);
#endif
#ifdef THINK_C
   SET_PORT_FOR_FRAME_GENRE();
   LS_MOVETO (vertices[0].x, FIXED(vertices[0].y));
   for (i=1; i < vertex_count; i++)
	  LS_LINETO (vertices[i].x, FIXED(vertices[i].y));
#endif
#ifdef _Windows
	{
	HDC hdc;

	hdc = GetDC (srgp__canvasTable[0].drawable.win);
	MoveTo(hdc, vertices[0].x, FIXED(vertices[0].y));
	for (i=1; i< vertex_count; i++)
		LineTo (hdc, vertices[i].x, FIXED(vertices[i].y));
	ReleaseDC(srgp__canvasTable[0].drawable.win, hdc);
	}
#endif
   TURN_ON_RUBBER_ECHO_IF_ANY;
}


void
SRGP_polyLineCoord (int vertex_count, int *x_coords, int *y_coords)
{
   register int i;

   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_polyLineCoord  %d 0x%x,0x%x\n",
		  vertex_count, x_coords, y_coords);
	  srgp_check_system_state();
	  srgp_check_polyline_list_size(vertex_count);
	  LeaveIfNonFatalErr();
   }

   TURN_OFF_RUBBER_ECHO_IF_ANY;
#ifdef X11
   for (i=0; i < vertex_count; i++) {
	  Xformat_vertices[i].x = x_coords[i];
	  Xformat_vertices[i].y = FIXED(y_coords[i]);
   }
   XDrawLines
	  (srgpx__display,
	   srgp__curActiveCanvasSpec.drawable.xid,
	   srgp__curActiveCanvasSpec.gc_frame,
	   Xformat_vertices, vertex_count, CoordModeOrigin);
#endif
#ifdef THINK_C
   SET_PORT_FOR_FRAME_GENRE();
   LS_MOVETO (x_coords[0], FIXED(y_coords[0]));
   for (i=1; i < vertex_count; i++)
	  LS_LINETO (x_coords[i], FIXED(y_coords[i]));
#endif
#ifdef _Windows
	{
	HDC hdc;

	hdc = GetDC (srgp__canvasTable[0].drawable.win);
	MoveTo(hdc, x_coords[0], FIXED(y_coords[0]));
	for (i=1; i< vertex_count; i++)
		LineTo (hdc, x_coords[i], FIXED(y_coords[i]));
	ReleaseDC(srgp__canvasTable[0].drawable.win, hdc);
	}
#endif
   TURN_ON_RUBBER_ECHO_IF_ANY;
}


void
SRGP_polygon (int vertex_count, point *vertices)
{
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_polygon  %d 0x%x\n",
		  vertex_count, vertices);
	  srgp_check_system_state();
	  srgp_check_polygon_list_size(vertex_count);
	  LeaveIfNonFatalErr();
   }

   PUSH_TRACE;
   SRGP_polyLine (vertex_count, vertices);
   /* draw the line between the first vertex and the last vertex */
   SRGP_line (vertices[0], vertices[vertex_count-1]);
   POP_TRACE;
}


void
SRGP_polygonCoord (int vertex_count, int *x_coords, int *y_coords)
{
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_polygonCoord  %d 0x%d,0x%d\n",
		  vertex_count, x_coords, y_coords);
	  srgp_check_system_state();
	  srgp_check_polygon_list_size(vertex_count);
	  LeaveIfNonFatalErr();
   }

   PUSH_TRACE;
   SRGP_polyLineCoord (vertex_count, x_coords, y_coords);
   /* draw the line between the first vertex and the last vertex */
   SRGP_lineCoord
	  (x_coords[0], y_coords[0],
	   x_coords[vertex_count-1], y_coords[vertex_count-1]);
   POP_TRACE;
}



/** FILLED RECTANGLES AND POLYGONS
**/

void
SRGP_fillRectangleCoord (int left_x, int bottom_y, int right_x, int top_y)
{
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_fillRectangleCoord (%d,%d)->(%d,%d)\n",
		  left_x, bottom_y, right_x, top_y);
	  srgp_check_system_state();
	  srgp_check_rectangle(left_x, bottom_y, right_x, top_y);
	  LeaveIfNonFatalErr();
   }


   TURN_OFF_RUBBER_ECHO_IF_ANY;
#ifdef X11
   XFillRectangle
	  (srgpx__display,
	   srgp__curActiveCanvasSpec.drawable.xid,
	   srgp__curActiveCanvasSpec.gc_fill,
	   left_x, FIXED(top_y),
	   (right_x-left_x+1), (top_y-bottom_y+1));
#endif
#ifdef THINK_C
   SET_PORT_FOR_FILL_GENRE();
   r = FIXED_RECT(left_x, bottom_y, right_x, top_y);
   if (srgp__curActiveCanvasSpec.attributes.fill_style == PIXMAP_PATTERN)
	  FillCRect
		 (&r,
		  srgp__pixmapPatternTable
			 [srgp__curActiveCanvasSpec.attributes.fill_pixmap_pattern_id]);
   else
   PaintRect (&r);
#endif
#ifdef _Windows
	{
	HDC hdc;

	hdc = GetDC (srgp__canvasTable[0].drawable.win);
	Rectangle(hdc, left_x, FIXED(top_y), right_x+1, FIXED(bottom_y)+1);
	ReleaseDC(srgp__canvasTable[0].drawable.win, hdc);
	}
#endif
   TURN_ON_RUBBER_ECHO_IF_ANY;
}

void
SRGP_fillRectangle (rectangle rect)
{
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_fillRectangle (%d,%d)->(%d,%d)\n",
		  ExplodeRect(rect));
   }

   PUSH_TRACE;
   SRGP_fillRectangleCoord
	  (rect.bottom_left.x, rect.bottom_left.y,
	   rect.top_right.x, rect.top_right.y);
   POP_TRACE;
}

void
SRGP_fillRectanglePt (point bottom_left, point top_right)
{
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_fillRectanglePt (%d,%d)->(%d,%d)\n",
		  ExplodePt(bottom_left), ExplodePt(top_right));
   }

   PUSH_TRACE;
   SRGP_fillRectangleCoord
	  (bottom_left.x, bottom_left.y,
	   top_right.x, top_right.y);
   POP_TRACE;
}


void
SRGP_fillPolygon (int vertex_count, point *vertices)
{
   register int i;
#ifdef THINK_C
   PolyHandle p;
#endif

   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_fillPolygon:  %d  0x%x\n",
		  vertex_count, vertices);
	  srgp_check_system_state();
	  srgp_check_polygon_list_size(vertex_count);
	  LeaveIfNonFatalErr();
   }

   TURN_OFF_RUBBER_ECHO_IF_ANY;

#ifdef X11
   for (i=0; i < vertex_count; i++) {
	  Xformat_vertices[i].x = vertices[i].x;
	  Xformat_vertices[i].y = FIXED(vertices[i].y);
   }
   XFillPolygon
	  (srgpx__display,
	   srgp__curActiveCanvasSpec.drawable.xid,
	   srgp__curActiveCanvasSpec.gc_fill,
	   Xformat_vertices, vertex_count, Complex, CoordModeOrigin);
#endif

#ifdef THINK_C
   p = OpenPoly();
   MoveTo (vertices[0].x, FIXED(vertices[0].y));
   for (i=1; i < vertex_count; i++)
	  LineTo (vertices[i].x, FIXED(vertices[i].y));
   ClosePoly ();
   if (srgp__curActiveCanvasSpec.attributes.fill_style == PIXMAP_PATTERN)
	  FillCPoly
		 (p,
		  srgp__pixmapPatternTable
			 [srgp__curActiveCanvasSpec.attributes.fill_pixmap_pattern_id]);
   else {
	  SET_PORT_FOR_FILL_GENRE();
	  PaintPoly (p);
   }
   KillPoly (p);
#endif
#ifdef _Windows
	{
	HDC hdc;
	LPPOINT WinCoords;
	int i;

	WinCoords = (POINT *) SRGP_malloc(2 * vertex_count * sizeof(int));
	for (i=0; i<vertex_count; i++) {
		WinCoords[i].x = vertices[i].x;
		WinCoords[i].y = FIXED(vertices[i].y);
	}
	hdc = GetDC (srgp__canvasTable[0].drawable.win);
	Polygon(hdc, WinCoords, vertex_count);
	ReleaseDC(srgp__canvasTable[0].drawable.win, hdc);
	SRGP_free (WinCoords);
	}
#endif
   TURN_ON_RUBBER_ECHO_IF_ANY;
}


void
SRGP_fillPolygonCoord (int vertex_count, int *x_coords, int *y_coords)
{
   register int i;
#ifdef THINK_C
   PolyHandle p;
#endif

   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_fillPolygonCoord:  %d  0x%x,0x%x\n",
		  vertex_count, x_coords, y_coords);
	  srgp_check_system_state();
	  srgp_check_polygon_list_size(vertex_count);
	  LeaveIfNonFatalErr();
   }

   TURN_OFF_RUBBER_ECHO_IF_ANY;

#ifdef X11
   for (i=0; i < vertex_count; i++) {
	  Xformat_vertices[i].x = x_coords[i];
	  Xformat_vertices[i].y = FIXED(y_coords[i]);
   }
   XFillPolygon
	  (srgpx__display,
	   srgp__curActiveCanvasSpec.drawable.xid,
	   srgp__curActiveCanvasSpec.gc_fill,
	   Xformat_vertices, vertex_count, Complex, CoordModeOrigin);
#endif

#ifdef THINK_C
   p = OpenPoly();
   MoveTo (x_coords[0], FIXED(y_coords[0]));
   for (i=1; i < vertex_count; i++)
	  LineTo (x_coords[i], FIXED(y_coords[i]));
   ClosePoly ();
   if (srgp__curActiveCanvasSpec.attributes.fill_style == PIXMAP_PATTERN)
	  FillCPoly
		 (p,
		  srgp__pixmapPatternTable
			 [srgp__curActiveCanvasSpec.attributes.fill_pixmap_pattern_id]);
   else {
	  SET_PORT_FOR_FILL_GENRE();
	  PaintPoly (p);
   }
   KillPoly (p);
#endif

#ifdef _Windows
	{
	HDC hdc;
	LPPOINT WinCoords;
	int i;

	WinCoords = (POINT *) SRGP_malloc(2 * vertex_count * sizeof(int));
	for (i=0; i<vertex_count; i++) {
		WinCoords[i].x = x_coords[i];
		WinCoords[i].y = FIXED(y_coords[i]);
	}
	hdc = GetDC (srgp__canvasTable[0].drawable.win);
	Polygon(hdc, WinCoords, vertex_count);
	ReleaseDC(srgp__canvasTable[0].drawable.win, hdc);
	SRGP_free (WinCoords);
	}
#endif

   TURN_ON_RUBBER_ECHO_IF_ANY;
}



/** ELLIPSES
**/

#ifdef X11
static int xangle1, xangle2;

ComputeXangles (double start, double end)
{
   if (start <= end) {
	  xangle1 = (int)(start*64);
	  xangle2 = (int)((end-start)*64);
   }
   else {
	  xangle1 = (int) (end*64);
	  xangle2 = (int) ((start-360.0-end)*64);
   }
}
#endif

#ifdef _Windows
static point startPoint, endPoint;

point ComputeWinArcEnds (double angle, rectangle bounding_rect)
{
	point end;
	double temp;

	int halfWidth = (bounding_rect.top_right.x - bounding_rect.bottom_left.x)/2;
	int halfHeight = (bounding_rect.top_right.y - bounding_rect.bottom_left.y + 1)/2;


	if ((angle==90)||(angle==270)) {
		end.x = bounding_rect.bottom_left.x + halfWidth;
		if (angle==90)
			end.y = bounding_rect.top_right.y;
		else end.y = bounding_rect.bottom_left.y;
	}
	else {
		if ((angle>90)&&(angle<270))
			end.x = -halfWidth*100;
		else end.x = halfWidth*100;
		temp = ((double)end.x) * tan((2*3.141592654*angle)/360);
		end.y = bounding_rect.bottom_left.y + halfHeight + (int) temp;
		end.x = bounding_rect.bottom_left.x + halfWidth + end.x;
	}
	return end;
}
#endif

void
SRGP_ellipseArc (rectangle bounding_rect, double start, double end)
{
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_ellipseArc:  (%d,%d)->(%d,%d) (%f)->(%f)\n",
		  ExplodeRect(bounding_rect), start, end);
	  srgp_check_system_state();
	  srgp_check_rectangle
	 (bounding_rect.bottom_left.x, bounding_rect.bottom_left.y,
	  bounding_rect.top_right.x, bounding_rect.top_right.y);
	  LeaveIfNonFatalErr();
   }

   TURN_OFF_RUBBER_ECHO_IF_ANY;
#ifdef X11
   ComputeXangles (start, end);
   XDrawArc
	  (srgpx__display,
	   srgp__curActiveCanvasSpec.drawable.xid,
	   srgp__curActiveCanvasSpec.gc_frame,
	   bounding_rect.bottom_left.x, FIXED(bounding_rect.top_right.y),
	   (bounding_rect.top_right.x - bounding_rect.bottom_left.x),
	   (bounding_rect.top_right.y - bounding_rect.bottom_left.y),
	   xangle1, xangle2);
#endif
#ifdef THINK_C
   SetRect (&r, bounding_rect.bottom_left.x, FIXED(bounding_rect.top_right.y),
		bounding_rect.top_right.x, FIXED(bounding_rect.bottom_left.y));
   SET_PORT_FOR_FRAME_GENRE();
   FrameArc (&r, (int)(90 - start), (int)(-(end+((start>end)?360:0) - start)));
#endif
#ifdef _Windows
	{
	HDC   hdc;

    if (start != end) {
		startPoint = ComputeWinArcEnds(start, bounding_rect);
		endPoint = ComputeWinArcEnds(end, bounding_rect);
		hdc = GetDC (srgp__canvasTable[0].drawable.win);
		Arc(hdc, bounding_rect.bottom_left.x, FIXED(bounding_rect.top_right.y),
			bounding_rect.top_right.x+1, FIXED(bounding_rect.bottom_left.y)+1,
			startPoint.x, FIXED(startPoint.y),
			endPoint.x, FIXED(endPoint.y));
		ReleaseDC(srgp__canvasTable[0].drawable.win, hdc);
    }
	}
#endif

   TURN_ON_RUBBER_ECHO_IF_ANY;
}


void
SRGP_ellipse (rectangle bounding_rect)
{
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_ellipse:  (%d,%d)->(%d,%d)\n",
		  ExplodeRect(bounding_rect));
	  srgp_check_system_state();
	  srgp_check_rectangle
	 (bounding_rect.bottom_left.x, bounding_rect.bottom_left.y,
	  bounding_rect.top_right.x, bounding_rect.top_right.y);
	  LeaveIfNonFatalErr();
   }

   PUSH_TRACE;
   SRGP_ellipseArc (bounding_rect, 0.0, 360.0);
   POP_TRACE;
}



void
SRGP_fillEllipseArc (rectangle bounding_rect, double start, double end)
{
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_fillEllipseArc:  (%d,%d)->(%d,%d)\n",
		  ExplodeRect(bounding_rect));
	  srgp_check_system_state();
	  srgp_check_rectangle
	 (bounding_rect.bottom_left.x, bounding_rect.bottom_left.y,
	  bounding_rect.top_right.x, bounding_rect.top_right.y);
	  LeaveIfNonFatalErr();
   }

   TURN_OFF_RUBBER_ECHO_IF_ANY;
#ifdef X11
   ComputeXangles (start, end);
   XFillArc
	  (srgpx__display,
	   srgp__curActiveCanvasSpec.drawable.xid,
	   srgp__curActiveCanvasSpec.gc_fill,
	   bounding_rect.bottom_left.x, FIXED(bounding_rect.top_right.y),
	   (bounding_rect.top_right.x - bounding_rect.bottom_left.x),
	   (bounding_rect.top_right.y - bounding_rect.bottom_left.y),
	   xangle1, xangle2);
#endif

#ifdef THINK_C
   SetRect (&r, bounding_rect.bottom_left.x, FIXED(bounding_rect.top_right.y),
		bounding_rect.top_right.x, FIXED(bounding_rect.bottom_left.y));
   if (srgp__curActiveCanvasSpec.attributes.fill_style == PIXMAP_PATTERN)
	  FillCArc (&r, (int)(90 - start), (int)(-(end+((start>end)?360:0) - start)),
				srgp__pixmapPatternTable
				   [srgp__curActiveCanvasSpec.attributes.fill_pixmap_pattern_id]);
   else {
	  SET_PORT_FOR_FILL_GENRE();
	  PaintArc (&r, (int)(90 - start), (int)(-(end+((start>end)?360:0) - start)));
   }
#endif
#ifdef _Windows
	{
	HDC hdc;

    if (start != end) {
		startPoint = ComputeWinArcEnds(start, bounding_rect);
		endPoint = ComputeWinArcEnds(end, bounding_rect);
		hdc = GetDC (srgp__canvasTable[0].drawable.win);
		Pie(hdc, bounding_rect.bottom_left.x, FIXED(bounding_rect.top_right.y),
			bounding_rect.top_right.x+1, FIXED(bounding_rect.bottom_left.y)+1,
			startPoint.x, FIXED(startPoint.y), endPoint.x, FIXED(endPoint.y));
		ReleaseDC(srgp__canvasTable[0].drawable.win, hdc);
	}
	}
#endif

   TURN_ON_RUBBER_ECHO_IF_ANY;
}


void
SRGP_fillEllipse (rectangle bounding_rect)
{
   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_fillEllipse:  (%d,%d)->(%d,%d)\n",
		  ExplodeRect(bounding_rect));
	  srgp_check_system_state();
	  srgp_check_rectangle
	 (bounding_rect.bottom_left.x, bounding_rect.bottom_left.y,
	  bounding_rect.top_right.x, bounding_rect.top_right.y);
	  LeaveIfNonFatalErr();
   }

   PUSH_TRACE;
   SRGP_fillEllipseArc (bounding_rect, 0.0, 360.0);
   POP_TRACE;
}



/** TEXT
X11 implementation notes:
   Unfortunately, we don't keep a GC around just for text.
   Neither the frame nor the fill GC are necessarily correct for text;
   text is always drawn in SOLID style.

   Basically, if we find that the frame GC currently has a non-solid X-fill-style,
   we temporarily change the frame GC's X-fill-style to SOLID and then restore.

   This could be woefully inefficient if the application is indeed using
   a non-solid pen-style!
**/

void
SRGP_text (point origin, char *str)
{
#ifdef X11
   boolean restoration_needed = FALSE;
#endif

   DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_text:  %d,%d  %s\n",
		  origin.x, origin.y, str);
	  srgp_check_system_state();
	  LeaveIfNonFatalErr();
   }

   TURN_OFF_RUBBER_ECHO_IF_ANY;

#ifdef X11
   if (srgp__curActiveCanvasSpec.attributes.pen_style != SOLID) {
	  restoration_needed = TRUE;
	  XSetFillStyle (srgpx__display,
			 srgp__curActiveCanvasSpec.gc_frame, SOLID);
   }

   XDrawString
	  (srgpx__display,
	   srgp__curActiveCanvasSpec.drawable.xid,
	   srgp__curActiveCanvasSpec.gc_frame,
	   origin.x, FIXED(origin.y), str, strlen(str));

   if (restoration_needed)
	  XSetFillStyle (srgpx__display,
			 srgp__curActiveCanvasSpec.gc_frame,
			 srgp__curActiveCanvasSpec.attributes.pen_style);
#endif

#ifdef THINK_C
   PenPat(black);
   CtoPstr(str);
   MoveTo (origin.x, FIXED(origin.y));
   DrawString (str);
   PtoCstr(str);
#endif

#ifdef _Windows
	{
	HDC     hdc;

	hdc = GetDC (srgp__canvasTable[0].drawable.win);
	TextOut (hdc, origin.x, FIXED(origin.y), str, strlen(str));
	ReleaseDC(srgp__canvasTable[0].drawable.win, hdc);
	}
#endif
   TURN_ON_RUBBER_ECHO_IF_ANY;
}
