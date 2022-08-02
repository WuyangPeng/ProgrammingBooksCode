	.file	"initialize.c"
gcc2_compiled.:
___gnu_compiled_c:
.globl _reboot
.data
	.align 2
	.type	 _reboot,@object
	.size	 _reboot,4
_reboot:
	.long 0
.globl _revision
	.align 2
	.type	 _revision,@object
	.size	 _revision,4
_revision:
	.long 9
.text
LC0:
	.ascii "7.9.1439 i386 GATEWAY (dls@phoenix.dls) Mon Sep 22 00:37:34 PDT 1997\0"
LC1:
	.ascii "Xinu Version %s\0"
LC2:
	.ascii "\12\12%s\12\0"
LC3:
	.ascii "\12\0"
LC4:
	.ascii "   (reboot %d)\12\0"
LC5:
	.ascii "%d bytes real mem\12\0"
LC6:
	.ascii "%d bytes Xinu code\12\0"
LC7:
	.ascii "en\0"
LC8:
	.ascii "dis\0"
LC9:
	.ascii "clock %sabled\12\0"
LC10:
	.ascii "main\0"
LC11:
	.ascii "netstart\0"
	.align 2
.globl _nulluser
	.type	 _nulluser,@function
_nulluser:
	pushl %ebp
	movl %esp,%ebp
	call _initevec
	call _sysinit
	pushl $0
	pushl $3
	call _open
	pushl $LC0
	pushl $LC1
	pushl $_vers
	call _sprintf
	pushl $_vers
	pushl $LC2
	call _kprintf
	addl $28,%esp
	movl _reboot,%eax
	incl _reboot
	testl %eax,%eax
	jg L2
	pushl $LC3
	call _kprintf
	addl $4,%esp
	jmp L3
	.align 2,0x90
L2:
	pushl _reboot
	pushl $LC4
	call _kprintf
	addl $8,%esp
L3:
	movl _maxaddr,%eax
	incl %eax
	pushl %eax
	pushl $LC5
	call _kprintf
	movl $_end,%eax
	subl $_start,%eax
	pushl %eax
	pushl $LC6
	call _kprintf
	addl $16,%esp
	movl $LC8,%eax
	cmpl $1,_clkruns
	jne L4
	movl $LC7,%eax
L4:
	pushl %eax
	pushl $LC9
	call _kprintf
	call _enable
	pushl $0
	pushl $1
	pushl $LC10
	pushl $20
	pushl $1024
	pushl $_main
	call _create
	addl $32,%esp
	pushl %eax
	pushl $1
	pushl $LC11
	pushl $100
	pushl $1000
	pushl $_netstart
	call _create
	pushl %eax
	call _resume
	.align 2,0x90
L6:
	jmp L6
	.align 2,0x90
Lfe1:
	.size	 _nulluser,Lfe1-_nulluser
.lcomm _currsp.4,4
LC12:
	.ascii "prnull\0"
	.align 2
	.type	 _sysinit,@function
_sysinit:
	pushl %ebp
	movl %esp,%ebp
	pushl %edi
	pushl %esi
	pushl %ebx
	movl $0,_numproc
	movl $49,_nextproc
	movl $99,_nextsem
	movl $50,_nextqueue
	movl _maxaddr,%eax
	incl %eax
	cmpl $655360,%eax
	jbe L11
	movl $_end+7,%edx
	andb $248,%dl
	movl %edx,_memlist
	movl $1048576,(%edx)
	movl $655356,%eax
	subl $_end,%eax
	andb $252,%al
	movl %eax,4(%edx)
	movl $0,1048576
	movl _maxaddr,%eax
	addl $-1051648,%eax
	andb $252,%al
	movl %eax,1048580
	jmp L12
	.align 2,0x90
L11:
	movl $_end+7,%edx
	andb $248,%dl
	movl %edx,_memlist
	movl $0,(%edx)
	movl _maxaddr,%eax
	subl $_end,%eax
	addl $-3072,%eax
	andb $252,%al
	movl %eax,4(%edx)
L12:
	xorl %esi,%esi
	.align 2,0x90
L16:
	leal (%esi,%esi,8),%eax
	leal (%esi,%eax,2),%eax
	leal (%esi,%eax,2),%eax
	movb $2,_proctab(,%eax,4)
	incl %esi
	cmpl $49,%esi
	jle L16
	movl $_proctab,%ecx
	movb $1,_proctab
	xorl %edx,%edx
	.align 2,0x90
