using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace Ch07Ex01Tracepoints
{
   class Program
   {
      static void Main(string[] args)
      {
         int[] testArray = { 4, 7, 4, 2, 7, 3, 7, 8, 3, 9, 1, 9 };
         int[] maxValIndices;
         int maxVal = Maxima(testArray, out maxValIndices);
         Console.WriteLine("Maximum value {0} found at element indices:",
                           maxVal);
         foreach (int index in maxValIndices)
         {
            Console.WriteLine(index);
         }
         Console.ReadKey();
      }

      static int Maxima(int[] integers, out int[] indices)
      {
         indices = new int[1];
         int maxVal = integers[0];
         indices[0] = 0;
         int count = 1;
         for (int i = 1; i < integers.Length; i++)
         {
            if (integers[i] > maxVal)
            {
               maxVal = integers[i];
               count = 1;
               indices = new int[1];
               indices[0] = i;
            }
            else
            {
               if (integers[i] == maxVal)
               {
                  count++;
                  int[] oldIndices = indices;
                  indices = new int[count];
                  oldIndices.CopyTo(indices, 0);
                  indices[count - 1] = i;
               }
            }
         }
         Trace.WriteLine(string.Format(
            "Maximum value {0} found, with {1} occurrences.", maxVal, count));
         return maxVal;
      }
   }
}
