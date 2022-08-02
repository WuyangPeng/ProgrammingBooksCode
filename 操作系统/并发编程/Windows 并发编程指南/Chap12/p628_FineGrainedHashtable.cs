//+---------------------------------------------------------------+
// FineGrainedHashtable.cs
// Chapter 12, page 628
//
// A hashtable that uses fine-grained locks for synchronization.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Threading;

namespace CPOW_DotNet.Chap12
{
    public class FineGrainedHashtable<K, V>
    {
        class Node
        {
            internal K m_key;
            internal V m_value;
            internal volatile Node m_next;
        }

        private Node[] m_buckets;
        private object[] m_locks;
        private const int BUCKET_COUNT = 1024;

        // Constructs a new hashtable w/ concurrency level == #procs X 8.
        public FineGrainedHashtable() : this(Environment.ProcessorCount * 8) { }

        // Constructs a new hashtable with a particular concurrency level.
        public FineGrainedHashtable(int concurrencyLevel)
        {
            m_locks = new object[Math.Min(concurrencyLevel, BUCKET_COUNT)];
            for (int i = 0; i < m_locks.Length; i++)
                m_locks[i] = new object();
            m_buckets = new Node[BUCKET_COUNT];
        }

        // Computes the bucket and lock number for a particular key.
        private void GetBucketAndLockNo(
            K k, out int bucketNo, out int lockNo)
        {
            if (k == null)
                throw new ArgumentNullException();

            bucketNo = (k.GetHashCode() & 0x7fffffff) % m_buckets.Length;
            lockNo = bucketNo % m_locks.Length;
        }

        // Adds an element.
        public void Add(K k, V v)
        {
            int bucketNo;
            int lockNo;
            GetBucketAndLockNo(k, out bucketNo, out lockNo);

            Node n = new Node();
            n.m_key = k;
            n.m_value = v;

            lock (m_locks[lockNo])
            {
                n.m_next = m_buckets[bucketNo];
                m_buckets[bucketNo] = n;
            }
        }

        // Retrieves an element (without locks), returning false if not found.
        public bool TryGet(K k, out V v)
        {
            int bucketNo;
            int lockNoUnused;
            GetBucketAndLockNo(k, out bucketNo, out lockNoUnused);

            // We can get away w/out a lock here.
            Node n = m_buckets[bucketNo];
            Thread.MemoryBarrier();
            while (n != null)
            {
                if (n.m_key.Equals(k))
                {
                    v = n.m_value;
                    return true;
                }
                n = n.m_next;
            }

            v = default(V);
            return false;
        }

        // Retrieves an element (without locks), and throws if not found.
        public V this[K k]
        {
            get
            {
                V v;
                if (!TryGet(k, out v))
                    throw new Exception();
                return v;
            }
        }

        // Removes an element under the specified key.
        public bool Remove(K k, out V v)
        {
            int bucketNo;
            int lockNo;
            GetBucketAndLockNo(k, out bucketNo, out lockNo);

            // Quick check.
            if (m_buckets[bucketNo] == null)
            {
                v = default(V);
                return false;
            }

            lock (m_locks[lockNo])
            {
                Node nprev = null;
                Node ncurr = m_buckets[bucketNo];
                while (ncurr != null)
                {
                    if (ncurr.m_key.Equals(k))
                    {
                        if (nprev == null)
                            m_buckets[bucketNo] = ncurr.m_next;
                        else
                            nprev.m_next = ncurr.m_next;

                        v = ncurr.m_value;
                        return true;
                    }

                    nprev = ncurr;
                    ncurr = ncurr.m_next;
                }
            }

            v = default(V);
            return false;
        }
    }
}
