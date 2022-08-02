//+---------------------------------------------------------------+
// LazyInitRelaxedVal.cs
// Chapter 10, page 527
//
// A lazy init type that allows multiple allocations (for structs).
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Threading;

#pragma warning disable 0420

namespace CPOW_DotNet.Chap10
{
    public class LazyInitRelaxedVal<T> where T : struct
    {
        class Boxed
        {
            internal T m_value;
            internal Boxed(T value) { m_value = value; }
        }

        private volatile Boxed m_value;
        private Func<T> m_factory;

        public LazyInitRelaxedVal(Func<T> factory) { m_factory = factory; }

        public T Value
        {
            get
            {
                if (m_value == null)
                    Interlocked.CompareExchange(
                        ref m_value, new Boxed(m_factory()), null);
                return m_value.m_value;
            }
        }
    }
}
