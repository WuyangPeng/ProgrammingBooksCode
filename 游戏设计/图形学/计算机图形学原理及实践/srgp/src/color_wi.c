/*
	Color SRGP functions for MS Windows 3.0

	X color names are found in rgb.h.

	NOTE:  This version does not implement a palette when in VGA or lower
		   resolution modes!  Changes in the color table will only affect
		   future displayed objects.
*/

# include "srgplocal.h"
# include "srgp_win.h"
# include <math.h>
# include <string.h>
# include <ctype.h>
# include <stdlib.h>
# include <stdio.h>

#define DEFAULT_MAX_COLOR_INDEX   255

/*

	NOTE:  Do not use xor with a black color!  (use SRGP_WHITE or 1 to be
		   safe.

*/

/* not finished */
void SRGP__initColor (int requested_planes)
{
  srgp__available_depth = ((float) log(DEFAULT_MAX_COLOR_INDEX)
							/ (float) log(2));

  color_table = SRGP_malloc(sizeof(COLORREF)*(DEFAULT_MAX_COLOR_INDEX));
  SRGP_BLACK = 0;
  SRGP_WHITE = 1;
  color_table[SRGP_BLACK] = RGB(0,0,0);
  color_table[SRGP_WHITE] = RGB(255,255,255);

  if ((requested_planes == 0) ||
	  (requested_planes > srgp__available_depth))
	  srgp__application_depth = srgp__available_depth;
  else
	  srgp__application_depth = requested_planes;
  srgp__max_pixel_value = (1 << srgp__application_depth) - 1;

}

void SRGP_loadColorTable (int startentry, int count, unsigned short *red,
						  unsigned short *green, unsigned short *blue)
{
  int i, j, endi;

  if (srgp__available_depth == 1)
	  return;

  endi = startentry + count;

  DEBUG_AIDS{
	  SRGP_trace (SRGP_logStream, "SRGP_loadColorTable  %d  %d  %d %d %d\n",
				  startentry, count, red[0], green[0], blue[0]);

	  /* PERFORM CHECKING LEGALITY OF THE RANGE OF INDICES. */
	  srgp_check_pixel_value (startentry, "start");
	  srgp_check_pixel_value (endi-1, "end");
  }

  for (i=startentry, j=0; j < count ; j++, i++) {
	  color_table[i] = RGB(red[j],green[j],blue[j]);
  }
}


#ifdef OLDRGB
int SRGP_find_color_name (const SRGP_common_color *key,
						  const SRGP_common_color *datum)
{
   return (strcmp (key->name, datum->name));
}
#endif

void SRGP_loadSingleColor (int index, unsigned short red,
						   unsigned short green,unsigned short blue)
{
   SRGP_loadColorTable (index, 1, &red, &green, &blue);
}


void SRGP_loadCommonColor (int entry, char *name)
{
   char far *colors;
   char *colorid;
   char *converted;
   int i, j;
   char *rgbValue;
   boolean done;
   int red = 0;
   int green = 0;
   int blue = 0;
   int listlen;


   if (srgp__available_depth == 1)
	   return;

   DEBUG_AIDS{
	   SRGP_trace (SRGP_logStream, "SRGP_loadCommonColor  %d  %s\n", entry, name);
	   srgp_check_pixel_value (entry, "start/end");
   }

	converted = SRGP_malloc(strlen(name) + 3);
	converted[0] = ' ';
	for (i=0, j=1; i <= strlen(name); i++)
	  if (name[i] != ' ') {
		  converted[j] = tolower(name[i]);
		  j++;
	  }
	strcat(converted," ");

	colors = LockResource (srgp__colorlist);

	colorid = strstr(colors, converted);
	if (colorid != NULL) {
		rgbValue = colorid + strlen(converted);
		sscanf(rgbValue, "%d %d %d", &red, &green, &blue);
	}

/*  First attempt.  Better if the names were in order... */
/*
	listlen = strlen(colors);

	colorid = SRGP_malloc(80);
	for (i = 0; (colors[i] != '\n') && (i < listlen); i++)
		colorid[i] = colors[i];
	colorid[i++] = '\0';
	done = FALSE;
	do {
		rgbValue = strchr(colorid, ' ');
		rgbValue[0] = '\0';
		rgbValue++;
		done = (strcmpi(colorid, converted) == 0);
		if (!done) {
			for (j = 0; (colors[i] != '\n') && (i < listlen); i++, j++)
				colorid[j] = colors[i];
			colorid[i++] = '\0';
			if (i == listlen)
				done = TRUE;
		} else {
			sscanf(rgbValue, "%d %d %d", &red, &green, &blue);
		}
	} while (!done);
*/

	UnlockResource(srgp__colorlist);

#ifdef OLDRGB
   strcpy (key.name, name);
   key.red = key.green = key.blue = 0;
   if ((color = (SRGP_common_color *) bsearch (&key, SRGP_colors,
		SRGP_NUM_COMMON_COLORS, sizeof(SRGP_common_color),
		(int(*) (const void *, const void *)) SRGP_find_color_name)) == NULL) {

/*	 printf ("SRGP: unknown color \"%s\"\n", name); */

	 return;
   }
#endif

   PUSH_TRACE;
   SRGP_loadSingleColor (entry, red, green, blue);
   POP_TRACE;
}


void SRGP_inquireColorTable (int start, int cnt,
							 unsigned short *r, unsigned short *g,
							 unsigned short *b)
{
  int i, j, endi;

  /* LEAVE IMMEDIATELY IF EXECUTING ON BILEVEL DISPLAY */
  if (srgp__available_depth == 1)
	 return;

  endi = start + cnt;

  DEBUG_AIDS{
	  /* PERFORM CHECKING LEGALITY OF THE RANGE OF INDICES. */
	  srgp_check_pixel_value (start, "start");
	  srgp_check_pixel_value (endi-1, "end");
  }

  for (i=start, j=0; j < cnt; i++, j++) {
	 r[j] = GetRValue(color_table[i]);
	 g[j] = GetGValue(color_table[i]);
	 b[j] = GetBValue(color_table[i]);
  }
}


