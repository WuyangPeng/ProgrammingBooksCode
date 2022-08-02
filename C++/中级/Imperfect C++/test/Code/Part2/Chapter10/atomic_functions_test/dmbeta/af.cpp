
#if defined(WINSTL_ATOMIC_FNS_CALLCONV_IS_FASTCALL)
__declspec(naked) long __fastcall atomic_postdecrement_up(long volatile * /* pl */)
#elif defined(WINSTL_ATOMIC_FNS_CALLCONV_IS_STDCALL)
__declspec(naked) long __stdcall atomic_postdecrement_up(long volatile * /* pl */)
#else
# error Need to define calling convention
#endif /* call-conv */
{
    _asm
    {
        // pop 1 into eax, which can then be atomically added into *pl (held
        // in ecx). Since it's an xadd it exchanges the previous value into eax
        mov eax, -1

#if defined(WINSTL_ATOMIC_FNS_CALLCONV_IS_FASTCALL)
        // __fastcall: ecx is pl
#elif defined(WINSTL_ATOMIC_FNS_CALLCONV_IS_STDCALL)
        // __stdcall: arguments are on the stack

        mov ecx, dword ptr [esp + 4]
#else
# error Need to define calling convention
#endif /* call-conv */

        xadd dword ptr [ecx], eax

        // Since this is post-decrement, we need do nothing, since the previous
        // value is in eax

        ret
    }
}

#include <stdio.h>

int main()
{
    for(long i = 0, j = 0; i < 10; ++i)
    {
        int k;

        k = atomic_postdecrement_up(&j);

        printf("%d, %d, %d\n", i, j, k);
    }

    return 0;
}
