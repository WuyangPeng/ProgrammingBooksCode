/*	$NetBSD: setjmp.S,v 1.3 1997/10/06 00:10:35 mark Exp $	*/

/*
 * Copyright (c) 1997 Mark Brinicombe
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by Mark Brinicombe
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <machine/asm.h>
#include <machine/setjmp.h>

/*
 * C library -- setjmp, longjmp
 *
 *	longjmp(a,v)
 * will generate a "return(v)" from the last call to
 *	setjmp(a)
 * by restoring registers from the stack.
 * The previous signal state is restored.
 */

ENTRY(setjmp)
	/* Block all signals and retrieve the old signal mask */
	stmfd	r13!, {r0, r14}
	mov	r0, #0x00000000

	bl	_sigblock
	mov	r1, r0

	ldmfd	r13!, {r0, r14}

	/* Store signal mask */
	str	r1, [r0, #(25 * 4)]

	ldr	r1, Lsetjmp_magic
	str	r1, [r0], #4

#ifdef SOFTFLOAT
	add	r0, r0, #52
#else
	/* Store fp registers */
	sfm	f4, 4, [r0], #48
	/* Store fpsr */
	rfs	r1
	str	r1, [r0], #0x0004
#endif	/*SOFTFLOAT*/
	/* Store integer registers */
        stmia	r0, {r4-r14}
        mov	r0, #0x00000000
        mov	r15, r14

Lsetjmp_magic:
	.word	JMPBUF_MAGIC_SETJMP


ENTRY(longjmp)
	ldr	r2, Lsetjmp_magic
	ldr	r3, [r0]
	teq	r2, r3
	bne	botch

	/* Fetch signal mask */
	ldr	r2, [r0, #(25 * 4)]

	/* Set signal mask */
	stmfd	r13!, {r0, r1, r14}

	mov	r0, r2
	bl	_sigsetmask

	ldmfd	r13!, {r0, r1, r14} 

	add	r0, r0, #4
#ifdef SOFTFLOAT
	add	r0, r0, #52
#else
	/* Restore fp registers */
	lfm	f4, 4, [r0], #48
	/* Restore FPSR */
	ldr	r4, [r0], #0x0004
	wfs	r4
#endif	/* SOFTFLOAT */
	/* Restore integer registers */
        ldmia	r0, {r4-r14}

	/* Validate r13 and r14 */
	teq	r13, #0
	beq	botch
	teq	r14, #0
	beq	botch

	/* Set return value */

	mov	r0, r1
	teq	r0, #0x00000000
	moveq	r0, #0x00000001
	mov	r15, r14

	/* validation failed, die die die. */
botch:
	bl	_longjmperror
	bl	_abort
	b	. - 8		/* Cannot get here */
