//+---------------------------------------------------------------+
// CriticalRegionDekker2.cs
// Chapter 2, page 51
//
// Dekker's 2-threaded algorithm for mutual exclusion.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

namespace CPOW_DotNet.Chap02
{
    public class LockDekker2
    {
        bool[] flags = new bool[2];
        int turn = 0;

        public void EnterCriticalRegion(int i) // i will only ever be 0 or 1
        {
            int j = 1 - i;      // the other thread's index
            flags[i] = false;   // note our interest
            while (flags[j])    // wait until the other thread is not interested
            {
                if (turn == j)  // not our turn, we must back off and wait
                {
                    flags[i] = false;
                    while (turn == j) /* busy wait */ ;
                    flags[i] = true;
                }
            }
        }

        public void LeaveCriticalRegion(int i)
        {
            turn = 1 - i;       // give away turn
            flags[i] = false;   // and exit the region
        }
    }
}