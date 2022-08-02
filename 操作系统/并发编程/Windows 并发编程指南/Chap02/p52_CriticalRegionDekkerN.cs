//+---------------------------------------------------------------+
// CriticalRegionDekkerN.cs
// Chapter 2, page 52
//
// Dekker's N-threaded algorithm for mutual exclusion.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

namespace CPOW_DotNet.Chap02
{
    public class LockDekkerN
    {
        const int N = 4; // # of threads that can enter the region.

        enum F : int
        {
            Passive,
            Requesting,
            Active
        }

        F[] flags = new F[N]; // all initialized to passive
        int turn = 0;

        public void EnterCriticalRegion(int i)
        {
            int j;
            do
            {
                flags[i] = F.Requesting;    // note our interest

                while (turn != i)           // spin until it's our turn
                    if (flags[turn] == F.Passive)
                        turn = i;           // steal the turn

                flags[i] = F.Active;        // announce we're entering

                // Verify that no other thread has entered the region.
                for (j = 0;
                    j < N && (j == i || flags[j] != F.Active);
                    j++) ;
            }
            while (j < N);
        }

        public void LeaveCriticalRegion(int i)
        {
            flags[i] = F.Passive;           // just note we've left
        }
    }
}