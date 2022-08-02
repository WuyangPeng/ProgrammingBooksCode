//+---------------------------------------------------------------+
// BlockingBoundedQueue.cs
// Chapter 12, page 647
//
// A simple blocking/bounded queue that uses two monitors.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Collections.Generic;
using System.Threading;

namespace CPOW_DotNet.Chap12
{
    public class BlockingBoundedQueue<T>
    {
        private Queue<T> m_queue = new Queue<T>();
        private int m_capacity;
        private object m_fullEvent = new object();
        private int m_fullWaiters = 0;
        private object m_emptyEvent = new object();
        private int m_emptyWaiters = 0;

        public BlockingBoundedQueue(int capacity)
        {
            m_capacity = capacity;
        }

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
                // If full, wait until an item is consumed.
                while (m_queue.Count == m_capacity)
                {
                    m_fullWaiters++;
                    try
                    {
                        lock (m_fullEvent)
                        {
                            Monitor.Exit(m_queue);
                            Monitor.Wait(m_fullEvent); // @BUGBUG: deadlock prone.
                            Monitor.Enter(m_queue);
                        }
                    }
                    finally
                    {
                        m_fullWaiters--;
                    }
                }

                m_queue.Enqueue(item);
            }

            // Wake consumers who are waiting for a new item.
            if (m_emptyWaiters > 0)
                lock (m_emptyEvent)
                    Monitor.Pulse(m_emptyEvent);
        }

        public T Dequeue()
        {
            T item;

            lock (m_queue)
            {
                while (m_queue.Count == 0)
                {
                    // Queue is empty, wait for a new item to arrive.
                    m_emptyWaiters++;
                    try
                    {
                        lock (m_emptyEvent)
                        {
                            Monitor.Exit(m_queue);
                            Monitor.Wait(m_emptyEvent); // @BUGBUG: deadlock prone.
                            Monitor.Enter(m_queue);
                        }
                    }
                    finally
                    {
                        m_emptyWaiters--;
                    }
                }

                item = m_queue.Dequeue();
            }

            // Wake producers who are waiting to produce.
            if (m_fullWaiters > 0)
                lock (m_fullEvent)
                    Monitor.Pulse(m_fullEvent);

            return item;
        }

        public T Peek()
        {
            lock (m_queue)
                return m_queue.Peek();
        }
    }
}
