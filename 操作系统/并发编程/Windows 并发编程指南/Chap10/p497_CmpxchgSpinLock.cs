//+---------------------------------------------------------------+
// CmpxchgSpinLock.cs
// Chapter 10, page 497
//
// A (very naive) spin lock using the X86 CMPXCHG instruction.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System.Threading;

#pragma warning disable 0420

namespace CPOW_DotNet.Chap10
{
    public struct CmpxchgSpinLock
    {
        private volatile int m_taken;

        public void Enter()
        {
            int mid = Thread.CurrentThread.ManagedThreadId;
            while (Interlocked.CompareExchange(
                ref m_taken, mid, 0) != 0) /*spin*/ ;
        }

        public void Exit()
        {
            m_taken = 0;
        }
    }
}
