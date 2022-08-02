/* blkcopy.s - blkcopy */

/*------------------------------------------------------------------------
 * blkcopy - copy "count" bytes from "src" to "dst"
 *	blkcopy(dst, src, count)
 *------------------------------------------------------------------------
 */
	.globl	_blkcopy
	.globl	_memcpy
/*
 * NOTE: to handle overlapping buffers in the copy, blkcopy() copies 
 *	bytes back-to-front if src < dst, front-to-back otherwise
 */
	.align	2
_memcpy:
_blkcopy:
	pushl	%esi
	pushl	%edi
	movl	12(%esp),%edi
	movl	16(%esp),%esi
	movl	20(%esp),%ecx
	cmpl	%edi,%esi
	jle	L100
	sarl	$2,%ecx			/* long word count	*/
	cld
	rep
	movsl
	movl	20(%esp),%ecx
	andl	$3,%ecx			/* move residual bytes	*/
	rep
	movsb
	popl 	%edi
	popl	%esi
	ret
L100:
	decl	%ecx
	addl	%ecx,%esi		/* set pointers to end	*/
	addl	%ecx,%edi
	incl	%ecx
	std
	andl	$3,%ecx			/* move residual bytes */
	rep
	movsb
	subl	$3,%esi		/* convert to long word pointer	*/
	subl	$3,%edi		/* convert to long word pointer	*/
	movl	20(%esp),%ecx
	sarl	$2,%ecx			/* long-word count	*/
	rep
	movsl
	popl	%edi
	popl	%esi
	ret
