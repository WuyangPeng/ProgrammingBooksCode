//+---------------------------------------------------------------+
// CriticalRegionStrictAlternation.cs
// Chapter 2, page 49
//
// Strict alternation for mutual exclusion.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

namespace CPOW_DotNet.Chap02
{
    public class LockStrictAlternation
    {
        const int N = 4; // # of threads in the system.
        int turn = 0; // Thread 0 gets its turn first.

        public void EnterCriticalRegion(int i)
        {
            while (turn != i) /* busy wait */ ;
            // Someone gave us the turn... we own the region.
        }

        public void LeaveCriticalRegion(int i)
        {
            // Give the turn to the next thread (possibly wrapping to 0).
            turn = (i + 1) % N;
        }
    }
}
