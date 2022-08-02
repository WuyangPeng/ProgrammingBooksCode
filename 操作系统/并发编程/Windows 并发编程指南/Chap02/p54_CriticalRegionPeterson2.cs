//+---------------------------------------------------------------+
// CriticalRegionPeterson2.cs
// Chapter 2, page 54
//
// Peterson's 2-threaded algorithm for mutual exclusion.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

namespace CPOW_DotNet.Chap02
{
    public class LockPeterson2
    {
        bool[] flags = new bool[2];
        int turn = 0;

        public void EnterCriticalRegion(int i)
        {
            flags[i] = true; // note our interest in the region
            turn = 1 - i;    // give the turn away

            // Wait until the region is available or it's our turn.
            while (flags[1 - i] && turn != i) /* busy wait */ ;
        }

        public void LeaveCriticalRegion(int i)
        {
            flags[i] = false; // just exit the region
        }
    }
}