using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SimpleDispose
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Fun with Dispose *****\n");

            // Use a comma-delimited list to declare multiple objects to dispose.
            using (MyResourceWrapper rw = new MyResourceWrapper(),
                  rw2 = new MyResourceWrapper())
            {
                // Use rw and rw2 objects.
            }
        }

    }

}
