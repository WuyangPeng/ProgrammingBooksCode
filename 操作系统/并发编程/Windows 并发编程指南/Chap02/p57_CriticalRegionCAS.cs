//+---------------------------------------------------------------+
// CriticalRegionCAS.cs
// Chapter 2, page 57
//
// A hardware compare-and-swap mutually exclusive lock.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System.Threading;

namespace CPOW_DotNet.Chap02
{
    public class LockCAS
    {
        int taken = 0;

        public void EnterCriticalRegion()
        {
            // Mark the region as taken.
            while (!Helpers.CAS(ref taken, 1, 0)) /* busy wait */ ;
        }

        public void LeaveCriticalRegion()
        {
            taken = 0; // Mark the region as available.
        }
    }
}