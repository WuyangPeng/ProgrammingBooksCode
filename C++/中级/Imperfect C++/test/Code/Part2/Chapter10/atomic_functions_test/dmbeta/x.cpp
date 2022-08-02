_TEXT   segment dword use32 public 'CODE'   ;size is 179
_TEXT   ends
_DATA   segment dword use32 public 'DATA'   ;size is 108
_DATA   ends
CONST   segment dword use32 public 'CONST'  ;size is 0
CONST   ends
_BSS    segment dword use32 public 'BSS'    ;size is 10
_BSS    ends
FLAT    group   
    extrn   long cdecl atomic_postincrement_smp(long volatile *)
    extrn   long cdecl atomic_postdecrement_smp(long volatile *)
    extrn   syscall spin_mutex::spin_mutex(long *)
    extrn   __except_list
    extrn   void syscall spin_mutex::lock()
    extrn   void syscall spin_mutex::unlock()
    extrn   syscall spin_mutex::~spin_mutex()
    extrn   __acrtused_con
    extrn   long cdecl atomic_postdecrement_up(long volatile *)
XIFCB   segment dword use32 public 'DATA'   ;size is 0
XIFCB   ends
XIFU    segment dword use32 public 'DATA'   ;size is 4
XIFU    ends
XIFL    segment dword use32 public 'DATA'   ;size is 0
XIFL    ends
XIFM    segment dword use32 public 'DATA'   ;size is 0
XIFM    ends
XIFCE   segment dword use32 public 'DATA'   ;size is 0
XIFCE   ends
includelib SNN.lib
    extrn   _printf
    extrn   __cpp_framehandler
    extrn   __imp__InterlockedExchange@8
    extrn   __imp__Sleep@4
    extrn   __imp__GetSystemInfo@4

    public  ?is_host_up@?%af_cpp1529504381@YA_NXZ
    public  _main
    public  ___SI?%af_cpp1529504381_
long cdecl atomic_postincrement_smp(long volatile *)    COMDAT flags=x0 attr=x10 align=x0 
long cdecl atomic_postdecrement_smp(long volatile *)    COMDAT flags=x0 attr=x10 align=x0 
syscall spin_mutex::spin_mutex(long *)  COMDAT flags=x0 attr=x10 align=x0 
void syscall spin_mutex::lock() COMDAT flags=x0 attr=x10 align=x0 
void syscall spin_mutex::unlock()   COMDAT flags=x0 attr=x10 align=x0 
syscall spin_mutex::~spin_mutex()   COMDAT flags=x0 attr=x10 align=x0 
long cdecl atomic_postdecrement_up(long volatile *) COMDAT flags=x0 attr=x10 align=x0 

_TEXT   segment
    assume  CS:_TEXT
?is_host_up@?%af_cpp1529504381@YA_NXZ:
        sub ESP,02Ch
        cmp byte ptr FLAT:_BSS[00h],0
        jne L61
        push    offset FLAT:_BSS[4]
        lea ECX,4[ESP]
        call    near ptr syscall spin_mutex::spin_mutex(long *)
        lea ECX,[ESP]
        call    near ptr void syscall spin_mutex::lock()
        cmp byte ptr FLAT:_BSS[00h],0
        jne L51
        lea EAX,8[ESP]
        push    EAX
        call    dword ptr __imp__GetSystemInfo@4
        mov EDX,1
        mov byte ptr FLAT:_BSS[00h],1
        cmp dword ptr 01Ch[ESP],1
        je  L4B
        xor EDX,EDX
L4B:        mov FLAT:_BSS[08h],DL
L51:        lea ECX,[ESP]
        call    near ptr void syscall spin_mutex::unlock()
        lea ECX,[ESP]
        call    near ptr syscall spin_mutex::~spin_mutex()
L61:        mov AL,FLAT:_BSS[08h]
        add ESP,02Ch
        ret
        nop
        nop
        nop
        nop
        nop
        nop
;
;#define    _WINSTL_NO_NAMESPACES
;
;//#define  STLSOFT_NO_FASTCALL
;
;#include <winstl_atomic_functions.h>
;#include <stdio.h>
;
;int main()
;{
_main:
        push    EAX
        push    EAX
        push    EBX
;   for(long i = 0, j = 0; i < 10; ++i)
        xor EBX,EBX
        mov 8[ESP],EBX
;   {
;       int k;
;
;//     k = atomic_preincrement_up(&j);
;//     k = atomic_postincrement_up(&j);
;//     k = atomic_predecrement_up(&j);
;       k = atomic_postdecrement_up(&j);
;
;       printf("%d, %d, %d\n", i, j, k);
L79:        lea EAX,8[ESP]
        push    EAX
        call    near ptr long cdecl atomic_postdecrement_up(long volatile *)
        add ESP,4
        push    EAX
        push    dword ptr 0Ch[ESP]
        push    EBX
        push    offset FLAT:_DATA[060h]
        call    near ptr _printf
;   }
        inc EBX
        add ESP,010h
        cmp EBX,0Ah
;offset x9e for source line 24 is in middle of instruction at x9d
;
;   return 0;
;}
        jb  L79
        pop EBX
        add ESP,8
        xor EAX,EAX
        ret
___SI?%af_cpp1529504381_:
        push    EAX
        call    near ptr ?is_host_up@?%af_cpp1529504381@YA_NXZ
        mov FLAT:_BSS[09h],AL
        pop EAX
        ret
