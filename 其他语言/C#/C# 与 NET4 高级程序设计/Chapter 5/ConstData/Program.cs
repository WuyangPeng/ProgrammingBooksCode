using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConstData
{
    class MyMathClass
    {
        public static readonly double PI;

        static MyMathClass()
        { PI = 3.14; }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Fun with Const *****\n");
            Console.WriteLine("The value of PI is: {0}", MyMathClass.PI);

            // Error! Can't change a constant!
            // MyMathClass.PI = 3.1444;

            Console.ReadLine();
        }

        // This is just for a test.
        static void LocalConstStringVariable()
        {
            // A local constant data point can be directly accessed.
            const string fixedStr = "Fixed string Data";
            Console.WriteLine(fixedStr);

            // Error!
            // fixedStr = "This will not work!";
        }

    }
}

