/* clkint.s - _clkint */

#include <icu.s>

		.data
count100:	.long	100
		.text
		.globl	_clkint
_clkint:
		cli
		pushal
		movb	$EOI,%al
		outb	%al,$OCW1_2

		incl	_ctr100
		subl	$1,count100
		ja	cl1
		incl	_clktime
		movl	$100,count100
cl1:
		cmpl	$0,_slnempty
		je	clpreem
		movl	_sltop,%eax
		decl	(%eax)
		ja	clpreem
		call	_wakeup
clpreem:	decl	_preempt
		ja	clret
		call	_resched
clret:
		popal
		sti
		iret
