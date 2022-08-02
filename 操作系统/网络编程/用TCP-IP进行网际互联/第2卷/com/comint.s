/* comint.s - comint */

#include <icu.s>

/*------------------------------------------------------------------------
 * comint  --  interrupt handler for SLU input
 *------------------------------------------------------------------------
 */
	.text
	.globl	_comint

_comint:
	cli
	pushal
	movb	$EOI,%al
	outb	%al,$OCW1_2
	call	_comintr
	popal
	sti
	iret
