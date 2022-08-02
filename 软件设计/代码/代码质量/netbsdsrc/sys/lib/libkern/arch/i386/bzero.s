/*
 * Written by J.T. Conklin <jtc@netbsd.org>.
 * Public domain.
 */

#include <machine/asm.h>

#if defined(LIBC_SCCS)
	RCSID("$NetBSD: bzero.S,v 1.5 1995/10/07 09:27:02 mycroft Exp $")
#endif

ENTRY(bzero)
	pushl	%edi
	movl	8(%esp),%edi
	movl	12(%esp),%edx

	cld				/* set fill direction forward */
	xorl	%eax,%eax		/* set fill data to 0 */

	/*
	 * if the string is too short, it's really not worth the overhead
	 * of aligning to word boundries, etc.  So we jump to a plain
	 * unaligned set.
	 */
	cmpl	$16,%edx
	jb	L1

	movl	%edi,%ecx		/* compute misalignment */
	negl	%ecx
	andl	$3,%ecx
	subl	%ecx,%edx
	rep				/* zero until word aligned */
	stosb

	movl	%edx,%ecx		/* zero by words */
	shrl	$2,%ecx
	andl	$3,%edx
	rep
	stosl

L1:	movl	%edx,%ecx		/* zero remainder by bytes */
	rep
	stosb

	popl	%edi
	ret
