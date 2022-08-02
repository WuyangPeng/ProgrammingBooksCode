using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch11Ex03
{
   class Program
   {
      static void Main(string[] args)
      {
         Primes primesFrom2To1000 = new Primes(2, 1000);
         foreach (long i in primesFrom2To1000)
            Console.Write("{0} ", i);

         Console.ReadKey();
      }
   }
}
