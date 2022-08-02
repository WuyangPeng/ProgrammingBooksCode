//+---------------------------------------------------------------+
// BtsSpinLock.cs
// Chapter 10, page 503
//
// A (very naive) spin lock using the X86 BTS instruction. Emulated
// by using a custom interlocked helper, since .NET doesn't support
// the BTS/BTR instructions.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System.Threading;

namespace CPOW_DotNet.Chap10
{
    public struct BtsSpinLock
    {
        private volatile int m_taken;

        public void Enter()
        {
#pragma warning disable 0420
            while (InterlockedHelpers.BitTestAndSet(ref m_taken, 0)) /*spin*/ ;
#pragma warning restore 0420
        }

        public void Exit()
        {
            m_taken = 0;
        }
    }
}
