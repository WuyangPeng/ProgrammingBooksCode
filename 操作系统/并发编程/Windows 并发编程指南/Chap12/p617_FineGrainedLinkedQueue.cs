//+---------------------------------------------------------------+
// FineGrainedLinkedQueue.cs
// Chapter 12, page 617
//
// A linked queue that uses fine-grained locks.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Threading;

namespace CPOW_DotNet.Chap12
{
    public class FineGrainedLinkedQueue<T>
    {
        class Node
        {
            internal T m_val;
            internal Node m_next;
        }

        private Node m_head;
        private Node m_tail;
        private object m_enqLock = new object();
        private object m_deqLock = new object();

        public FineGrainedLinkedQueue()
        {
            m_head = m_tail = new Node();
        }

        public void Enqueue(T obj)
        {
            Node n = new Node();
            n.m_val = obj;

            lock (m_enqLock)
            {
                m_tail.m_next = n;
                m_tail = n;
            }
        }

        public T Dequeue()
        {
            T val;

            lock (m_deqLock)
            {
                Node next = m_head.m_next;

                if (next == null)
                    throw new Exception("empty");

                val = next.m_val;
                m_head = next;
            }

            return val;
        }
    }
}
