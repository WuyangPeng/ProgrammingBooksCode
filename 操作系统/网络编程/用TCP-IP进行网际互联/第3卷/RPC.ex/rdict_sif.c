/* rdict_sif.c - init_1, insert_1, delete_1, lookup_1_svc */

#include <rpc/rpc.h>

#define	RPC_SVC
#include "rdict.h"

/* Server-side stub inteface routines written by hand */

static	int retcode;

int	initw(void), insertw(char *), deletew(char *), lookupw(char *);

/*------------------------------------------------------------------------
 * insertw_1_svc -  server side interface to remote procedure insertw
 *------------------------------------------------------------------------
 */
int	*
insertw_1_svc(char **w, struct svc_req *rqstp)
{
	retcode = insertw(*(char **)w);
	return &retcode;
}

/*------------------------------------------------------------------------
 * initw_1_svc -  server side interface to remote procedure initw
 *------------------------------------------------------------------------
 */
int	*
initw_1_svc(void *w, struct svc_req *rqstp)
{
	retcode = initw();
	return &retcode;
}

/*------------------------------------------------------------------------
 * deletew_1_svc -  server side interface to remote procedure deletew
 *------------------------------------------------------------------------
 */
int	*
deletew_1_svc(char **w, struct svc_req *rqstp)
{
	retcode = deletew(*(char **)w);
	return &retcode;
}

/*------------------------------------------------------------------------
 * lookupw_1_svc -  server side interface to remote procedure lookupw
 *------------------------------------------------------------------------
 */
int	*
lookupw_1_svc(char **w, struct svc_req *rqstp)
{
	retcode = lookupw(*(char**)w);
	return &retcode;
}
