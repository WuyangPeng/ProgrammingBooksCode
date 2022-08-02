
#include <conf.h>
#include <kernel.h>
#include <io.h>

/*------------------------------------------------------------------------
 *  congetc -- read a character from the SUN physical keyboard
 *------------------------------------------------------------------------
 */
congetc(struct devsw *pdev )
{
	return SYSERR;
}


/*------------------------------------------------------------------------
 *  conread -- read from the SUN physical keyboard
 *------------------------------------------------------------------------
 */
conread(struct devsw *pdev, char *buff, unsigned count)
{
	return SYSERR;
}
