using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace OverflowCheck
{
   class Program
   {
      static void Main(string[] args)
      {
         byte destinationVar;
         short sourceVar = 281;
         destinationVar = checked((byte)sourceVar);
         Console.WriteLine("sourceVar val: {0}", sourceVar);
         Console.WriteLine("destinationVar val: {0}", destinationVar);

         Console.ReadKey();
      }
   }
}
