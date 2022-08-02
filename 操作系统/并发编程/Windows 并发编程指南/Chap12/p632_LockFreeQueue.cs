//+---------------------------------------------------------------+
// LockFreeQueue.cs
// Chapter 12, page 632
//
// A lock free queue, based on Michael and Scott's paper:
// "Simple, Fast, and Practical Non-Blocking and Blocking
// Concurrent Queue Algorithms", in the 15th Annual ACM Symposium
// on Principles of Distributed Computing (1996).
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;

#pragma warning disable 0420

namespace CPOW_DotNet.Chap12
{
    public class LockFreeQueue<T> : IEnumerable<T>
    {
        class Node
        {
            internal T m_val;
            internal volatile Node m_next;
        }

        private volatile Node m_head;
        private volatile Node m_tail;

        public LockFreeQueue()
        {
            m_head = m_tail = new Node();
        }

        public int Count
        {
            get
            {
                int count = 0;
                for (Node curr = m_head.m_next;
                    curr != null; curr = curr.m_next) count++;
                return count;
            }
        }

        public bool IsEmpty
        {
            get { return m_head.m_next == null; }
        }

        private Node GetTailAndCatchUp()
        {
            Node tail = m_tail;
            Node next = tail.m_next;

            // Update the tail until it really points to the end.
            while (next != null)
            {
                Interlocked.CompareExchange(ref m_tail, next, tail);
                tail = m_tail;
                next = tail.m_next;
            }

            return tail;
        }

        public void Enqueue(T obj)
        {
            // Create a new node.
            Node newNode = new Node();
            newNode.m_val = obj;

            // Add to the tail end.
            Node tail;
            do
            {
                tail = GetTailAndCatchUp();
                newNode.m_next = tail.m_next;
            }
            while (Interlocked.CompareExchange(
                ref tail.m_next, newNode, null) != null);

            // Try to swing the tail. If it fails, we'll do it later.
            Interlocked.CompareExchange(ref m_tail, newNode, tail);
        }

        public bool TryDequeue(out T val)
        {
            while (true)
            {
                Node head = m_head;
                Node next = head.m_next;

                if (next == null)
                {
                    val = default(T);
                    return false;
                }
                else
                {
                    if (Interlocked.CompareExchange(
                        ref m_head, next, head) == head)
                    {
                        // Note: this read would be unsafe with a C++
                        // implementation. Another thread may have dequeued
                        // and freed 'next' by the time we get here, at
                        // which point we would try to dereference a bad
                        // pointer. Because we're in a GC-based system,
                        // we're OK doing this -- GC keeps it alive.
                        val = next.m_val;
                        return true;
                    }
                }
            }
        }

        public bool TryPeek(out T val)
        {
            Node curr = m_head.m_next;

            if (curr == null)
            {
                val = default(T);
                return false;
            }
            else
            {
                val = curr.m_val;
                return true;
            }
        }

        public IEnumerator<T> GetEnumerator()
        {
            Node curr = m_head.m_next;
            Node tail = GetTailAndCatchUp();

            while (curr != null)
            {
                yield return curr.m_val;

                if (curr == tail)
                    break;

                curr = curr.m_next;
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return ((IEnumerable<T>)this).GetEnumerator();
        }
    }
}
