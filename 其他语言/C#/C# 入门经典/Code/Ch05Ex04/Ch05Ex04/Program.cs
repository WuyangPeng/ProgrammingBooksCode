using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch05Ex04
{
   class Program
   {
      static void Main(string[] args)
      {
         string[] friendNames = {"Robert Barwell", "Mike Parry",
                                 "Jeremy Beacock"};
         int i;
         Console.WriteLine("Here are {0} of my friends:",
                           friendNames.Length);
         for (i = 0; i <= friendNames.Length; i++)
         {
            Console.WriteLine(friendNames[i]);
         }
         Console.ReadKey();
      }
   }
}
