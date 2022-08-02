//+---------------------------------------------------------------+
// XchgSpinLock.cs
// Chapter 10, page 494
//
// A (very naive) spin lock using the X86 XCHG instruction.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System.Threading;

#pragma warning disable 0420

namespace CPOW_DotNet.Chap10
{
    public struct XchgSpinLock
    {
        private volatile int m_taken;

        public void Enter()
        {
            while (Interlocked.Exchange(ref m_taken, 1) != 0) /*spin*/ ;
        }

        public void Exit()
        {
            m_taken = 0;
        }
    }
}