L21:
	movb LC12(%edx),%al
	movb %al,40(%edx,%ecx)
	incl %edx
	cmpl $6,%edx
	jle L21
	movl _maxaddr,%edi
	addl $-3071,%edi
	movl %edi,36(%ecx)
	movl _maxaddr,%edi
	addl $-3,%edi
	movl %edi,28(%ecx)
	movl 28(%ecx),%edi
	addl $-4,%edi
	movl %edi,8(%ecx)
	movl 28(%ecx),%eax
	movl $43689,(%eax)
	movl $_nulluser,60(%ecx)
	movl $0,56(%ecx)
	movl $0,4(%ecx)
	movl $0,_currpid
	xorl %esi,%esi
	.align 2,0x90
L26:
	movl %esi,%eax
	sall $4,%eax
	leal _semaph(%eax),%ebx
	movb $1,_semaph(%eax)
	call _newqueue
	movl %eax,8(%ebx)
	incl %eax
	movl %eax,12(%ebx)
	incl %esi
	cmpl $99,%esi
	jle L26
	call _newqueue
	movl %eax,_rdyhead
	movl %eax,%edi
	incl %edi
	movl %edi,_rdytail
	call __mkinit
	call _clkinit
	xorl %esi,%esi
	.align 2,0x90
L31:
	pushl %esi
	call _init
	addl $4,%esp
	incl %esi
	cmpl $47,%esi
	jle L31
	movl $1,%eax
	leal -12(%ebp),%esp
	popl %ebx
	popl %esi
	popl %edi
	leave
	ret
Lfe2:
	.size	 _sysinit,Lfe2-_sysinit
LC13:
	.ascii "%s\12\0"
LC14:
	.ascii "looping... press reset\12\0"
	.align 2
.globl __stop
	.type	 __stop,@function
__stop:
	pushl %ebp
	movl %esp,%ebp
	pushl 8(%ebp)
	pushl $LC13
	call _kprintf
	pushl $LC14
	call _kprintf
	.align 2,0x90
L34:
	jmp L34
	.align 2,0x90
Lfe3:
	.size	 __stop,Lfe3-__stop
LC15:
	.ascii "%X\12\0"
LC16:
	.ascii "\12bad mem %X (%x != 0xA5)\12\0"
	.align 2
.globl _sizmem
	.type	 _sizmem,@function
_sizmem:
	pushl %ebp
	movl %esp,%ebp
	subl $8,%esp
	pushl %edi
	pushl %esi
	pushl %ebx
	movl $1048576,%esi
	movl $0,-8(%ebp)
	.align 2,0x90
L41:
	xorl %edi,%edi
	pushl %esi
	pushl $LC15
	call _kprintf
	xorl %ebx,%ebx
	addl $8,%esp
	.align 2,0x90
L45:
	movb (%ebx,%esi),%dl
	movb %dl,-4(%ebp)
	movb $165,(%ebx,%esi)
	call _junk
	cmpb $165,(%ebx,%esi)
	jne L51
	movb -4(%ebp),%dl
	movb %dl,(%ebx,%esi)
	incl %ebx
	cmpl $4095,%ebx
	jle L45
L43:
	testl %edi,%edi
	jne L40
	incl -8(%ebp)
	addl $4096,%esi
	cmpl $655360,%esi
	jne L41
	addl $96,-8(%ebp)
	movl $1048576,%esi
	jmp L41
	.align 2,0x90
L51:
	movzbl (%ebx,%esi),%eax
	pushl %eax
	leal (%ebx,%esi),%eax
	pushl %eax
	pushl $LC16
	call _kprintf
	incl %edi
	addl $12,%esp
	jmp L43
	.align 2,0x90
L40:
	movl -8(%ebp),%eax
	leal -20(%ebp),%esp
	popl %ebx
	popl %esi
	popl %edi
	leave
	ret
Lfe4:
	.size	 _sizmem,Lfe4-_sizmem
	.align 2
.globl _junk
	.type	 _junk,@function
_junk:
	pushl %ebp
	movl %esp,%ebp
	leave
	ret
Lfe5:
	.size	 _junk,Lfe5-_junk
.comm _rdyhead,4
.comm _rdytail,4
.comm _proctab,7800
.comm _numproc,4
.comm _nextproc,4
.comm _currpid,4
.comm _lastpid,4
.comm _semaph,1600
.comm _nextsem,4
.comm _memlist,8
.comm _maxaddr,4
.comm _q,3048
.comm _nextqueue,4
.comm _intmap,768
.comm _tty,2336
.comm _vers,100
.comm _sem,4
.comm _pid1,4
.comm _pid2,4
.comm _ptid,4
.lcomm _esp,4
