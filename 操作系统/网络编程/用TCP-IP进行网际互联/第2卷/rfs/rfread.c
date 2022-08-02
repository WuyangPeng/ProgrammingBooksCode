/* rfread.c - rfread */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  rfread  --  read one or more bytes from a remote file
 *------------------------------------------------------------------------
 */
rfread(struct devsw *pdev, char *buff, unsigned len)
{
	return( rfio(pdev, FS_READ, (u_char *)buff, min(len,RDATLEN) ) );
}
