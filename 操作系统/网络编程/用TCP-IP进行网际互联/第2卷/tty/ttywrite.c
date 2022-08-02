/* ttywrite.c - ttywrite */

#include <conf.h>
#include <kernel.h>
#include <tty.h>

/*------------------------------------------------------------------------
 * ttywrite - write a buffer to a tty
 *------------------------------------------------------------------------
 */
int
ttywrite(struct devsw *pdev, unsigned char *buf, unsigned len)
{
	struct devsw	*phw;
	struct tty	*ptty = (struct tty *)pdev->dvioblk;
	unsigned	i;

	if (ptty == 0)
		return SYSERR;
	phw = ptty->tty_phw;
	if (phw == 0)
		return SYSERR;
	if (phw->dvputc == 0)
		return SYSERR;
	for (i=0; i<len; ++i) {
		if (ptty->tty_oflags & TOF_RAW) {
			if (phw->dvputc(phw, buf[i]) != OK)
				break;
		}
		/* else, do cooked output */
		if ( buf[i] > 127) {
			(phw->dvputc)(phw, 'M');
			(phw->dvputc)(phw, '-');
			(phw->dvputc)(phw, buf[i] & 0x7f);
			continue;
		}
#ifdef notdef
		if (buf[i] == '\n')
			(phw->dvputc)(phw, '\r');
#endif
		(phw->dvputc)(phw, buf[i]);
	}
	return i;
}
