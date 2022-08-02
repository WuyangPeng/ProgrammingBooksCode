using System;
//+---------------------------------------------------------------+
// SimpleAsyncOperation.cs
// Chapter 8, page 417-418
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System.Threading;

namespace CPOW_DotNet.Chap08
{
    public class SimpleAsyncOperation
    {
        public int Work(int sleepyTime)
        {
            Thread.Sleep(sleepyTime);
            return new Random().Next();
        }

        public IAsyncResult BeginWork(
            int sleepyTime, AsyncCallback callback, object state)
        {
            return new SimpleAsyncResult<int>(
                delegate { return Work(sleepyTime); },
                callback,
                state
            );
        }

        public int EndWork(IAsyncResult asyncResult)
        {
            SimpleAsyncResult<int> simpleResult =
                asyncResult as SimpleAsyncResult<int>;

            if (simpleResult == null)
                throw new ArgumentException("Bad async result.");

            return simpleResult.End();
        }
    }
}
