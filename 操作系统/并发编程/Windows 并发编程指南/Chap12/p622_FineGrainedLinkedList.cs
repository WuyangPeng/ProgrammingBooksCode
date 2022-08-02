//+---------------------------------------------------------------+
// FineGrainedLinkedList.cs
// Chapter 12, page 622
//
// A linked list that allows adds and removes from the middle, and
// uses fine-grained locking for synchronization.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Collections.Generic;
using System.Threading;

namespace CPOW_DotNet.Chap12
{
    public class FineGrainedLinkedList<T>
    {
        class Node
        {
            internal T m_val;
            internal Node m_next;
        }

        private Node m_head;
        private Node m_tail;

        public FineGrainedLinkedList()
        {
            m_head = m_tail = new Node();
        }

        public void AddHead(T obj)
        {
            Node n = new Node();
            n.m_val = obj;

            while (true)
            {
                Node h = m_head;
                lock (h)
                {
                    if (m_head != h) continue;
                    n.m_next = h.m_next;
                    h.m_next = n;
                    break;
                }
            }
        }

        public T RemoveHead()
        {
            T val;

            while (true)
            {
                Node h = m_head;
                lock (h)
                {
                    if (m_head != h) continue;

                    if (h.m_next == null)
                        throw new Exception("empty");

                    Node next = h.m_next;
                    val = next.m_val;
                    m_head = next;
                    break;
                }
            }

            return val;
        }

        public void AddTail(T obj)
        {
            Node n = new Node();
            n.m_val = obj;

            while (true)
            {
                Node t = m_tail;
                lock (t)
                {
                    if (m_tail != t) continue;
                    t.m_next = n;
                    m_tail = n;
                    break;
                }
            }
        }

        // RemoveTail difficult w/out doubly linking. Left as an exercise.

        private delegate void FindAction(Node pred, Node curr);

        private bool TryFindAndPerform(T obj, FindAction action)
        {
            Node pred = m_head;
            Node curr;

            Monitor.Enter(pred);
            while ((curr = pred.m_next) != null)
            {
                Monitor.Enter(curr);
                if (EqualityComparer<T>.Default.Equals(curr.m_val, obj))
                {
                    action(pred, curr);
                    Monitor.Exit(pred);
                    Monitor.Exit(curr);
                    return true;
                }
                Monitor.Exit(pred);
                pred = curr;
            }
            Monitor.Exit(pred);

            return false;
        }

        public bool TryInsertAfter(T search, T toAdd)
        {
            return TryFindAndPerform(search, delegate(Node pred, Node curr)
            {
                Node n = new Node();
                n.m_val = toAdd;
                n.m_next = curr.m_next;
                curr.m_next = n;
            });
        }

        public bool TryInsertBefore(T search, T toAdd)
        {
            return TryFindAndPerform(search, delegate(Node pred, Node curr)
            {
                Node n = new Node();
                n.m_val = toAdd;
                n.m_next = curr;
                pred.m_next = n;
            });
        }

        public bool TryRemove(T obj)
        {
            return TryFindAndPerform(obj, delegate(Node pred, Node curr)
            {
                pred.m_next = curr.m_next;
                if (m_tail == curr)
                    m_tail = pred;
            });
        }

        /// <summary>
        /// An alternative TryFindAndPerform algorithm that uses optimistic techniques
        /// to avoid locking each node hand-over-hand while walking it.
        /// </summary>
        /// <param name="obj">An object to look for.</param>
        /// <param name="action">The action to perform once found.</param>
        /// <returns>True if the object was found, false otherwise.</returns>
        private bool TryFindAndPerformOptimistic(T obj, FindAction action)
        {
            while (true)
            {
                Node pred = m_head;
                Node curr;

                while ((curr = pred.m_next) != null)
                {
                    if (EqualityComparer<T>.Default.Equals(curr.m_val, obj))
                    {
                        lock (pred)
                        {
                            lock (curr)
                            {
                                // If next pointer changed, curr was deleted.
                                if (pred.m_next != curr)
                                    break;
                                // If random access updates are allowed, we must
                                // revalidate that equals still holds.
                                if (!EqualityComparer<T>.Default.Equals(
                                        curr.m_val, obj))
                                    break;

                                action(pred, curr);
                                return true;
                            }
                        }
                    }
                    pred = curr;
                }

                if (curr == null)
                    return false;
            }
        }
    }
}
