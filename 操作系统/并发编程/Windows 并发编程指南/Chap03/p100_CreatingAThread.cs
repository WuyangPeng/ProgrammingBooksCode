//+---------------------------------------------------------------+
// CreatingAThread.cs
// Chapter 3, page 100, 101
//
// Listing 3.2 and related snippets which create new threads.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Threading;

namespace CPOW_DotNet.Chap03
{
    public static class CreatingAThread
    {
        /// <summary>
        /// Listing 3.2, on page 100.
        /// </summary>
        public static void ExampleWithDelegates()
        {
            Thread newThread = new Thread(
                new ParameterizedThreadStart(MyThreadStart));

            Console.WriteLine("{0}: Created thread (ID {1})",
                Thread.CurrentThread.ManagedThreadId,
                newThread.ManagedThreadId);

            newThread.Start("Hello world"); // Begin execution.

            newThread.Join(); // Wait for the thread to finish.

            Console.WriteLine("{0}: Thread exited",
                Thread.CurrentThread.ManagedThreadId);
        }

        private static void MyThreadStart(object obj)
        {
            Console.WriteLine("{0}: Running: {1}",
                Thread.CurrentThread.ManagedThreadId, obj);
        }

        /// <summary>
        /// Subsequent example using anonymous delegates, page 100.
        /// </summary>
        public static void ExampleWithAnonymousDelegates()
        {
            Thread newThread = new Thread(delegate(object obj)
            {
                Console.WriteLine("{0}: Running {1}",
                    Thread.CurrentThread.ManagedThreadId, obj);
            });
            newThread.Start("Hello world (with anon delegates)");
            newThread.Join();
        }

        /// <summary>
        /// Subsequent example using C# 3.0 lambdas, page 101.
        /// </summary>
        public static void ExampleWithLambdas()
        {
            Thread newThread = new Thread(obj =>
                Console.WriteLine("{0}: Running {1}",
                    Thread.CurrentThread.ManagedThreadId, obj)
            );
            newThread.Start("Hello world (with lambdas)");
            newThread.Join();
        }
   
    }
}