using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch14Ex07
{
   class Program
   {
      static void Main(string[] args)
      {
         string[] curries = { "pathia", "jalfreze", "korma" };
         Console.WriteLine(curries.Aggregate(
            (a, b) => a + " " + b));
         Console.WriteLine(curries.Aggregate<string, int>(
            0,
            (a, b) => a + b.Length));
         Console.WriteLine(curries.Aggregate<string, string, string>(
            "Some curries:",
            (a, b) => a + " " + b,
            a => a));
         Console.WriteLine(curries.Aggregate<string, string, int>(
            "Some curries:",
            (a, b) => a + " " + b,
            a => a.Length));
         Console.ReadKey();
      }
   }
}
