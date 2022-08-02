//+---------------------------------------------------------------+
// ImmutablePair.cs
// Chapter 2, page 36
//
// A straightforward immutable pair class.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

namespace CPOW_DotNet.Chap02
{
    public class ImmutablePair<T, U>
    {
        private readonly T m_first;
        private readonly U m_second;

        public ImmutablePair(T first, U second)
        {
            m_first = first;
            m_second = second;
        }

        public T First { get { return m_first; } }
        public U Second { get { return m_second; } }
    }
}
