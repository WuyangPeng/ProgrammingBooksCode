//+---------------------------------------------------------------+
// BlockingQueue.cs
// Chapter 12, page 643
//
// A simple blocking queue that uses one monitor.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Collections.Generic;
using System.Threading;

namespace CPOW_DotNet.Chap12
{
    public class BlockingQueue<T>
    {
        private Queue<T> m_queue = new Queue<T>();
        private int m_waitingConsumers = 0;

        public int Count
        {
            get
            {
                lock (m_queue)
                    return m_queue.Count;
            }
        }

        public void Clear()
        {
            lock (m_queue)
                m_queue.Clear();
        }

        public bool Contains(T item)
        {
            lock (m_queue)
                return m_queue.Contains(item);
        }

        public void Enqueue(T item)
        {
            lock (m_queue)
            {
                m_queue.Enqueue(item);

                // Wake consumers waiting for a new element.
                if (m_waitingConsumers > 0)
                    Monitor.Pulse(m_queue);
            }
        }

        public T Dequeue()
        {
            lock (m_queue)
            {
                while (m_queue.Count == 0)
                {
                    // Queue is empty, wait until an element arrives.
                    m_waitingConsumers++;
                    try
                    {
                        Monitor.Wait(m_queue);
                    }
                    finally
                    {
                        m_waitingConsumers--;
                    }
                }

                return m_queue.Dequeue();
            }
        }

        public T Peek()
        {
            lock (m_queue)
                return m_queue.Peek();
        }
    }
}
