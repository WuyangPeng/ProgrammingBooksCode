//+---------------------------------------------------------------+
// BlockingBoundedQueue.cs
// Chapter 5, page 225
//
// A blocking/bounded queue that uses a mutex and semaphores.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Collections.Generic;
using System.Threading;

namespace CPOW_DotNet.Chap05
{
    public class BlockingBoundedQueue<T>
    {
        private Queue<T> m_queue = new Queue<T>();
        private Mutex m_mutex = new Mutex();
        private Semaphore m_producerSemaphore;
        private Semaphore m_consumerSemaphore;

        public BlockingBoundedQueue(int capacity)
        {
            m_producerSemaphore = new Semaphore(capacity, capacity);
            m_consumerSemaphore = new Semaphore(0, capacity);
        }

        public void Enqueue(T obj)
        {
            // Ensure the buffer hasn't become full yet. If it has, we will
            // be blocked until a consumer takes an item.
            m_producerSemaphore.WaitOne();

            // Now enter the critical region and insert into our queue.
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
            m_consumerSemaphore.Release();
        }

        public T Dequeue()
        {
            // This call will block if the queue is empty.
            m_consumerSemaphore.WaitOne();

            // Dequeue the item from within our critical region.
            T value;
            m_mutex.WaitOne();
            try
            {
                value = m_queue.Dequeue();
            }
            finally
            {
                m_mutex.ReleaseMutex();
            }

            // Note that we took an item, possibly waking producers.
            m_producerSemaphore.Release();

            return value;
        }
    }
}