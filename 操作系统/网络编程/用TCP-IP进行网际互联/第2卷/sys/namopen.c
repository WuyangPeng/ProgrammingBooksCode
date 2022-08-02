/* namopen.c - namopen */

#include <conf.h>
#include <kernel.h>
#include <name.h>

/*------------------------------------------------------------------------
 *  namopen  -  open an object (e.g., remote file) based on the name
 *------------------------------------------------------------------------
 */
int
namopen(struct devsw *pdev, void *filenam0, void *mode0)
{
	char	*filenam = filenam0;
	char	*mode = mode0;
	int	dev;
	char	newname[NAMLEN];

	if ( (dev=nammap(filenam, newname)) == SYSERR)
		return SYSERR;
	return open(dev, newname, mode);
}
