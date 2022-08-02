using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CustomGenericMethods
{
    #region generic helper class
    public static class MyGenericMethods
    {
        public static void Swap<T>(ref T a, ref T b)
        {
            Console.WriteLine("You sent the Swap() method a {0}",
              typeof(T));
            T temp;
            temp = a;
            a = b;
            b = temp;
        }

        public static void DisplayBaseClass<T>()
        {
            Console.WriteLine("Base class of {0} is: {1}.",
              typeof(T), typeof(T).BaseType);
        }
    }
    #endregion

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Fun with Custom Generic Methods *****\n");

            #region Swap data!
            // Swap 2 ints.
            int a = 10, b = 90;
            Console.WriteLine("Before swap: {0}, {1}", a, b);
            Swap<int>(ref a, ref b);
            Console.WriteLine("After swap: {0}, {1}", a, b);
            Console.WriteLine();

            // Swap 2 strings.
            string s1 = "Hello", s2 = "There";
            Console.WriteLine("Before swap: {0} {1}!", s1, s2);
            Swap<string>(ref s1, ref s2);
            Console.WriteLine("After swap: {0} {1}!", s1, s2);
            Console.WriteLine();

            // Compiler will infer System.Boolean.
            bool b1 = true, b2 = false;
            Console.WriteLine("Before swap: {0}, {1}", b1, b2);
            Swap(ref b1, ref b2);
            Console.WriteLine("After swap: {0}, {1}", b1, b2);
            Console.WriteLine();
            #endregion

            // Must supply type parameter if
            // the method does not take params.
            DisplayBaseClass<int>();
            DisplayBaseClass<string>();

            // Compiler error! No params? Must supply placeholder!
            // DisplayBaseClass();

            Console.ReadLine();
        }

        #region Generic methods
        // This method will swap any two items.
        // as specified by the type parameter <T>.
        static void Swap<T>(ref T a, ref T b)
        {
            Console.WriteLine("You sent the Swap() method a {0}", typeof(T));
            T temp;
            temp = a;
            a = b;
            b = temp;
        }

        static void DisplayBaseClass<T>()
        {
            // BaseType is a method used in reflection, 
            // which will be examined in Chapter 15
            Console.WriteLine("Base class of {0} is: {1}.",
              typeof(T), typeof(T).BaseType);
        }
        #endregion
    }
}
