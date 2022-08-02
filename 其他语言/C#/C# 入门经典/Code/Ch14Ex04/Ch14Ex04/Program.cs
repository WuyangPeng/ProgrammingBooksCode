using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch14Ex04
{
   class Program
   {
      static void Main(string[] args)
      {
         string sentence = "'twas brillig, and the slithy toves did gyre and gimble in the wabe:";
         List<string> words;

         words = WordProcessor.GetWords(sentence);
         Console.WriteLine("Original sentence:");
         foreach (string word in words)
         {
            Console.Write(word);
            Console.Write(' ');
         }

         Console.WriteLine('\n');

         words = WordProcessor.GetWords(sentence, reverseWords: true, capitalizeWords: true);
         Console.WriteLine("Capitalized sentence with reversed words:");
         foreach (string word in words)
         {
            Console.Write(word);
            Console.Write(' ');
         }

         Console.ReadKey();
      }
   }
}
