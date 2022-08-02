/* $XFree86: xc/programs/Xserver/hw/xfree86/vga256/drivers/sis/sis_textblt.s,v 1.2 1997/01/12 10:52:29 dawes Exp $ */

/*
 *
 * Copyright 1993 by H. Hanemaayer, Utrecht, The Netherlands
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of H. Hanemaayer not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  H. Hanemaayer makes no representations
 * about the suitability of this software for any purpose.  It is provided
 * "as is" without express or implied warranty.
 *
 * H. HANEMAAYER DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL H. HANEMAAYER BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * Author:  H. Hanemaayer, <hhanemaa@cs.ruu.nl>
 *
 * Modified for use with CHIPS by David Bateman <dbateman@ee.uts.edu.au>
 * Modified for Sis by Xavier Ducoin (xavier@rd.lectra.fr)
 *
 */

#include "assyntax.h"

 	FILE("sis_textblt.S")

	AS_BEGIN

/* Definition of stack frame function arguments. */

#define nglyph_arg	REGOFF(8,EBP)
#define height_arg	REGOFF(12,EBP)
#define glyphp_arg	REGOFF(16,EBP)
#define glyphwidth_arg	REGOFF(20,EBP)
#define vaddr_arg	REGOFF(24,EBP)

#define BYTE_REVERSED	GLNAME(byte_reversed)

/* I assume %eax and %edx can be trashed. */
/* Saving %ebx and %ecx may be unnecessary. */

	SEG_TEXT

#define bound_var	REGIND(ESP)

	ALIGNTEXT4
#if 1
	GLOBL GLNAME(sisTransferText)
GLNAME(sisTransferText):

	PUSH_L	(EBP)
	MOV_L	(ESP,EBP)
	PUSH_L	(EBX)
	PUSH_L	(ECX)
	PUSH_L	(ESI)
	PUSH_L	(EDI)
	SUB_L	(CONST(4),ESP)		/* one local variable */

	XOR_L   (EDX,EDX)		/* line = 0 */
	MOV_B	(CONST(0),CL)		/* shift = 0 */
	MOV_B	(glyphwidth_arg,CH)
	MOV_L	(EDX,EAX)		/* dworddata = 0 */

.line_loop2:
	CMP_L	(height_arg,EDX)
	JGE	(.finished2)

	MOV_L	(glyphp_arg,EDI)	/* glyphp */
	MOV_L	(nglyph_arg,ESI)
	LEA_L	(REGBISD(EDI,ESI,4,0),ESI) /* &(glyphp[nglyph]) */
	MOV_L	(ESI,bound_var)

.char_loop2:
	CMP_L	(bound_var,EDI)
	JGE 	(.line_finished2)

	MOV_L	(REGIND(EDI),EBX)	/* glyphp[chari] */
	MOV_L	(REGBISD(EBX,EDX,4,0),EBX) /* data = glyphp[chari][line] */
	MOV_L	(EBX,ESI)
	SHL_L	(CL,EBX)
	ADD_L	(EBX,EAX)		/* dworddata += low(data << shift) */
	ADD_B	(CH,CL)			/* shift += glyphwidth */
	ADD_L	(CONST(4),EDI)		/* glyphp += 4 */
	CMP_B	(CONST(32),CL)		/* shift < 32? */
	JL	(.char_loop2)

	/* At this point, high32(data << old_shift) is equal to */
	/* ESI >> (32 - (shift - glyphwidth)) */
	MOV_B   (CL,BL)
	SUB_B	(CH,CL)		/* shift - glyphwidth */
	NEG_B	(CL)
	ADD_B	(CONST(32),CL)
	SHR_L	(CL,ESI)
	MOV_B	(BL,CL)

	/* Write a 32-bit word. */
	XOR_L	(EBX,EBX)
	MOV_B	(AL,BL)
	MOV_B	(REGOFF(BYTE_REVERSED,EBX),AL)
	MOV_B	(AH,BL)
	MOV_B	(REGOFF(BYTE_REVERSED,EBX),AH)
	ROL_L	(CONST(16),EAX)
	MOV_B	(AL,BL)
	MOV_B	(REGOFF(BYTE_REVERSED,EBX),AL)
	MOV_B	(AH,BL)
	MOV_B	(REGOFF(BYTE_REVERSED,EBX),AH)
	MOV_L	(vaddr_arg,EBX)
	ROL_L	(CONST(16),EAX)
	SUB_B	(CONST(32),CL)		/* shift -= 32 (blend) */
	MOV_L	(EAX,REGIND(EBX))	/* *vaddr = dworddata */
	MOV_L	(ESI,EAX)		/* dworddata = high(data << shift) */
	ADD_L	(CONST(4),EBX)		/* vaddr++ */
	MOV_L	(EBX,vaddr_arg)
	JMP	(.char_loop2)

.line_finished2:
	INC_L	(EDX)			/* line++ */
	TEST_B	(CL,CL)
	JZ 	(.line_loop2)

	/* Make sure last bits of line are padded to a double-word boundary. */

	MOV_B	(CONST(32),CL)
	/* Write a 32-bit word. */
	XOR_L	(EBX,EBX)
	MOV_B	(AL,BL)
	MOV_B	(REGOFF(BYTE_REVERSED,EBX),AL)
	MOV_B	(AH,BL)
	MOV_B	(REGOFF(BYTE_REVERSED,EBX),AH)
	ROL_L	(CONST(16),EAX)
	MOV_B	(AL,BL)
	MOV_B	(REGOFF(BYTE_REVERSED,EBX),AL)
	MOV_B	(AH,BL)
	MOV_B	(REGOFF(BYTE_REVERSED,EBX),AH)
	MOV_L	(vaddr_arg,EBX)
	ROL_L	(CONST(16),EAX)
	SUB_B	(CONST(32),CL)		/* shift -= 32 (blend) */
	MOV_L	(EAX,REGIND(EBX))	/* *vaddr = dworddata */
	MOV_L	(CONST(0),EAX)		/* dworddata = 0 */
	ADD_L	(CONST(4),EBX)		/* vaddr++ (long)*/
	MOV_L	(EBX,vaddr_arg)
	JMP	(.line_loop2)

.finished2:
	ADD_L	(CONST(4),ESP)
	POP_L	(EDI)
	POP_L	(ESI)
	POP_L	(ECX)
	POP_L	(EBX)
	POP_L	(EBP)
	RET
#endif
