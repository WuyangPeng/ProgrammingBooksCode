using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch04Ex02
{
   class Program
   {
      static void Main(string[] args)
      {
         string comparison;
         Console.WriteLine("Enter a number:");
         double var1 = Convert.ToDouble(Console.ReadLine());
         Console.WriteLine("Enter another number:");
         double var2 = Convert.ToDouble(Console.ReadLine());
         if (var1 < var2)
            comparison = "less than";
         else
         {
            if (var1 == var2)
               comparison = "equal to";
            else
               comparison = "greater than";
         }
         Console.WriteLine("The first number is {0} the second number.",
                           comparison);
         Console.ReadKey();
      }
   }
}
