/* rfwrite.c - rfwrite */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  rfwrite  --  write one or more bytes to a remote file
 *------------------------------------------------------------------------
 */
int
rfwrite(struct devsw *pdev, unsigned char *buff, unsigned len)
{
	int	i;

	for (i=len ; i > 0 ; i-=RDATLEN, buff+=RDATLEN)
		if (rfio(pdev,FS_WRITE,buff,min(i,RDATLEN)) == SYSERR)
			return(SYSERR);
	return len;
}
