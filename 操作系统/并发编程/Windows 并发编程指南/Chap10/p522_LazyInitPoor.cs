//+---------------------------------------------------------------+
// LazyInitPoor.cs
// Chapter 10, page 522
//
// An example of a poorly performing lazy initialization class.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;

namespace CPOW_DotNet.Chap10
{
    public class LazyInitPoor<T>
    {
        private T m_value;
        private bool m_initialized;
        private object m_sync = new object();
        private Func<T> m_factory;

        public LazyInitPoor(Func<T> factory) { m_factory = factory; }

        public T Value
        {
            get
            {
                lock (m_sync)
                {
                    if (!m_initialized)
                    {
                        m_value = m_factory();
                        m_initialized = true;
                    }
                }
                return m_value;
            }
        }
    }
}
