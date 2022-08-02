using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch05Ex05
{
   class Program
   {
      static void Main(string[] args)
      {
         string myString = "This is a test.";
         char[] separator = {' '};
         string[] myWords;
         myWords = myString.Split(separator);
         foreach (string word in myWords)
         {
            Console.WriteLine("{0}", word);
         }
         Console.ReadKey();


      }
   }
}
