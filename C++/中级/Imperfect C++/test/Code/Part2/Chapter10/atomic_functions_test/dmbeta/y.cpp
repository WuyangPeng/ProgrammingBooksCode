FLAT    group   
;Time = Sun Nov 16 16:12:54 2003

;File = ..\dmbeta\af.cpp
    public  long stdcall atomic_postdecrement_up(long volatile *)
    public  _main
    extrn   _printf
    public  boolcdecl __Naf_cpp_main::is_host_up()
    extrn   __imp__GetSystemInfo@4
    extrn   __imp__Sleep@4
    extrn   __imp__InterlockedExchange@8
    public  ??_C@_0M@A@?$CFd?0?5?$CFd?0?5?$CFd?6?$AA@

includelib  Intel(R) C++ Compiler for 32-bit applications, Version 7.0   Build 20021018Z -Qvc7 -Qlocation,link,P:\Program Files\Microsoft Visual Studio .NET\Vc7\Bin -Zd -DSTLSOFT_NO_FASTCALL 
_TEXT   segment
    assume  CS:_TEXT
_TEXT   ends
_DATA   segment
___link:
    db  000h,000h,000h,000h
    dd  offset FLAT:___sti__af_cpp_main
    db  000h,000h,000h,000h
_DATA   ends
_BSS    segment
s_init_9187:
    db  04ch,001h,00fh,000h
s_spin_9187:
    db  066h,015h,0b7h,03fh
s_up_9187:
    db  00dh,006h,000h,000h
?s_up@__Naf_cpp_main@@4_NA:
    db  071h,000h,000h,000h
_BSS    ends
_DATA   segment
_DATA   ends
_DATA   segment
_DATA   ends
_DATA   segment
_DATA   ends
_TEXT   segment
    assume  CS:_TEXT
_TEXT   ends
_TEXT   segment
    assume  CS:_TEXT
;offset x1e for source line 0 is past end of code segment x10
;
;#define    _WINSTL_NO_NAMESPACES
;
;//#define  STLSOFT_NO_FASTCALL
;
long stdcall atomic_postdecrement_up(long volatile *):
        mov EAX,0FFFFFFFFh
;offset x1e for source line 0 is past end of code segment x10
;#include <winstl_atomic_functions.h>
;#include <stdio.h>
;
;int main()
;{
;   for(long i = 0, j = 0; i < 10; ++i)
;   {
        mov ECX,4[ESP]
;offset x1e for source line 0 is past end of code segment x10
;       int k;
;
;//     k = atomic_preincrement_up(&j);
;//     k = atomic_postincrement_up(&j);
;//     k = atomic_predecrement_up(&j);
        xadd    EAX,[ECX]
;offset x1e for source line 0 is past end of code segment x10
;       k = atomic_postdecrement_up(&j);
;
;       printf("%d, %d, %d\n", i, j, k);
;   }
;
        ret
;offset x1e for source line 0 is past end of code segment x10
;   return 0;
;}
        nop
;offset x1e for source line 0 is past end of code segment x10
        nop
;offset x1e for source line 0 is past end of code segment x10
        nop
_TEXT   ends
includelib  -defaultlib:libcp -defaultlib:uuid.lib -defaultlib:uuid.lib -defaultlib:libm -defaultlib:LIBC -defaultlib:libirc -defaultlib:OLDNAMES 
_TEXT   segment
    assume  CS:_TEXT
_main:
        push    EBP
        mov EBP,ESP
        sub ESP,3
        and ESP,0FFFFFFF8h
        add ESP,4
        push    EBX
        push    ESI
        xor EAX,EAX
        mov EBX,EAX
        mov [ESP],0
L19:        lea EDX,[ESP]
        push    EDX
        call    near ptr long stdcall atomic_postdecrement_up(long volatile *)
        push    EAX
        push    dword ptr 4[ESP]
        push    EBX
        push    offset FLAT:??_C@_0M@A@?$CFd?0?5?$CFd?0?5?$CFd?6?$AA@
        call    near ptr _printf
        add ESP,010h
        add EBX,1
        cmp EBX,0Ah
        jl  L19
        xor EAX,EAX
        pop ECX
        pop EBX
        mov ESP,EBP
        pop EBP
        ret
        nop
        nop
        nop
_TEXT   ends
_TEXT   segment
    assume  CS:_TEXT
boolcdecl __Naf_cpp_main::is_host_up():
        sub ESP,02Ch
        mov AL,s_init_9187
        test    AL,AL
        jne L83
        mov EAX,offset FLAT:s_spin_9187
        test    EAX,EAX
        je  L8E
        mov EAX,offset FLAT:s_spin_9187
L1A:        mov dword ptr 4[ESP],0
        mov [ESP],EAX
        push    1
        push    EAX
        call    dword ptr __imp__InterlockedExchange@8
        test    EAX,EAX
        je  L4A
L32:        push    1
        call    dword ptr __imp__Sleep@4
        push    1
        push    dword ptr 4[ESP]
;offset x41 for source line 0 is in middle of instruction at x40
        call    dword ptr __imp__InterlockedExchange@8
        test    EAX,EAX
        jne L32
L4A:        mov AL,s_init_9187
        test    AL,AL
        jne L77
        lea EAX,8[ESP]
        push    EAX
        call    dword ptr __imp__GetSystemInfo@4
        mov EAX,01Ch[ESP]
        mov byte ptr s_init_9187,1
        xor EDX,EDX
        cmp EAX,1
        setz    DL
        mov s_up_9187,DL
L77:        push    0
        push    dword ptr 4[ESP]
        call    dword ptr __imp__InterlockedExchange@8
L83:        movzx   EAX,byte ptr s_up_9187
        add ESP,02Ch
        ret
L8E:        lea EAX,4[ESP]
        jmp short   L1A
_TEXT   ends
_DATA   segment
__init_0:
    dd  offset FLAT:___sti__af_cpp_main
_DATA   ends
_TEXT   segment
    assume  CS:_TEXT
;offset x60 for source line 0 is past end of code segment xc
___sti__af_cpp_main:
        call    near ptr boolcdecl __Naf_cpp_main::is_host_up()
;offset x60 for source line 0 is past end of code segment xc
        mov ?s_up@__Naf_cpp_main@@4_NA,AL
;offset x60 for source line 0 is past end of code segment xc
        ret
;offset x60 for source line 0 is past end of code segment xc
        nop
_TEXT   ends
_DATA   segment
??_C@_0M@A@?$CFd?0?5?$CFd?0?5?$CFd?6?$AA@:
    db  025h,064h,02ch,020h,025h,064h,02ch,020h
    db  025h,064h,00ah,000h
_DATA   ends
    end
