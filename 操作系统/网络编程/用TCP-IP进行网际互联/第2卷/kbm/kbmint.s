/* kbmint.s - kbmint */

#include <icu.s>

/*------------------------------------------------------------------------
 * kbmint  --  interrupt handler for keyboard input
 *------------------------------------------------------------------------
 */
	.text
	.globl	_kbmint

_kbmint:
	cli
	pushal
	movb	$EOI,%al
	outb	%al,$OCW1_2
	call	_kbmiin
	popal
	sti
	iret
