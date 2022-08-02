using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch03Ex01
{
    class Program
    {
        static void Main(string[] args)
        {
            int myInteger;
            string myString;
            myInteger = 17;
            myString = "\"myInteger\" is";
            Console.WriteLine("{0} {1}.", myString, myInteger);
            Console.ReadKey();
        }
    }
}
