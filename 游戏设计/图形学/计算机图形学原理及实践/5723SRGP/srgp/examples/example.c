#include "srgp.h"
#include <stdio.h>

/* TEST OF LOCATOR SAMPLE MODE. */

/* Left button paints in red, middle in green, right in blue.
   Multiple buttons lead to color mixing.
 */


#define DLM   deluxe_locator_measure

int
LocatorMeasuresEqual(DLM first, DLM second)

{
return (

	(first.position.x == second.position.x) && 
	(first.position.y == second.position.y) &&

	(first.button_chord[0] == second.button_chord[0]) &&  
	 (first.button_chord[1] == second.button_chord[1]) &&  
	 (first.button_chord[2] == second.button_chord[2]) &&

         (first.modifier_chord[0] == second.modifier_chord[0]) &&  
	 (first.modifier_chord[1] == second.modifier_chord[1]) &&  
	 (first.modifier_chord[2] == second.modifier_chord[2]) 
  );
}

DLM
WaitForAnyChange (DLM original)
{
   DLM	retval;

   SRGP_sampleDeluxeLocator(&retval);
   while ( LocatorMeasuresEqual(original, retval) )
      SRGP_sampleDeluxeLocator(&retval);
 
   return(retval);
}

void main(int argc, char *argv[])
{
   char measure[3];
   char oldchar = '\0';
   DLM locmeasure;
   int col;
   int x=0;

   SRGP_begin ("Painting application", 500,500,3,FALSE);

   SRGP_loadCommonColor (0, "black");
   SRGP_loadCommonColor (1, "blue");
   SRGP_loadCommonColor (2, "maroon");
   SRGP_loadCommonColor (3, "cyan");
   SRGP_loadCommonColor (4, "red");
   SRGP_loadCommonColor (5, "magenta");
   SRGP_loadCommonColor (6, "yellow");
   SRGP_loadCommonColor (7, "white");

   SRGP_setLocatorEchoType (CURSOR);
   SRGP_setFillStyle(BITMAP_PATTERN_OPAQUE); 
   SRGP_setLocatorButtonMask
      (LEFT_BUTTON_MASK | MIDDLE_BUTTON_MASK | RIGHT_BUTTON_MASK);
   SRGP_setInputMode(LOCATOR, SAMPLE);
   SRGP_setKeyboardProcessingMode (RAW);
   SRGP_setInputMode(KEYBOARD, SAMPLE);

/*   printf("calling sampleKeyboard\n"); */
   SRGP_sampleKeyboard (measure,2);
   SRGP_text(SRGP_defPoint(200,200),measure);
/*   printf("returned from sampleKeyboard\n");*/
   while (TRUE) {
	  SRGP_sampleDeluxeLocator (&locmeasure);
	  col = 0;
/*	  printf("buttons=%d,%d,%d\t",
		locmeasure.button_chord[LEFT_BUTTON],
		locmeasure.button_chord[MIDDLE_BUTTON],
		locmeasure.button_chord[RIGHT_BUTTON]);
	  printf("pos=%d,%d\n",locmeasure.position.x,locmeasure.position.y);*/
	  if (locmeasure.button_chord[LEFT_BUTTON]==DOWN) col += 4;
	  if (locmeasure.button_chord[MIDDLE_BUTTON]==DOWN) col += 2;
	  if (locmeasure.button_chord[RIGHT_BUTTON]==DOWN) col += 1;
	  if (col > 0) {
		SRGP_setColor (col);
/*	    SRGP_setFillBitmapPattern (col); */
		SRGP_rectangleCoord
		   (locmeasure.position.x-5, locmeasure.position.y-5,
			locmeasure.position.x+5, locmeasure.position.y+5);
	  }
	  SRGP_sampleKeyboard (measure,2);
	  if (measure[0] != oldchar) {
		   SRGP_text(SRGP_defPoint(200+x,200),measure);
		   oldchar = measure[0];
		   x+=10;
	  }
   }

   SRGP_getKeyboard(measure,2);
/*   printf("\nfinal='%s'\n",measure);*/

   SRGP_end ();
}