using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch14Ex02
{
   class Program
   {
      static void Main(string[] args)
      {
         var curries = new[]
         {
            new
            {
               MainIngredient = "Lamb",
               Style = "Dhansak",
               Spiciness = 5
            },
            new
            {
               MainIngredient = "Lamb",
               Style = "Dhansak",
               Spiciness = 5
            },
            new
            {
               MainIngredient = "Chicken",
               Style = "Dhansak",
               Spiciness = 5
            }
         };
         Console.WriteLine(curries[0].ToString());
         Console.WriteLine(curries[0].GetHashCode());
         Console.WriteLine(curries[1].GetHashCode());
         Console.WriteLine(curries[2].GetHashCode());
         Console.WriteLine(curries[0].Equals(curries[1]));
         Console.WriteLine(curries[0].Equals(curries[2]));
         Console.WriteLine(curries[0] == curries[1]);
         Console.WriteLine(curries[0] == curries[2]);

         Console.ReadKey();
      }
   }
}
