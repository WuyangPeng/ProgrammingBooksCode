/* rdict_cif.c - initw, insertw, deletew, lookupw */

#include <rpc/rpc.h>

#include <stdio.h>

#define RPC_CLNT
#include "rdict.h"

/* Client-side stub interface routines written by programmer */

extern	CLIENT	*handle;		/* handle for remote procedure	*/
static	int	*ret;			/* tmp storage for return code	*/

/*------------------------------------------------------------------------
 * initw - client interface routine that calls initw_1
 *------------------------------------------------------------------------
 */
int
initw()
{
	ret = initw_1(0, handle);
	return ret==0 ? 0 : *ret;
}

/*------------------------------------------------------------------------
 * insertw - client interface routine that calls insertw_1
 *------------------------------------------------------------------------
 */
int
insertw(char *word)
{
	char	**arg;			/* pointer to argument */
	arg = &word;
	ret = insertw_1(arg, handle);
	return ret==0 ? 0 : *ret;
}

/*------------------------------------------------------------------------
 * deletew - client interface routine that calls deletew_1
 *------------------------------------------------------------------------
 */
int
deletew(char *word)
{
	char	**arg;			/* pointer to argument */

	arg = &word;
	ret = deletew_1(arg, handle);
	return ret==0 ? 0 : *ret;
}

/*------------------------------------------------------------------------
 * lookupw - client interface routine that calls lookupw_1
 *------------------------------------------------------------------------
 */
int
lookupw(char *word)
{
	char	**arg;			/* pointer to argument */

	arg = &word;
	ret = lookupw_1(arg, handle);
	return ret==0 ? 0 : *ret;
}
