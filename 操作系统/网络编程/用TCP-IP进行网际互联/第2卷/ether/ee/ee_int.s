/* ee_int.s - _ee_int */

#include <icu.s>

		.text
		.globl	_ee_int
_ee_int:
		cli
		pushal

		movb	$EOI,%al	/* re-enable the device */
		outb	%al,$OCW1_2

		call	_ee_intr

		popal
		sti
		iret
