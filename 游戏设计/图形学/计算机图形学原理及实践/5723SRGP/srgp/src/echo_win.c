#include "srgplocal.h"

/** INFORMATION ABOUT THE LOW-LEVEL ECHOING DRIVERS

SRGP__initEchoModule ()
   Must be called once, during initialization.
   The echo-attribute globals must have already been given
      default initial values!

SRGP__updateLocatorRubberAnchor ()
   Acesses current locator rubber anchor from globals.
   May be called whether rubber echo is active or not.

SRGP__enableLocatorRubberEcho ()
   Accesses current locator measure info from global variables.
   May be called carelessly:
      1) Will not re-enable if already enabled
      2) Will refuse to enable echo for a device that is:
	  A) not active currently, and 
	  B) not in a state for which echo is desired

SRGP__updateLocatorRubberEcho ()
   Accesses current locator measure info from global variables.
   May be called carelessly:
      Will not update if device is currently disabled.

SRGP__disableLocatorRubberEcho ()
   May be called carelessly:
      Will not re-disable if already disabled


SRGP__updateLocatorCursorShape ()
   May be called whether or not the cursor echo is active.

SRGP__enableLocatorCursorEcho ()
SRGP__disableLocatorCursorEcho ()
	  May be called carelessly.

SRGP__updateRawCursorPosition ()
	  Accesses cur_locator_measure from global variables.
	  Informs the underlying graphics package of the desired "cursor warp".
	  Automatically updates any type of locator echo: cursor or rubber.


SRGP__updateKeyboardEchoAttributes ()
   May be called whether or not key echo is active.
   Obtains attributes from global variables.

SRGP__enableKeyboardEcho ()
SRGP__updateKeyboardEcho ()
SRGP__disableKeyboardEcho ()
	  Similar to above: may be called carelessly.

**/

/* FOR LOCATOR ECHO */
static boolean locator_echo_is_active=FALSE;
/*
static GC echo__locator_gc;
*/
static HCURSOR echo__locator_cursor_shape;

static point echo__locator_rubber_anchor, echo__locator_previous_position;
	 /* IN windows, not SRGP, COORDS */

/* FOR KEYBOARD ECHO */
static boolean keyboard_echo_is_active=FALSE;
/*
static GC echo__keyboard_gc;
static XFontStruct *echo__keyboard_font;
*/
static int
	/* THE SCREEN LOCATION OF THE ECHO IN windows's COORDINATE SYSTEM!
	 */
	echo__keyboard_left,   /* X */
	echo__keyboard_origin;  /* Y */
/*
static XCharStruct echo__keyboard_overall;
*/

/* <not done> */
void
SRGP__initEchoModule ()
{
   /* CREATE THE TWO GC's. */
/*
   echo__keyboard_gc = XCreateGC (srgpx__display, srgpx__screenwin, 0L, NULL);
   echo__locator_gc = XCreateGC (srgpx__display, srgpx__screenwin, 0L, NULL);
*/

   /* INITIALIZE KEYBOARD GC: font, color, origin */
   SRGP__updateKeyboardEchoAttributes ();

   /* DEFAULT LOCATOR-ECHO RUBBER ANCHOR (same as keyboard echo). */
   echo__locator_rubber_anchor =
	  SRGP_defPoint(echo__keyboard_left, echo__keyboard_origin);

   /* INITIALIZE LOCATOR RUBBER-ECHO GC: write-mode XOR. */
/*
   XSetFunction (srgpx__display, echo__locator_gc, GXxor);
   XSetForeground (srgpx__display, echo__locator_gc, (unsigned long) 1);
*/
}



