/* cominput.c - cominput */

#include <conf.h>
#include <kernel.h>
#include <tty.h>
#include <io.h>

extern struct tty contty;

/*------------------------------------------------------------------------
 * cominput - handle an input character from a serial line device
 *------------------------------------------------------------------------
 */
INTPROC
cominput(unsigned int ch)
{
	kprintf("cominput\n");
	return;
}
