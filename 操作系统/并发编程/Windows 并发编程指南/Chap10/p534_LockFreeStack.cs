//+---------------------------------------------------------------+
// LockFreeStack.cs
// Chapter 10, page 534
//
// A custom nonblocking stack.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Threading;

#pragma warning disable 0420

namespace CPOW_DotNet.Chap10
{
    public class LockFreeStack<T>
    {
        class Node
        {
            internal T m_value;
            internal volatile Node m_next;
        }

        volatile Node m_head;

        public void Push(T value)
        {
            Node n = new Node();
            n.m_value = value;

            Node h;
            do
            {
                h = m_head;
                n.m_next = h;
            }
            while (Interlocked.CompareExchange(ref m_head, n, h) != h);
        }

        public T Pop()
        {
            Node n;
            do
            {
                n = m_head;
                if (n == null) throw new Exception("stack empty");
            }
            while (Interlocked.CompareExchange(ref m_head, n.m_next, n) != n);

            return n.m_value;
        }
    }
}
