using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SimpleDelegate
{
    // This delegate can point to any method,
    // taking two integers and returning an integer.
    public delegate int BinaryOp(int x, int y); 

    #region SimpleMath class
    // This class contains methods BinaryOp will
    // point to.
    public class SimpleMath
    {
        public int Add(int x, int y)
        { return x + y; }
        public int Subtract(int x, int y)
        { return x - y; }
        public static int SquareNumber(int a)
        { return a * a; }
    }
    #endregion

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Simple Delegate Example *****\n");

            // Error! Method does not match delegate pattern!
            // BinaryOp b2 = new BinaryOp(SimpleMath.SquareNumber);

            // .NET delegates can also point to instance methods as well.
            SimpleMath m = new SimpleMath();
            BinaryOp b = new BinaryOp(m.Add);

            DisplayDelegateInfo(b);

            // Invoke Add() method indirectly using delegate object.
            Console.WriteLine("10 + 10 is {0}", b.Invoke(10, 10));
            Console.ReadLine();
        }

        #region Helper method to display what a delegate is pointing to.
        static void DisplayDelegateInfo(Delegate delObj)
        {
            // Print the names of each member in the
            // delegate's invocation list.
            foreach (Delegate d in delObj.GetInvocationList())
            {
                Console.WriteLine("Method Name: {0}", d.Method);
                Console.WriteLine("Type Name: {0}", d.Target);
            }
        }
        #endregion
    }
}

