//+---------------------------------------------------------------+
// LazyInitOnlyOnce.cs
// Chapter 10, page 525
//
// An example of a better performing lazy init type for any types.
// Note: the class is just called "LazyInit<T>" in the book.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;

namespace CPOW_DotNet.Chap10
{
    public class LazyInitOnlyOnce<T>
    {
        private T m_value;
        private volatile bool m_initialized;
        private object m_sync = new object();
        private Func<T> m_factory;

        public LazyInitOnlyOnce(Func<T> factory) { m_factory = factory; }

        public T Value
        {
            get
            {
                if (!m_initialized)
                {
                    lock (m_sync)
                    {
                        if (!m_initialized)
                        {
                            m_value = m_factory();
                            m_initialized = true;
                        }
                    }
                }
                return m_value;
            }
        }
    }
}
