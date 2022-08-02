//+---------------------------------------------------------------+
// BlockingQueueWithManualResetEvents.cs
// Chapter 5, page 248
//
// A blocking queue with manual-reset events.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Collections.Generic;
using System.Threading;

namespace CPOW_DotNet.Chap05
{
    public class BlockingQueueWithManualResetEvents<T>
    {
        private Queue<T> m_queue = new Queue<T>();
        private Mutex m_mutex = new Mutex();
        private ManualResetEvent m_event = new ManualResetEvent(false);

        public void Enqueue(T obj)
        {
            // Enter the critical region and insert into our queue.
            m_mutex.WaitOne();
            try
            {
                m_queue.Enqueue(obj);

                // If the queue was empty, the event should be
                // in a signaled set, possibly waking waiters.
                if (m_queue.Count == 1)
                    m_event.Set();
            }
            finally
            {
                m_mutex.ReleaseMutex();
            }
        }

        public T Dequeue()
        {
            // Dequeue the item from within our critical region.
            T value;
            bool taken = true;
            m_mutex.WaitOne();
            try
            {
                // If the queue is empty, we will need to exit the
                // critical region and wait for the event to be set.
                while (m_queue.Count == 0)
                {
                    taken = false;
                    m_mutex.ReleaseMutex();
                    m_event.WaitOne();
                    m_mutex.WaitOne();
                    taken = true;
                }

                value = m_queue.Dequeue();

                // If we made the queue empty, set to non-signaled.
                if (m_queue.Count == 0)
                    m_event.Reset();
            }
            finally
            {
                if (taken)
                {
                    m_mutex.ReleaseMutex();
                }
            }

            return value;
        }
    }
}