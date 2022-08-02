/* sonotsup.c - sonotsup */

#include <stdio.h>

/*------------------------------------------------------------------------
 * sonotsup - an unsupported escape command
 *------------------------------------------------------------------------
 */
int
sonotsup(FILE *sfp, FILE *tfp, int c)
{
	fprintf(tfp, "\nunsupported escape: %c.\n", c);
	fprintf(tfp, "s  - turn on scripting\t\t");
	fprintf(tfp, "u  - turn off scripting\n");
	fprintf(tfp, ".  - disconnect\t\t\t");
	fprintf(tfp, "^Z - suspend\n");
	fprintf(tfp, "^T - print status\n");
	return 0;
}