static void
ToggleRubberRect (void)
/* DRAWS BETWEEN rubber_anchor AND previous_position */
{
   int tlx, tly, trx, try;
   int oldWidth, oldWriteMode;
   HDC hdc;
   HBRUSH hBrush;

   if (echo__locator_rubber_anchor.x < echo__locator_previous_position.x) {
	  tlx = echo__locator_rubber_anchor.x;
	  trx = echo__locator_previous_position.x;
   }
   else {
	  tlx = echo__locator_previous_position.x;
	  trx = echo__locator_rubber_anchor.x;
   }

   if (echo__locator_rubber_anchor.y < echo__locator_previous_position.y) {
	  tly = echo__locator_rubber_anchor.y;
	  try = echo__locator_previous_position.y;
   }
   else {
	  tly = echo__locator_previous_position.y;
	  try = echo__locator_rubber_anchor.y;
   }
   oldWidth = srgp__curActiveCanvasSpec.attributes.line_width;
   oldWriteMode = srgp__curActiveCanvasSpec.attributes.write_mode;

   PUSH_TRACE;
   SRGP_setLineWidth(1);
   SRGP_setWriteMode(WRITE_XOR);
   POP_TRACE;

   hdc = GetDC (srgp__canvasTable[0].drawable.win);
   hBrush = SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
   Rectangle(hdc, tlx, tly, trx, try);
   DeleteObject(SelectObject(hdc,hBrush));
   ReleaseDC(srgp__canvasTable[0].drawable.win, hdc);

   PUSH_TRACE;
   SRGP_setLineWidth(oldWidth);
   SRGP_setWriteMode(oldWriteMode);
   POP_TRACE;
}


static void
ToggleRubberLine(void)
/* DRAWS BETWEEN rubber_anchor AND previous_position */
{
   HDC hdc;
   int oldWidth, oldWriteMode;

   oldWidth = srgp__curActiveCanvasSpec.attributes.line_width;
   oldWriteMode = srgp__curActiveCanvasSpec.attributes.write_mode;

   PUSH_TRACE;
   SRGP_setLineWidth(1);
   SRGP_setWriteMode(WRITE_XOR);
   POP_TRACE;

   hdc = GetDC (srgp__canvasTable[0].drawable.win);
   MoveTo(hdc,echo__locator_previous_position.x,
			  echo__locator_previous_position.y);
   LineTo(hdc,echo__locator_rubber_anchor.x,
			  echo__locator_rubber_anchor.y);
   ReleaseDC(srgp__canvasTable[0].drawable.win,hdc);

   PUSH_TRACE;
   SRGP_setLineWidth(oldWidth);
   SRGP_setWriteMode(oldWriteMode);
   POP_TRACE;

}

static void
ToggleRubberEcho(void)
{
   if (srgp__cur_locator_echo_type == RUBBER_RECT)
	  ToggleRubberRect();
   else
	  ToggleRubberLine();
}


void
SRGP__enableLocatorRubberEcho ()
{
   if ( ! locator_echo_is_active)
	  if (srgp__cur_mode[LOCATOR] != INACTIVE)
	 if (srgp__cur_locator_echo_type > CURSOR) {
		echo__locator_previous_position =
		   SRGP_defPoint
		  (srgp__cur_locator_measure.position.x,
		   SCREENFIXED(srgp__cur_locator_measure.position.y));
		echo__locator_rubber_anchor =
		   SRGP_defPoint
		  (srgp__cur_locator_echo_anchor.x,
		   SCREENFIXED(srgp__cur_locator_echo_anchor.y));
		locator_echo_is_active = TRUE;
		ToggleRubberEcho();
	 }
}


void
SRGP__disableLocatorRubberEcho()
{
   if (locator_echo_is_active) {
	  ToggleRubberEcho();
	  locator_echo_is_active = FALSE;
   }
}


void
SRGP__updateLocatorRubberEcho ()
{
   if (locator_echo_is_active) {
	  ToggleRubberEcho();
	  echo__locator_previous_position =
	 SRGP_defPoint (srgp__cur_Xcursor_x, srgp__cur_Xcursor_y);
	  ToggleRubberEcho();
   }
}



