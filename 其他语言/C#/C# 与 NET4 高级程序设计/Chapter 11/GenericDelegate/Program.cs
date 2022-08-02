using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GenericDelegate
{
    // This generic delegate can call any method
    // returning void and taking a single type parameter.
    public delegate void MyGenericDelegate<T>(T arg);
    public delegate void MyDelegate(object arg);

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Generic Delegates *****\n");

            // Register targets.
            MyGenericDelegate<string> strTarget =
              new MyGenericDelegate<string>(StringTarget);
            strTarget("Some string data");

            MyGenericDelegate<int> intTarget =
              new MyGenericDelegate<int>(IntTarget);
            intTarget(9);

            MyDelegate d = new MyDelegate(MyTarget);
            d("More string data");

            // Method group conversion syntax.
            MyDelegate d2 = MyTarget;
            d2(9);  // Boxing penalty.
            Console.ReadLine();     
        }

        #region Targets for delegates
        static void StringTarget(string arg)
        {
            Console.WriteLine("arg in uppercase is: {0}", arg.ToUpper());
        }

        static void IntTarget(int arg)
        {
            Console.WriteLine("++arg is: {0}", ++arg);
        }

        // Due to a lack of type safety, we must
        // determine the underlying type before casting.
        static void MyTarget(object arg)
        {
            if (arg is int)
            {
                int i = (int)arg;  // Unboxing penalty.
                Console.WriteLine("++arg is: {0}", ++i);
            }

            if (arg is string)
            {
                string s = (string)arg;
                Console.WriteLine("arg in uppercase is: {0}", s.ToUpper());
            }
        }

        #endregion
    }
}

