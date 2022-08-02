using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExtensionLib;

namespace Ch14Ex05
{
   class Program
   {
      static void Main(string[] args)
      {
         Console.WriteLine("Enter a string to convert:");
         string sourceString = Console.ReadLine();
         Console.WriteLine("String with title casing: {0}",
            sourceString.GetWords(capitalizeWords: true).AsSentence());
         Console.WriteLine("String backwards: {0}",
            sourceString.GetWords(reverseOrder: true, reverseWords: true).AsSentence());
         Console.WriteLine("String length backwards: {0}",
            sourceString.Length.ToStringReversed());
         Console.ReadKey();
      }
   }
}
