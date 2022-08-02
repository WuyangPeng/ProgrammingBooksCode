//+---------------------------------------------------------------+
// SimpleAsyncResult.cs
// Chapter 8, page 414
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Threading;

// @TODO for 2e:
//    - Lazy initialize the MRE
//    - Don't leak the MRE

namespace CPOW_DotNet.Chap08
{
    public delegate T Func<T>();

    public class SimpleAsyncResult<T> : IAsyncResult
    {
        // All of the ordinary async result state.
        private volatile int m_isCompleted; // 0==not complete, 1==complete.
        private readonly ManualResetEvent m_asyncWaitHandle;
        private readonly AsyncCallback m_callback;
        private readonly object m_asyncState;

        // To hold the results, exceptional or ordinary.
        private Exception m_exception;
        private T m_result;

        public SimpleAsyncResult(
            Func<T> work, AsyncCallback callback, object state)
        {
            m_callback = callback;
            m_asyncState = state;
            m_asyncWaitHandle = new ManualResetEvent(false);

            RunWorkAsynchronously(work);
        }

        public bool IsCompleted
        {
            get { return (m_isCompleted == 1); }
        }

        // We always queue work asynchronously, so always return false.
        public bool CompletedSynchronously
        {
            get { return false; }
        }

        public WaitHandle AsyncWaitHandle
        {
            get { return m_asyncWaitHandle; }
        }

        public object AsyncState
        {
            get { return m_asyncState; }
        }

        // Runs the work on the thread pool, capturing exceptions,
        // results, and signaling completion.
        private void RunWorkAsynchronously(Func<T> work)
        {
            ThreadPool.QueueUserWorkItem(delegate
            {
                try
                {
                    m_result = work();
                }
                catch (Exception e)
                {
                    m_exception = e;
                }
                finally
                {
                    // Signal completion in the proper order:
                    m_isCompleted = 1;
                    m_asyncWaitHandle.Set();
                    if (m_callback != null)
                        m_callback(this);
                }
            });
        }

        // Helper function to end the result. Only safe to be called
        // once by one thread, ever.
        public T End()
        {
            // Wait for the work to finish, if it hasn't already.
            if (m_isCompleted == 0)
            {
                m_asyncWaitHandle.WaitOne();
                m_asyncWaitHandle.Close();
            }

            // Propagate any exceptions or return the result.
            if (m_exception != null)
                throw m_exception;

            return m_result;
        }
    }
}
