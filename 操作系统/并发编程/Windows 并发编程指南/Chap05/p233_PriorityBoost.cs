//+---------------------------------------------------------------+
// PriorityBoost.cs
// Chapter 5, page 233
//
// Illustration of priority boosting.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Collections.Generic;
using System.Threading;

namespace CPOW_DotNet.Chap05
{
    public static class PriorityBoost
    {
        /// <summary>
        /// An example that illustrates the effect of priority boosting.
        /// When run on a single CPU machine, t2's setting of the event will
        /// always boost t1 and (provided the threads are of equal priority)
        /// will force t1 to preempt t2.  This will lead to the output:
        /// 
        ///   t1: waiting
        ///   t2: setting
        ///   t1: woke up, acquiring lock
        ///   t2: done w/ set, leaving lock
        ///   t1: acquired lock
        ///   
        /// </summary>
        public static void IllustrateBoosting()
        {
            ManualResetEvent mre = new ManualResetEvent(false);
            object lockObj = new object();

            Thread t1 = new Thread(delegate()
            {
                Console.WriteLine("t1: waiting");
                mre.WaitOne();

                Console.WriteLine("t1: woke up, acquiring lock");
                lock (lockObj)
                    Console.WriteLine("t1: acquired lock");
            });
            t1.Start();
            Thread.Sleep(1000); // Allow 't1' to get scheduled.

            lock (lockObj)
            {
                Console.WriteLine("t2: setting");
                mre.Set();
                Console.WriteLine("t2: done w/ set, leaving lock");
            }

            t1.Join();
        }
    }
}