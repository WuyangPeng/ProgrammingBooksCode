//+---------------------------------------------------------------+
// FineGrainedQueue.cs
// Chapter 12, page 619
//
// An array-based queue that uses fine-grained locks.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Threading;

namespace CPOW_DotNet.Chap12
{
    public class FineGrainedQueue<T>
    {
        private const int INITIAL_SIZE = 32;
        private T[] m_array = new T[INITIAL_SIZE];
        private int m_head = 0;
        private int m_tail = 0;
        private object m_enqLock = new object();
        private object m_deqLock = new object();

        public void Enqueue(T obj)
        {
            lock (m_enqLock)
            {
                int newTail = m_tail + 1;
                if (newTail == m_array.Length) newTail = 0;

                // If full, resize.
                if (newTail == m_head)
                {
                    Resize();
                    newTail = m_tail + 1;
                    // assert: newTail != m_array.Length
                    // assert: newTail != m_head
                }

                m_array[m_tail] = obj;
                m_tail = newTail;
            }
        }

        private void Resize()
        {
            // assert: m_enqLock is held.
            lock (m_deqLock)
            {
                T[] newArray = new T[m_array.Length * 2];
                Array.Copy(m_array, m_head, newArray, 0, m_array.Length - m_head);
                Array.Copy(m_array, 0, newArray, m_array.Length - m_head, m_head);
                m_array = newArray;

                if (m_tail < m_head)
                    m_tail += m_array.Length - m_head;
                else
                    m_tail -= m_head;

                m_head = 0;
            }
        }

        public T Dequeue()
        {
            lock (m_deqLock)
            {
                if (m_head == m_tail)
                    throw new Exception("empty");

                T value = m_array[m_head];

                if (default(T) == null)
                    m_array[m_head] = default(T); // mark eligible for GC

                int newHead = m_head + 1;
                if (newHead == m_array.Length) newHead = 0;
                m_head = newHead;

                return value;
            }
        }

    }
}
