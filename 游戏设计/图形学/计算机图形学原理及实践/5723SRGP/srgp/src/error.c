/*
	SRGP_error.c
	Implemented for MS Windows.
*/

#include "srgplocal.h"
#include "srgp_win.h"
#include <stdlib.h>
#include <stdarg.h>

char *srgp__identifierOfPackage = "SRGP for Windows";

#ifdef THINK_C
int srgp__identifierOfMessages;
#else
char **srgp__identifierOfMessages;
#endif

void
SRGP__error (int errtype,...)
{
	char rawmessage[256];
	char processedmessage[400];
	char logmessage[50];
	va_list argptr;

	LoadString(srgp__hInstance,0,logmessage,51);
	SRGP_trace(SRGP_logStream, logmessage, srgp__identifierOfPackage,
			   processedmessage);

	/* SIMPLE HANDLING??? */
	if (srgp__curErrHndlMode == NON_FATAL_ERRORS) {
		SRGP_errorOccurred = errtype;
		return;
	}


	LoadString(srgp__hInstance,errtype,rawmessage,255);
	va_start(argptr,errtype);
	vsprintf(processedmessage,rawmessage,argptr);
	va_end(argptr);
	MessageBox(srgp__canvasTable[0].drawable.win, processedmessage,
			   "SRGP error", MB_OK | MB_ICONEXCLAMATION);
	abort ();
}
