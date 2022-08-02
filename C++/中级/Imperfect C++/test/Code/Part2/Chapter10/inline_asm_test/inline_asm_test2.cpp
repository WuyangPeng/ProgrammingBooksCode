
long    s;

#include <stdio.h>

#if 1
#define _WINSTL_NO_NAMESPACE

#include <winstl_atomic_functions.h>

#else /* ? 0 */
#if defined(WINSTL_ATOMIC_FNS_CALLCONV_IS_FASTCALL)
# ifdef __DMC__
#  error __fastcall is not supported by Digital Mars
# endif /* __DMC__ */
__declspec(naked) long __fastcall atomic_postdecrement_up(long volatile * /* pl */)
#elif defined(WINSTL_ATOMIC_FNS_CALLCONV_IS_STDCALL)
__declspec(naked) long __stdcall atomic_postdecrement_up(long volatile * /* pl */)
#else
# error Need to define calling convention: WINSTL_ATOMIC_FNS_CALLCONV_IS_FASTCALL or WINSTL_ATOMIC_FNS_CALLCONV_IS_STDCALL
#endif /* call-conv */
{
    __asm
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

        mov dword ptr [s], ecx

        xadd dword ptr [ecx], eax

        // Since this is post-decrement, we need do nothing, since the previous
        // value is in eax

#if defined(WINSTL_ATOMIC_FNS_CALLCONV_IS_FASTCALL)
        ret
#elif defined(WINSTL_ATOMIC_FNS_CALLCONV_IS_STDCALL)
        ret 4
#else
# error Need to define calling convention: WINSTL_ATOMIC_FNS_CALLCONV_IS_FASTCALL or WINSTL_ATOMIC_FNS_CALLCONV_IS_STDCALL
#endif /* call-conv */
    }
}
#endif /* 0 */

#define decfn   atomic_postdecrement_up
#define incfn   atomic_postincrement_up
//#define decfn atomic_predecrement_smp
//#define decfn atomic_predecrement
//#define incfn atomic_preincrement

#if 1
int main()
{
    for(long i = 0, j = 10; i < 10; ++i)
    {
        int k;
        int l;

        k = decfn(&j);
        l = incfn(&j);
        k = decfn(&j);

#if 0 || \
    (   !defined(__BORLANDC__) && \
        !defined(__DMC__) && \
        !defined(__INTEL_COMPILER) && \
        !defined(__MWERKS__) && \
        !defined(__WATCOMC__))
        printf("0x%08x\t0x%08x\n", (unsigned long)&j, s);
#endif /* !__MWERKS__ */

        printf("%d, %d, %d, %d\n", i, j, k, l);
    }

    return 0;
}
#else /* ? 0 */
int main()
{
    for(long i = 0, j = 10; i < 10; ++i)
    {
        int k;

        k = decfn(&j);

#if 0 || \
    (   !defined(__BORLANDC__) && \
        !defined(__DMC__) && \
        !defined(__INTEL_COMPILER) && \
        !defined(__MWERKS__))
        printf("0x%08x\t0x%08x\n", (unsigned long)&j, s);
#endif /* !__MWERKS__ */

        printf("%d, %d, %d\n", i, j, k);
    }

    return 0;
}
#endif /* 0 */
