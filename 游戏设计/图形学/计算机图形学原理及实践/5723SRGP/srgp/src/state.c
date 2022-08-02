/*
	srgp_state.c
*/

#define SRGP_BOSS
#include "srgplocal.h"
#include <stdio.h>
#include <stdarg.h>

int SRGP_errorOccurred = 0;

errorHandlingMode srgp__curErrHndlMode = FATAL_ERRORS;

#ifdef _Windows
OFSTRUCT srgp__logOf;

void SRGP_winTrace(FILE *file, char *str, ...)
{
	va_list ap;

	file = fdopen(OpenFile("srgplog.txt", &srgp__logOf, OF_WRITE),"w");
	va_start(ap, str);
	vfprintf(file, str, ap);
	va_end(ap);
	fprintf(file, "\r");
	fclose(file);
}
#endif


/** SRGP_tracing
**/
void
SRGP_tracing (boolean please_trace)
{
	char message[] = "Unable to open the SRGP logfile!";

	if ( ! SRGP_logStream) {
#ifdef _Windows
		if (SRGP_logStream = fdopen(
						OpenFile("srgplog.txt",&srgp__logOf,OF_CREATE),"w"))
			fclose(SRGP_logStream);
		else {
			MessageBox(srgp__canvasTable[0].drawable.win, message,
					   "SRGP error", MB_OK | MB_ICONEXCLAMATION);
		}
#else
		/* LOGGING FILE IN LINE-BUFFERED MODE. */
		if (SRGP_logStream = fopen ("SRGPlogfile","w"))
			setvbuf (SRGP_logStream, NULL, _IOLBF, 512);
		else {
#ifdef THINK_C
			ReportSpecialError (message, NON_FATAL);
			return; /* we can't enable it, but we can continue! */
#else
		fprintf (stderr, "%s\n", message);
		exit(1);
#endif
		}
#endif
	}

	SRGP_trace (SRGP_logStream, "---- TRACE DISABLED\n");
	srgp__traceDisabled = ! please_trace;
	SRGP_trace (SRGP_logStream, "++++ TRACE ENABLED\n");
}

void
SRGP_disableDebugAids()
{
	srgp__userDebugAidsDisabled = TRUE;
}

void
SRGP_enableBlockedWait()
{
	srgp__blockedWaitEnabled = TRUE;
}

/* <not finished> */
static void
InitSRGP (char *name, int width, int height, int requested_planes,
		  boolean debugasap)
{
	register cnt;

	/* INIT TRACING ET.AL. */
	srgp__traceDisabled = TRUE;
	SRGP_logStream = NULL;


	srgp__canvasTable = SRGP_malloc(sizeof(canvas_spec) * MAX_CANVAS_INDEX+1);
	srgp__fontTable = SRGP_malloc(sizeof(fontInfo) * MAX_FONT_INDEX+1);
	srgp__cursorTable = SRGP_malloc(sizeof(cursorInfo) * MAX_CURSOR_INDEX+1);

	srgp__curActiveCanvasId = 0;
	srgp__curActiveCanvasSpec.max_xcoord = (width-1);
	srgp__curActiveCanvasSpec.max_ycoord = (height-1);

	SRGP__initGraphicsDevice (name, requested_planes, debugasap);
	srgp__canvasTable[0].drawable = srgp__curActiveCanvasSpec.drawable;

	SRGP__initCursorTable();

	SRGP__initFont();

	SRGP__setCanvasDefaults();

	srgp__resizeCallback = NULL;


	SRGP__initInputModule();
}

void SRGP_beginWithDebug (char *name, int width, int height, int planes,
						  boolean enable_trace)
{
	if (srgp__enabled)
		SRGP__error (ERR_ALREADY_ENABLED);
	else {
		srgp__enabled = TRUE;
		InitSRGP (name, width, height, planes, TRUE);
	}

	if (enable_trace)
		SRGP_tracing (TRUE);
}


void SRGP_begin (char *name, int width, int height, int planes,
				 boolean enable_trace)
{
	if (srgp__enabled)
		SRGP__error (ERR_ALREADY_ENABLED);
	else {
		srgp__enabled = TRUE;
		InitSRGP (name, width, height, planes, FALSE);
	}

	if (enable_trace)
		SRGP_tracing (TRUE);
}

void SRGP_registerResizeCallback (funcptr resizeCall)
{
   srgp__resizeCallback = resizeCall;
}

void SRGP_end ()
{
	SRGP_trace (SRGP_logStream, "SRGP_end\n");

	srgp__enabled = FALSE;
	if (SRGP_logStream)
		fclose(SRGP_logStream);
}

void SRGP_setErrorHandlingMode (errorHandlingMode newmode)
{
	srgp__curErrHndlMode = newmode;
}

static boolean CheckNotEnabledYet(void)
{
	if (srgp__enabled) {
		SRGP__error (ERR_ALREADY_ENABLED);
		return FALSE;
	}
	else return TRUE;
}

void SRGP_setMaxCanvasIndex(int i)
{
	if (CheckNotEnabledYet())
		MAX_CANVAS_INDEX = i;
}

void SRGP_setMaxPatternIndex(int i)
{
	if (CheckNotEnabledYet())
		MAX_PATTERN_INDEX = i;
}

void SRGP_setMaxCursorIndex(int i)
{
	if (CheckNotEnabledYet())
		MAX_CURSOR_INDEX = i;
}

void SRGP_setMaxFontIndex(int i)
{
	if (CheckNotEnabledYet())
		MAX_FONT_INDEX = i;
}

void SRGP_setMaxPointlistSize(int i)
{
	if (CheckNotEnabledYet())
		MAX_POINTLIST_SIZE = i;
}

void SRGP_setMaxStringSize(int i)
{
	if (CheckNotEnabledYet())
		MAX_STRING_SIZE = i;
}


void SRGP__reactToScreenResize (int www, int hhh)
{

	if (srgp__curActiveCanvasId == 0)
		srgp__canvasTable[0] = srgp__curActiveCanvasSpec;

	srgp__canvasTable[0].max_xcoord = www - 1;
	srgp__canvasTable[0].max_ycoord = hhh - 1;

	if (srgp__curActiveCanvasId == 0)
		srgp__curActiveCanvasSpec = srgp__canvasTable[0];

	/* The locator measure needs to be updated, since its y coord is a
	   function of the max_ycoord of the screen canvas. */
	srgp__cur_locator_measure.position.y =
		srgp__canvasTable[0].max_ycoord - srgp__cur_Xcursor_y;
	if (srgp__cur_locator_measure.position.y < 0)
		srgp__cur_locator_measure.position.y = 0;

	if (srgp__resizeCallback)
		(*srgp__resizeCallback) (www, hhh);
}

void SRGP_changeScreenCanvasSize (int newwidth, int newheight)
{
	SRGP__forceScreenResize(newwidth, newheight);
	SRGP__reactToScreenResize(newwidth, newheight);
}