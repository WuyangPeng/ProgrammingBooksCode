//+---------------------------------------------------------------+
// LazyInitOnlyOnceRef.cs
// Chapter 10, page 523
//
// An example of a better performing lazy init type for classes.
// Note: the class is just called "LazyInit<T>" in the book.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;

namespace CPOW_DotNet.Chap10
{
    public class LazyInitOnlyOnceRef<T> where T : class
    {
        private volatile T m_value;
        private object m_sync = new object();
        private Func<T> m_factory;

        public LazyInitOnlyOnceRef(Func<T> factory) { m_factory = factory; }

        public T Value
        {
            get
            {
                if (m_value == null)
                {
                    lock (m_sync)
                    {
                        if (m_value == null)
                            m_value = m_factory();
                    }
                }
                return m_value;
            }
        }
    }
}
