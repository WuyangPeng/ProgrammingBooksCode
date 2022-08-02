//+---------------------------------------------------------------+
// Barrier.cs
// Chapter 12, page 650
//
// A barrier which allows N threads to rendezvous.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Threading;

#pragma warning disable 0420

namespace CPOW_DotNet.Chap12
{
    public class Barrier : IDisposable
    {
        private readonly int m_initialCount; // Initial count.

        // High order bit 0==even, 1==odd; other bits are count.
        private volatile int m_currentCountAndSense;
        private const int MASK_CURR_SENSE = unchecked((int)0x80000000);
        private const int MASK_CURR_COUNT = ~MASK_CURR_SENSE;

        private ManualResetEvent m_oddEvent; // Event for odd phases.
        private ManualResetEvent m_evenEvent; // Event for even phases.

        public Barrier(int initialCount)
        {
            if (initialCount < 1)
                throw new ArgumentOutOfRangeException("initialCount");

            m_initialCount = initialCount;
            m_currentCountAndSense = initialCount; // Start at even sense.
            m_oddEvent = new ManualResetEvent(false);
            m_evenEvent = new ManualResetEvent(false);
        }

        public int InitialCount
        {
            get { return m_initialCount; }
        }

        public int CurrentCount
        {
            get { return m_currentCountAndSense & MASK_CURR_COUNT; }
        }

        public void SignalAndWait()
        {
            TrySignalAndWait(Timeout.Infinite);
        }

        public bool TrySignalAndWait(int timeoutMilliseconds)
        {
            // Read the sense so we can reverse it later if needed.
            int sense = (m_currentCountAndSense & MASK_CURR_SENSE);

            // We may have to retry in the case of timeouts, hence the loop.
            while (true)
            {
                int currentCountAndSense = m_currentCountAndSense;
                if ((currentCountAndSense & MASK_CURR_COUNT) == 1)
                {
                    // Last thread, try to reset the barrier state.
                    if (Interlocked.CompareExchange(
                            ref m_currentCountAndSense,
                            m_initialCount | (~(m_currentCountAndSense) & MASK_CURR_SENSE),
                            currentCountAndSense) != currentCountAndSense)
                        continue; // CAS failed, retry.

                    // Reset old event 1st, ensuring threads that wake up
                    // don't race and satisfy the next phase.
                    if (sense == 0)
                    {
                        // Even.
                        m_oddEvent.Reset();
                        m_evenEvent.Set();
                    }
                    else
                    {
                        // Odd.
                        m_evenEvent.Reset();
                        m_oddEvent.Set();
                    }
                }
                else
                {
                    // Not last thread, decrement the count and wait.
                    int newCount = (currentCountAndSense & MASK_CURR_SENSE) |
                        ((currentCountAndSense & MASK_CURR_COUNT) - 1);
                    if (Interlocked.CompareExchange(
                            ref m_currentCountAndSense, newCount,
                            currentCountAndSense) != currentCountAndSense)
                        continue; // CAS failed, retry.

                    // Wait on the event.
                    bool waitSuccess;
                    if (sense == 0)
                        waitSuccess = m_evenEvent.WaitOne(
                            timeoutMilliseconds, false);
                    else
                        waitSuccess = m_oddEvent.WaitOne(
                            timeoutMilliseconds, false);

                    // Timeouts are tricky since we already told other
                    // threads we reached the barrier.  Need to consider
                    // that they may have already noticed our state updates
                    // and hence moved to the next phasse. If they did move
                    // to the next phase, we will have to return true rather
                    // than timing out. We know this by checking the sense.
                    while (!waitSuccess)
                    {
                        currentCountAndSense = m_currentCountAndSense;
                        if ((currentCountAndSense & MASK_CURR_COUNT) != sense)
                            // Sense changed. We are past the point of
                            // timing out: return true.
                            break;

                        int resetCount =
                            (currentCountAndSense & MASK_CURR_SENSE) |
                            ((currentCountAndSense & MASK_CURR_COUNT) + 1);
                        if (Interlocked.CompareExchange(
                                ref m_currentCountAndSense, resetCount,
                                currentCountAndSense) != currentCountAndSense)
                            continue; // CAS failed, retry.

                        // Timed out and patched up our state changes.
                        return false;
                    }
                }

                return true;
            }
        }

        public void Dispose()
        {
            m_oddEvent.Close();
            m_evenEvent.Close();
        }
    }
}
