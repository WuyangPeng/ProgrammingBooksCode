
#include <conf.h>
#include <kernel.h>
#include <io.h>

/*------------------------------------------------------------------------
 *  comgetc -- read a character from a serial line
 *------------------------------------------------------------------------
 */
int
comgetc(struct devsw *pdev)
{
	return SYSERR;
}


/*------------------------------------------------------------------------
 *  comread -- read from a serial line
 *------------------------------------------------------------------------
 */
int
comread(struct devsw *pdev, char *buf, unsigned count)
{
	return SYSERR;
}
