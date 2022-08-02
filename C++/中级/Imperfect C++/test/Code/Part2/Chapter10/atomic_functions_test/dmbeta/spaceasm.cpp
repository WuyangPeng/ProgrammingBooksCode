_TEXT   segment dword use32 public 'CODE'   ;size is 63
_TEXT   ends
_DATA   segment dword use32 public 'DATA'   ;size is 12
_DATA   ends
CONST   segment dword use32 public 'CONST'  ;size is 0
CONST   ends
_BSS    segment dword use32 public 'BSS'    ;size is 0
_BSS    ends
FLAT    group   
includelib SNN.lib
    extrn   __acrtused_con
    extrn   _printf

    public  long stdcall atomic_postdecrement_up(long volatile *)
    public  _main
_TEXT   segment
    assume  CS:_TEXT
;
;#if defined(WINSTL_ATOMIC_FNS_CALLCONV_IS_FASTCALL)
;__declspec(naked) long __fastcall atomic_postdecrement_up(long volatile * /* pl */)
;#elif defined(WINSTL_ATOMIC_FNS_CALLCONV_IS_STDCALL)
;__declspec(naked) long __stdcall atomic_postdecrement_up(long volatile * /* pl */)
;#else
;# error Need to define calling convention
;#endif /* call-conv */
;{
long stdcall atomic_postdecrement_up(long volatile *):
        mov EAX,0FFFFFFFFh
;    _asm
;    {
;        // pop 1 into eax, which can then be atomically added into *pl (held
;        // in ecx). Since it's an xadd it exchanges the previous value into eax
;        mov eax, -1
;
;#if defined(WINSTL_ATOMIC_FNS_CALLCONV_IS_FASTCALL)
;        // __fastcall: ecx is pl
;#elif defined(WINSTL_ATOMIC_FNS_CALLCONV_IS_STDCALL)
;        // __stdcall: arguments are on the stack
;
;        mov ecx, dword ptr [esp + 4]
        mov ECX,4[ESP]
;#else
;# error Need to define calling convention
;#endif /* call-conv */
;
;        xadd dword ptr [ecx], eax
        xadd    EAX,[ECX]
;
;        // Since this is post-decrement, we need do nothing, since the previous
;        // value is in eax
;
;        ret
        ret
;    }
;}
;
;#include <stdio.h>
;
;int main()
;{
_main:
        enter   4,0
        push    EBX
;   for(long i = 0, j = 0; i < 10; ++i)
        xor EBX,EBX
        mov -4[EBP],EBX
        jmp short   L35
;   {
;       int k;
;
;//     k = atomic_preincrement_up(&j);
;//     k = atomic_postincrement_up(&j);
;//     k = atomic_predecrement_up(&j);
;       k = atomic_postdecrement_up(&j);
;
;       printf("%d, %d, %d\n", i, j, k);
L19:        lea ECX,-4[EBP]
        push    ECX
        call    near ptr long stdcall atomic_postdecrement_up(long volatile *)
        push    EAX
        push    dword ptr -4[EBP]
        push    EBX
        push    offset FLAT:_DATA
        call    near ptr _printf
;   }
        inc EBX
        add ESP,010h
L35:        cmp EBX,0Ah
        jb  L19
;
;   return 0;
        xor EAX,EAX
;}
        pop EBX
        leave
        ret
_TEXT   ends
_DATA   segment
D0  db  025h,064h,02ch,020h,025h,064h,02ch,020h
    db  025h,064h,00ah,000h
_DATA   ends
CONST   segment
CONST   ends
_BSS    segment
_BSS    ends
    end
