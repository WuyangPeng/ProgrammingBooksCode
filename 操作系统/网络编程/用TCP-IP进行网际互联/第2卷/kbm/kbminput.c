/* kbminput.c - kbminput */

#include <conf.h>
#include <kernel.h>
#include <tty.h>
#include <io.h>

extern struct tty kbmtty;

/*------------------------------------------------------------------------
 * kbminput - handle an input character from the kbmsole
 *------------------------------------------------------------------------
 */
INTPROC
kbminput(unsigned int ch)
{
kprintf("kbminput\n");
}
