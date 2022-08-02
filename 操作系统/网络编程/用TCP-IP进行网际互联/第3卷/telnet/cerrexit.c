/* cerrexit.c - cerrexit */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#include "local.h"

/*------------------------------------------------------------------------
 * cerrexit - cleanup and exit with an error message
 *------------------------------------------------------------------------
 */
int
cerrexit(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	vfprintf(stderr, format, args);
	(void) tcsetattr(0, TCSADRAIN, &oldtty);
	va_end(args);
	exit(1);
}
