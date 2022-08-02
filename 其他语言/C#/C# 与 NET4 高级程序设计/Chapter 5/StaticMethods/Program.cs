using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StaticMethods
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Fun with Static Methods *****\n");
            for (int i = 0; i < 5; i++)
                Console.WriteLine(Teenager.Complain());
            Console.ReadLine();
        }
    }
}
