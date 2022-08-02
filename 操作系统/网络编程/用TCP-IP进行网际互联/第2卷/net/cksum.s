	.text
	.align 2
	.globl	_cksum
_cksum:
	pushl	%ebp
	movl	%esp,%ebp

	movl	8(%ebp),%edx
	movl	12(%ebp),%ecx
	xorl	%eax,%eax		/* clear sum	*/
	testl	%ecx,%ecx		
	jle	L4
	sarl	$6,%ecx
	je	L5
L7:
	clc
	addl	(%edx),%eax
	adcl	4(%edx),%eax
	adcl	8(%edx),%eax
	adcl	12(%edx),%eax
	adcl	16(%edx),%eax
	adcl	20(%edx),%eax
	adcl	24(%edx),%eax
	adcl	28(%edx),%eax
	adcl	32(%edx),%eax
	adcl	36(%edx),%eax
	adcl	40(%edx),%eax
	adcl	44(%edx),%eax
	adcl	48(%edx),%eax
	adcl	52(%edx),%eax
	adcl	56(%edx),%eax
	adcl	60(%edx),%eax
	adcl	$0,%eax
	addl	$64,%edx
	decl	%ecx
	ja	L7
L5:
	movl	12(%ebp),%ecx
	andl	$0x3f,%ecx
	sarl	$2,%ecx	
	jle	L4
L3:
	clc
	addl	(%edx),%eax
	adcl	$0,%eax
	addl	$4,%edx
	decl	%ecx
	ja	L3
L4:

	movl	12(%ebp),%ecx
	andl	$2,%ecx
	jz	L1
	movzwl	(%edx),%ecx
	addl	%ecx,%eax
	addl	$2,%edx
L1:
	movl	12(%ebp),%ecx
	andl	$1,%ecx
	jz	L2
	xorl	%ecx,%ecx
	movb	(%edx),%cl
	addl	%ecx,%eax
L2:
	movl	%eax,%ecx
	shrl	$16,%eax
	andl	$0xffff,%eax
	andl	$0xffff,%ecx
	addl	%ecx,%eax
	movl	%eax,%ecx
	shrl	$16,%eax
	addl	%ecx,%eax

	notw	%ax
	movzwl	%ax,%eax
	leave
	ret