void
SRGP__updateLocatorRubberAnchor ()
{
   if (locator_echo_is_active)
	  ToggleRubberEcho();

   echo__locator_rubber_anchor =
	  SRGP_defPoint
	 (srgp__cur_locator_echo_anchor.x,
	  SCREENFIXED(srgp__cur_locator_echo_anchor.y));

   if (locator_echo_is_active)
	  ToggleRubberEcho();
}



void
SRGP__enableLocatorCursorEcho ()
{

   if (srgp__cur_mode[LOCATOR] != INACTIVE)
	  if (srgp__cur_locator_echo_type == CURSOR) {
		  SetCursor(echo__locator_cursor_shape);
/*
		  ShowCursor(TRUE);
*/
      }
}


/* not done */
void
SRGP__disableLocatorCursorEcho ()
{
/*
	ShowCursor(FALSE);
*/
}


void
SRGP__updateLocatorCursorShape ()
{
   echo__locator_cursor_shape = srgp__cursorTable[srgp__cur_cursor];
   SRGP__enableLocatorCursorEcho ();
}






/** KEYBOARD ECHO **/

/* <not done> */
static void
E_DrawText ()
{
/*
   int direction, ascent, descent;

   XDrawImageString (srgpx__display, srgpx__screenwin, echo__keyboard_gc,
			 echo__keyboard_left, echo__keyboard_origin,
			 srgp__cur_keyboard_measure.buffer,
			 srgp__cur_keyboard_measure_length);
   XTextExtents (echo__keyboard_font,
		 srgp__cur_keyboard_measure.buffer,
		 srgp__cur_keyboard_measure_length,
		 &direction, &ascent, &descent, &echo__keyboard_overall);
   if (srgp__cur_keyboard_measure_length == 0)
	  echo__keyboard_overall.ascent = ascent;
   XFillRectangle (srgpx__display, srgpx__screenwin, echo__keyboard_gc,
		   echo__keyboard_left + echo__keyboard_overall.width + 2,
		   echo__keyboard_origin - echo__keyboard_overall.ascent,
		   7, echo__keyboard_overall.ascent);

*/
}


/* <not done> */
static void
EraseText()
{
/*
   XClearArea (srgpx__display, srgpx__screenwin,
		   echo__keyboard_left,
		   echo__keyboard_origin - echo__keyboard_overall.ascent,
		   echo__keyboard_overall.width + 9,
		   echo__keyboard_overall.ascent + echo__keyboard_overall.descent,
		   FALSE);
*/
}


/* <not done> */
void
SRGP__enableKeyboardEcho ()
{
/*
   if ( ! keyboard_echo_is_active)
	  if (srgp__cur_mode[KEYBOARD] != INACTIVE)
	 if (srgp__cur_keyboard_processing_mode == EDIT) {
		keyboard_echo_is_active = TRUE;
		E_DrawText();
	 }
*/
}


/* <not done> */
void
SRGP__disableKeyboardEcho ()
{
/*
   if (keyboard_echo_is_active) {
	  EraseText();
	  keyboard_echo_is_active = FALSE;
   }
*/
}


/* <not done> */
void
SRGP__updateKeyboardEcho ()
{
/*
   if (keyboard_echo_is_active) {
	  EraseText();
	  E_DrawText();
   }
*/
}


/* <not done> */
void
SRGP__updateKeyboardEchoAttributes ()
{
/*
   if (keyboard_echo_is_active) {
	  EraseText();
   }

   echo__keyboard_left = srgp__cur_keyboard_echo_origin.x;
   echo__keyboard_origin = SCREENFIXED(srgp__cur_keyboard_echo_origin.y);

   XSetForeground (srgpx__display, echo__keyboard_gc,
		   COLORINDEX(srgp__cur_keyboard_echo_color));
   XSetBackground (srgpx__display, echo__keyboard_gc,
		   COLORINDEX(SRGP_WHITE));
   XSetFont (srgpx__display, echo__keyboard_gc,
		 (echo__keyboard_font =
			srgp__fontTable[srgp__cur_keyboard_echo_font])->fid);

   if (keyboard_echo_is_active) {
	  E_DrawText();
   }
*/
}






