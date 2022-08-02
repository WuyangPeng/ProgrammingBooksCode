using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VariableScopeInLoops
{
   class Program
   {
      static void Main(string[] args)
      {
         int i;
         string text = "";
         for (i = 0; i < 10; i++)
         {
            text = "Line " + Convert.ToString(i);
            Console.WriteLine("{0}", text);
         }
         Console.WriteLine("Last text output in loop: {0}", text);

         Console.ReadKey();
      }
   }
}
