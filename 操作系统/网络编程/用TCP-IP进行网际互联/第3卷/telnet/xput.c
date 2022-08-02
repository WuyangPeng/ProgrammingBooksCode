/* xput.c - xputc, xfputs */

#include <stdio.h>

extern FILE	*scrfp;

/*------------------------------------------------------------------------
 * xputc - putc with optional file scripting
 *------------------------------------------------------------------------
 */
int
xputc(char ch, FILE *fp)
{
	if (scrfp)
		(void) putc(ch, scrfp);
	return putc(ch, fp);
}

/*------------------------------------------------------------------------
 * xfputs - fputs with optional file scripting
 *------------------------------------------------------------------------
 */
int
xfputs(char *str, FILE *fp)
{
	if (scrfp)
		fputs(str, scrfp);
	fputs(str, fp);
}