_TEXT   ends
_DATA   segment
    db  001h,000h
    dd  offset FLAT:syscall spin_mutex::spin_mutex(long *)
    db  014h,000h
    db  000h,000h,030h,000h,000h,000h,0ffh,0ffh
    db  0ffh,0ffh,000h,000h,000h,000h,000h,000h
    db  001h,000h
    dd  offset FLAT:void syscall spin_mutex::lock()
    db  018h,000h
    db  000h,000h,03fh,000h,000h,000h,0ffh,0ffh
    db  0ffh,0ffh,000h,000h,000h,000h,000h,000h
    db  001h,000h
    dd  offset FLAT:void syscall spin_mutex::unlock()
    db  018h,000h
    db  000h,000h,023h,000h,000h,000h,0ffh,0ffh
    db  0ffh,0ffh,000h,000h,000h,000h,000h,000h
    db  001h,000h
    dd  offset FLAT:syscall spin_mutex::~spin_mutex()
    db  014h,000h
    db  000h,000h,019h,000h,000h,000h,0ffh,0ffh
    db  0ffh,0ffh,000h,000h,000h,000h,000h,000h
D60 db  025h,064h,02ch,020h,025h,064h,02ch,020h
    db  025h,064h,00ah,000h
_DATA   ends
CONST   segment
CONST   ends
_BSS    segment
_BSS    ends
XIFCB   segment
XIFCB   ends
XIFU    segment
    dd  offset FLAT:___SI?%af_cpp1529504381_
XIFU    ends
XIFL    segment
XIFL    ends
XIFM    segment
XIFM    ends
XIFCE   segment
XIFCE   ends
long cdecl atomic_postincrement_smp(long volatile *)    comdat
    assume  CS:long cdecl atomic_postincrement_smp(long volatile *)
        mov EAX,1
        lock
        xadd    EAX,[ECX]
        ret
long cdecl atomic_postincrement_smp(long volatile *)    ends
long cdecl atomic_postdecrement_smp(long volatile *)    comdat
    assume  CS:long cdecl atomic_postdecrement_smp(long volatile *)
        mov EAX,0FFFFFFFFh
        lock
        xadd    EAX,[ECX]
        ret
long cdecl atomic_postdecrement_smp(long volatile *)    ends
syscall spin_mutex::spin_mutex(long *)  comdat
    assume  CS:syscall spin_mutex::spin_mutex(long *)
L0:     push    EBP
        mov EBP,ESP
        mov EDX,FS:__except_list
        push    0FFFFFFFFh
        push    offset syscall spin_mutex::spin_mutex(long *)[043h]
        push    EDX
        mov EDX,ECX
        mov FS:__except_list,ESP
        sub ESP,8
        mov EAX,8[EBP]
        test    EAX,EAX
        jne L28
        lea EAX,4[EDX]
L28:        mov [EDX],EAX
        mov EAX,ECX
        mov dword ptr 4[EDX],0
        mov ECX,-0Ch[EBP]
        mov FS:__except_list,ECX
        mov ESP,EBP
        pop EBP
        ret 4
        mov EAX,offset FLAT:_DATA
        jmp near ptr __cpp_framehandler
syscall spin_mutex::spin_mutex(long *)  ends
void syscall spin_mutex::lock() comdat
    assume  CS:void syscall spin_mutex::lock()
L0:     push    EBP
        mov EBP,ESP
        mov EDX,FS:__except_list
        push    0FFFFFFFFh
        push    offset void syscall spin_mutex::lock()[051h]
        push    EDX
        mov FS:__except_list,ESP
        sub ESP,8
        push    EBX
        mov EBX,ECX
        push    1
        push    dword ptr [EBX]
        call    dword ptr __imp__InterlockedExchange@8
        test    EAX,EAX
        je  L43
L2D:        push    1
        call    dword ptr __imp__Sleep@4
        push    1
        push    dword ptr [EBX]
        call    dword ptr __imp__InterlockedExchange@8
        test    EAX,EAX
        jne L2D
L43:        mov EAX,-0Ch[EBP]
        mov FS:__except_list,EAX
        pop EBX
        mov ESP,EBP
        pop EBP
        ret
        mov EAX,offset FLAT:_DATA[018h]
        jmp near ptr __cpp_framehandler
void syscall spin_mutex::lock() ends
void syscall spin_mutex::unlock()   comdat
    assume  CS:void syscall spin_mutex::unlock()
L0:     push    EBP
        mov EBP,ESP
        mov EDX,FS:__except_list
        push    0FFFFFFFFh
        push    offset void syscall spin_mutex::unlock()[034h]
        push    EDX
        mov FS:__except_list,ESP
        sub ESP,8
        push    ECX
        push    0
        push    dword ptr [ECX]
        call    dword ptr __imp__InterlockedExchange@8
        mov EAX,-0Ch[EBP]
        mov FS:__except_list,EAX
        mov ESP,EBP
        pop EBP
        ret
        mov EAX,offset FLAT:_DATA[030h]
        jmp near ptr __cpp_framehandler
void syscall spin_mutex::unlock()   ends
syscall spin_mutex::~spin_mutex()   comdat
    assume  CS:syscall spin_mutex::~spin_mutex()
L0:     push    EBP
        mov EBP,ESP
        mov EDX,FS:__except_list
        push    0FFFFFFFFh
        push    offset syscall spin_mutex::~spin_mutex()[02Ah]
        push    EDX
        mov FS:__except_list,ESP
        sub ESP,8
        mov ECX,-0Ch[EBP]
        mov FS:__except_list,ECX
        mov ESP,EBP
        pop EBP
        ret
        mov EAX,offset FLAT:_DATA[048h]
        jmp near ptr __cpp_framehandler
syscall spin_mutex::~spin_mutex()   ends
long cdecl atomic_postdecrement_up(long volatile *) comdat
    assume  CS:long cdecl atomic_postdecrement_up(long volatile *)
        mov EAX,0FFFFFFFFh
        xadd    EAX,[ECX]
        ret
long cdecl atomic_postdecrement_up(long volatile *) ends
    end
