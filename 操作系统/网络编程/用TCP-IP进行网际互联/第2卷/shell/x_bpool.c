/* x_bpool.c - x_bpool */

#include <conf.h>
#include <kernel.h>
#include <mark.h>
#include <bufpool.h>

/*------------------------------------------------------------------------
 *  x_bpool  -  (command bpool) format and print buffer pool information
 *------------------------------------------------------------------------
 */
COMMAND	x_bpool(stdin, stdout, stderr, nargs, args)
int	stdin, stdout, stderr, nargs;
char	*args[];
{
	struct	bpool	*bpptr;
	char	str[80];
	int	i, inuse;

	for (i=0 ; i<nbpools ; i++) {
		bpptr = &bptab[i];
		inuse = bpptr->bptotal - scount(bpptr->bpsem);
		sprintf(str,
"pool=%2d. count %4d bsize=%4d, sem=%2d, inuse=%4d (%3d%%) max %4d (%3d%%)\n",
			i, bpptr->bptotal, bpptr->bpsize, bpptr->bpsem, 
			inuse, (inuse * 100)/bpptr->bptotal,
			bpptr->bpmaxused,
			(bpptr->bpmaxused*100)/bpptr->bptotal);
		write(stdout, str, strlen(str));
	}
	return(OK);
}
