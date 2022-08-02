//+---------------------------------------------------------------+
// BlockingQueueWithAutoResetEvents.cs
// Chapter 5, page 244
//
// A blocking queue with auto-reset events.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Collections.Generic;
using System.Threading;

namespace CPOW_DotNet.Chap05
{
    public class BlockingQueueWithAutoResetEvents<T>
    {
        private Queue<T> m_queue = new Queue<T>();
        private Mutex m_mutex = new Mutex();
        private AutoResetEvent m_event = new AutoResetEvent(false);

        public void Enqueue(T obj)
        {
            // Enter the critical region and insert into our queue.
            m_mutex.WaitOne();
            try
            {
                m_queue.Enqueue(obj);
            }
            finally
            {
                m_mutex.ReleaseMutex();
            }

            // Note that an item is available, possibly waking a consumer.
            m_event.Set();
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
                    WaitHandle.SignalAndWait(m_mutex, m_event);
                    m_mutex.WaitOne();
                    taken = true;
                }

                value = m_queue.Dequeue();
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