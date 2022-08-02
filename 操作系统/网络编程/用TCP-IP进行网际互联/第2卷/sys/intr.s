/* intr.s - disable(), restore(), enable(), pause(), halt() */


#include <icu.s>

	.text
	.globl	_enable
	.globl	_disable
	.globl	_restore
	.globl	_pause
	.globl	_halt
	.globl	_getirmask

/*------------------------------------------------------------------------
 * Xtrap - trap entry
 *------------------------------------------------------------------------
 */
Xtrap:
	call	_trap
	movw	$OCW1_2,%al
	outb	%al,$EOI
	popl	%eax		/* exception # */
	testl	$35,%eax
	jb	3f
	shrl	$5,%eax		/* convert to IRQ # */

	/* issue global rearm to cards */
	testl	$7,%eax
	ja	1f
	orl	$0x2f0,%eax	/* 0x2fX for IRQ 3-7 */
	movb	%bl,(%eax)
	jmp	3f
1:	testl	$9,%eax
	jz	2f
	testl	$15,%eax
	ja	3f
	orl	$0x6f0,%eax	/* 0x2f(X-8) for IRQ 10-15 */
	movb	%bl,(%eax)
	jmp	3f
2:	movb	%al,0x2f2	/* 0x2f2 for IRQ 9 */
3:
	popal
	leave
	iret

#define	INT(I) \
.globl	_Xint/**/I ;			\
_Xint/**/I:	pushl	%ebp ;		\
		movl	%esp,%ebp;	\
		pushal ;		\
		pushl	$I ;		\
		jmp	Xtrap

/*------------------------------------------------------------------------
 * _Xint? - default exception and interrupt entry points
 *	NB: These must be contiguous
 *------------------------------------------------------------------------
 */
INT(0);   INT(1);   INT(2);   INT(3);   INT(4);   INT(5);   INT(6);   INT(7);
INT(8);   INT(9);   INT(10);  INT(11);  INT(12);  INT(13);  INT(14);  INT(15);
INT(16);  INT(17);  INT(18);  INT(19);  INT(20);  INT(21);  INT(22);  INT(23);
INT(24);  INT(25);  INT(26);  INT(27);  INT(28);  INT(29);  INT(30);  INT(31);
INT(32);  INT(33);  INT(34);  INT(35);  INT(36);  INT(37);  INT(38);  INT(39);
INT(40);  INT(41);  INT(42);  INT(43);  INT(44);  INT(45);  INT(46);  INT(47);

		.globl	_defevec
_defevec:	.word	_Xint0
		.word	_Xint1
		.word	_Xint2
		.word	_Xint3
		.word	_Xint4
		.word	_Xint5
		.word	_Xint6
		.word	_Xint7
		.word	_Xint8
		.word	_Xint9
		.word	_Xint10
		.word	_Xint11
		.word	_Xint12
		.word	_Xint13
		.word	_Xint14
		.word	_Xint15
		.word	_Xint16
		.word	_Xint17
		.word	_Xint18
		.word	_Xint19
		.word	_Xint20
		.word	_Xint21
		.word	_Xint22
		.word	_Xint23
		.word	_Xint24
		.word	_Xint25
		.word	_Xint26
		.word	_Xint27
		.word	_Xint28
		.word	_Xint29
		.word	_Xint30
		.word	_Xint31
		.word	_Xint32
		.word	_Xint33
		.word	_Xint34
		.word	_Xint35
		.word	_Xint36
		.word	_Xint37
		.word	_Xint38
		.word	_Xint39
		.word	_Xint40
		.word	_Xint41
		.word	_Xint42
		.word	_Xint43
		.word	_Xint44
		.word	_Xint45
		.word	_Xint46
		.word	_Xint47

/*---------------------------------------------------------
 * pause: halt the processor until an interrupt occurs
 *---------------------------------------------------------
 */
_pause:
	call _enable
	hlt
	ret


/*---------------------------------------------------------
 * halt: do nothing forever
 *---------------------------------------------------------
 */
_halt:
	jmp _halt
	ret

/*---------------------------------------------------------
 * enable all interrupts
 *---------------------------------------------------------
 */
_enable:
	cli
	movw	_girmask,%ax
	outb	%al,$IMR1
	shrw	$8,%ax
	outb	%al,$IMR2
	sti
	ret


/*---------------------------------------------------------
 * disable(ps)    - disable interrupts, save old state in ps
 * STATWORD ps  (short *ps)
 *---------------------------------------------------------
 */
_disable:
	pushfl
	cli
	inb	$IMR2,%al
	shlw	$8,%ax
	inb	$IMR1,%al	
	notw	%ax		/* clear _girmask bits for user */
	orw	_girmask,%ax
	notw	%ax
	movl	8(%esp),%edx	/* get PS pointer	*/
	movw	%ax,(%edx)	/* save old IR mask	*/
	movb	$0xff,%al
	outb	%al,$IMR2
	movb	$0xff,%al
	outb	%al,$IMR1
	popfl
	ret


/*---------------------------------------------------------
 * restore(ps)    - restore interrupts to value in ps
 * STATWORD ps    (short *ps)
 *---------------------------------------------------------
 */
_restore: 
	pushfl
	cli
	movl	8(%esp),%edx
	movw	(%edx),%ax
	orw	_girmask,%ax
	outb	%al,$IMR1
	shrw	$8,%ax
	outb	%al,$IMR2
	popfl
	ret

/*------------------------------------------------------------------------
 * getirmask(ps)  - return current interrupt mask in ps
 *------------------------------------------------------------------------
 */
_getirmask:
	inb	$IMR2,%al
	shlw	$8,%ax
	inb	$IMR1,%al	
	movl	4(%esp),%edx
	movw	%ax,(%edx)
	ret

/*------------------------------------------------------------------------
 * Xignore - ignore this exception
 *------------------------------------------------------------------------
 */
.globl	_Xignore
_Xignore:
	iret
