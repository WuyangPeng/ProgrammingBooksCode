/* ctxsw.s - ctxsw */

		.text
		.globl	_ctxsw
newmask:	.word	0

/*------------------------------------------------------------------------
 * ctxsw -  call is ctxsw(&oldsp, &oldmask, &newsp, &newmask)
 *------------------------------------------------------------------------
 */
_ctxsw:
		pushl	%ebp
		movl	%esp,%ebp

		pushl	12(%ebp)
		call	_disable
		movl	20(%ebp),%eax
		movw	(%eax),%dx
		movw	%dx,newmask
		pushfl			/* save flags */
		pushal			/* save general regs */
		/* save segment registers here, if multiple allowed */
		movl	8(%ebp),%eax
		movl	%esp,(%eax)	/* save old SP */

		movl	16(%ebp),%eax
		movl	(%eax),%esp	/* restore new SP */
		/* restore new segment registers here, if multiple allowed */
		popal			/* restore general registers */
		popfl			/* restore flags */
		pushl	$newmask
		call	_restore
		leave
		ret

