//+---------------------------------------------------------------+
// InterlockedHelpers.cs
// Chapter 10, page 498, 499, 500, 502, 503, 504
//
// Some simple helper functions that use interlocked instructions.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Threading;

namespace CPOW_DotNet.Chap10
{
    public static class InterlockedHelpers
    {

        public static bool CompareAndSwap(ref int location, int value, int comparand)
        {
            return Interlocked.CompareExchange(
                ref location, value, comparand) == comparand;
        }

        public static void AtomicWrite(ref long location, long value)
        {
            if (IntPtr.Size == 4)
                Interlocked.Exchange(ref location, value);
            else
                location = value;
        }

        public static long AtomicRead(ref long location)
        {
            if (IntPtr.Size == 4)
                return Interlocked.CompareExchange(ref location, 0L, 0L);
            else
                return location;
        }

        /// <summary>
        /// Emulates the BTS instruction (though not as efficiently),
        /// described on page 502.  Tests a certain bit; if off, it will
        /// set the bit and return true; else, the function returns false.
        /// </summary>
        /// <param name="location">A byref to a location to test.</param>
        /// <param name="bit">The bit [0-32) to test.</param>
        /// <returns>True if the set took place, false otherwise.</returns>
        public static bool BitTestAndSet(ref int location, int bit)
        {
            int bitmask = (1 << bit);

            int observed;
            do
            {
                observed = location;
            }
            while (Interlocked.CompareExchange(
                    ref location, observed | bitmask, observed) != observed);

            return (observed & bitmask) == bitmask;
        }

        /// <summary>
        /// Emulates the BTR instruction (though not as efficiently),
        /// described on page 502.  Tests a certain bit; if on, it will
        /// reset the bit and return true; else, the function returns false.
        /// </summary>
        /// <param name="location">A byref to a location to test.</param>
        /// <param name="bit">The bit [0-32) to test.</param>
        /// <returns>True if the reset took place, false otherwise.</returns>
        public static bool BitTestAndReset(ref int location, int bit)
        {
            int bitmask = (1 << bit);

            int observed;
            do
            {
                observed = location;
            }
            while (Interlocked.CompareExchange(
                    ref location, observed | ~bitmask, observed) != observed);

            return (observed & bitmask) == bitmask;
        }

        public static void InterlockedUpdate(ref int location, Func<int, int> func)
        {
            int oldValue, newValue;
            do
            {
                oldValue = location;
                newValue = func(oldValue);
            }
            while (Interlocked.CompareExchange(
                ref location, newValue, oldValue) != oldValue);
        }

        public static void InterlockedXor(ref int location, int xorValue)
        {
            InterlockedUpdate(ref location, (x) => x ^ xorValue);
        }
    }
}
