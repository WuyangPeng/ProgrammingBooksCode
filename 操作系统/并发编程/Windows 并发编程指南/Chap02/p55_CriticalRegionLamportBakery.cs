//+---------------------------------------------------------------+
// CriticalRegionLamportBakery.cs
// Chapter 2, page 55
//
// Leslie Lamport's N-threaded bakery algorithm for mutual exclusion.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

namespace CPOW_DotNet.Chap02
{
    public class LockLamportBakery
    {
        const int N = 4; // # of threads that can enter the region.
        int[] choosing = new int[N];
        int[] number   = new int[N];

        public void EnterCriticalRegion(int i)
        {
            // Let others know we are choosing a ticket number.
            // Then find the max current ticket number and add one.
            choosing[i] = 1;
            int m = 0;
            for (int j = 0; j < N; j++)
            {
                int jn = number[j];
                m = jn > m ? jn : m;
            }
            number[i] = 1 + m;
            choosing[i] = 0;

            for (int j = 0; j < N; j++)
            {
                // Wait for threads to finish choosing.
                while (choosing[j] != 0) /* busy wait */ ;

                // Wait for those with lower tickets to finish. If we took
                // the same ticket number as another thread, the one with the
                // lowest ID gets to go first instead.
                int jn;
                while ((jn = number[j]) != 0 &&
                    (jn < number[i] || (jn == number[i] && j < i)))
                    /* busy wait */ ;
            }

            // Our ticket was called. Proceed to our region...
        }

        public void LeaveCriticalRegion(int i)
        {
            number[i] = 0;
        }
    }
}