/* unscript.c - unscript */

#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>

#include "local.h"

/*------------------------------------------------------------------------
 * unscript - end session scripting
 *------------------------------------------------------------------------
 */
int
unscript(FILE *sfp, FILE *tfp, int c)
{
	struct stat	statb;

	if (scrfp == 0) {
		fprintf(tfp, "\nNot scripting.\n");
		return 0;
	}
	(void) fflush(scrfp);
	if (fstat(fileno(scrfp), &statb) == 0)
		fprintf(tfp, "\n\"%s\": %d bytes.\n", scrname,
				statb.st_size);
	(void) fclose(scrfp);
	scrfp = 0;
	return 0;
}
