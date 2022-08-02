//+---------------------------------------------------------------+
// CriticalRegionBroken.cs
// Chapter 2, page 48
//
// A (very!) broken attempt at mutual exclusion; DO NOT USE THIS.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

namespace CPOW_DotNet.Chap02
{
    public class LockBroken
    {
        int taken = 0;

        public void EnterCriticalRegion()
        {
            while (taken != 0) /* busy wait */ ;
            taken = 1; // Mark the region as taken.
        }

        public void LeaveCriticalRegion()
        {
            taken = 0; // Mark the region as available.
        }
    }
}
