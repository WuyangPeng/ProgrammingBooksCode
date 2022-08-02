/* ue_int.s - _ue_int */

#include <icu.s>

		.text
		.globl	_ue_int
_ue_int:
		cli
		pushal

		movb	$EOI,%al	/* re-enable the device */
		outb	%al,$OCW1_2

		call	_ue_intr

		popal
		sti
		iret
