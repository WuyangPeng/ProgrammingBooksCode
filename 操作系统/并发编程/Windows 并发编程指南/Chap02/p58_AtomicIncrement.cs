//+---------------------------------------------------------------+
// AtomicIncrement.cs
// Chapter 2, page 58
//
// An example of an atomic increment method which uses CAS.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System.Threading;

namespace CPOW_DotNet.Chap02
{
    public static class Helpers
    {
        /// <summary>
        /// The CAS method isn't shown in the book, but is implied by the presence of
        /// special hardware instructions. Here's a sample implementation that uses
        /// the X86 CMPXCHG instruction to implement.
        /// </summary>
        /// <param name="target">A target location.</param>
        /// <param name="value">The new value to place there.</param>
        /// <param name="cmp">The value that must exist in order to replace it.</param>
        /// <returns>True if the value was replaced, false otherwise.</returns>
        public static bool CAS(ref int target, int value, int cmp)
        {
            return Interlocked.CompareExchange(ref target, value, cmp) == cmp;
        }

        /// <summary>
        /// An example of an atomic increment method using CAS.
        /// </summary>
        /// <param name="target">The target location to increment.</param>
        public static void AtomicIncrement(ref int target)
        {
            int seen;
            do
            {
                seen = target;
            }
            while (!CAS(ref target, seen + 1, seen));
        }
    }
}
