/**
This program places the keyboard in RAW EVENT mode.
**/

#include "srgp.h"

#include <string.h>
#include <alloc.h>

#ifdef THINK_C
void exit(int);
#endif

static deluxe_locator_measure dlm;
static char buffer[100];
static char kmstring[2];
static deluxe_keyboard_measure dkm;

static int lineheight, textw, texta, textd;

static int timeout;

static int locatorMode = SAMPLE;
static char *modeNames[] = {"INACTIVE", "SAMPLE", "EVENT"};

static int locatorButtonMask = LEFT_BUTTON_MASK;

static int width=10;
static int rectx = 10;
static int recty = 10;
static int startAng = 0;
static int endAng = 180;

point pt[4]={{10,10},{10,20},{20,20},{20,10}};

static void DisplayPrompt (void)
{
   int y = 100;
   char *arg;
   char *arg2;
   int test;

   y -= lineheight;
   SRGP_text (SRGP_defPoint(10,y), "Hit any keyboard key ('q' to exit)");

   arg = (char *) malloc (22);
   arg2 = (char *) malloc (22);
   strcpy (arg, "Hello, this is a test");
   strcpy (arg2, "Beeeeeeeeep!");
   test = strlen(arg);

   SRGP_text (SRGP_defPoint(10,y-50), arg);
   SRGP_text (SRGP_defPoint(10,y-70), arg2);

}

static void DisplayKeyboardMeasure (void)
{
   int y = 100;

   SRGP_setColor (COLOR_WHITE);
   SRGP_fillRectangleCoord (0,0, 400, 400);
   
   SRGP_setColor (COLOR_BLACK);
   
   y -= lineheight;
   sprintf (buffer, "Value: %c (hex %4x)", dkm.buffer[0], dkm.buffer[0]);
   SRGP_text (SRGP_defPoint(10,y), buffer);
   
   y -= lineheight;
   sprintf (buffer, "Modifier chord: %d, %d, %d", 
	    dkm.modifier_chord[0], dkm.modifier_chord[1], 
		dkm.modifier_chord[2]);
   SRGP_text (SRGP_defPoint(10,y), buffer);

   y -= lineheight;
   sprintf (buffer, "Timestamp: %8d seconds, %2d ticks",
		dkm.timestamp.seconds, dkm.timestamp.ticks);
   SRGP_text (SRGP_defPoint(10,y), buffer);

   y -= lineheight;
   sprintf (buffer, "Rectangle width: %d, bottom left: (%d,%d) top right: (%d,%d)",
					width, rectx, recty, rectx+width-1, recty+width-1);
   SRGP_text (SRGP_defPoint(10,y), buffer);


   pt[0].x = rectx;
   pt[0].y = recty;
   pt[1].x = rectx+width-1;
   pt[1].y = recty;
   pt[2].x = rectx+width-1;
   pt[2].y = recty+width-1;
   pt[3].x = rectx;
   pt[3].y = recty+width-1;

   SRGP_fillPolygon(4,pt);
/*
	SRGP_fillEllipseArc(SRGP_defRectangle(rectx, recty, rectx+width, recty+width),
    					startAng, endAng);

   SRGP_rectangleCoord(rectx, recty, rectx+width-1, recty+width-1);
*/
}





void main(int argc, char *argv[])
{

   SRGP_begin ("Keyboard exercise", 400, 100, 1, FALSE);

   SRGP_setInputMode (KEYBOARD, EVENT);
   SRGP_setKeyboardProcessingMode (RAW);

   dkm.buffer = kmstring;
   dkm.buffer_length = 2;

   SRGP_inquireTextExtent ("High", &textw, &texta, &textd);

   lineheight = texta + textd;

   DisplayPrompt();

   SRGP_rectangleCoord(10, 10, 10+width, 10+width); 


   while (1) {
	  switch (SRGP_waitEvent (INDEFINITE)) {
	   case KEYBOARD:
	 SRGP_getDeluxeKeyboard (&dkm);
	 if (dkm.buffer[0] == 'q') {
		SRGP_end();
		exit(0);
	 }	else if (dkm.buffer[0] == 'b') {
		width++;
	 }  else if (dkm.buffer[0] == 's') {
		width--;
	 }  else if (dkm.buffer[0] == 'l') {
		rectx--;
	 }  else if (dkm.buffer[0] == 'r') {
		rectx++;
	 }  else if (dkm.buffer[0] == 'u') {
		recty++;
	 }  else if (dkm.buffer[0] == 'd') {
		recty--;
	 }  else if (dkm.buffer[0] == '[') {
		startAng--;
	 }  else if (dkm.buffer[0] == ']') {
		startAng++;
	 }  else if (dkm.buffer[0] == '{') {
		endAng--;
	 }  else if (dkm.buffer[0] == '}') {
		endAng++;
     }
	 DisplayKeyboardMeasure();
	  }
   }
}
                                    