/* recopt.c - recopt, no_op */

#include <sys/types.h>

#include <stdio.h>

unsigned char	option_cmd;	/* has value WILL, WONT, DO, or DONT	*/

/*------------------------------------------------------------------------
 * recopt - record option type
 *------------------------------------------------------------------------
 */
int
recopt(FILE *sfp, FILE *tfp, int c)
{
	option_cmd = c;
	return 0;
}

/*------------------------------------------------------------------------
 * no_op - do nothing
 *------------------------------------------------------------------------
 */
int
no_op(FILE *sfp, FILE *tfp, int c)
{
	return 0;
}
