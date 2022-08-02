using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BegVCSharp_23_6_NumericAggregates
{
    class Program
    {
        static void Main(string[] args)
        {

            int[] numbers = generateLotsOfNumbers(12345678);

            Console.WriteLine("Numeric Aggregates");

            var queryResults =
                from n in numbers
                where n > 1000
                select n
               ;

            Console.WriteLine("Count of Numbers > 1000");
            Console.WriteLine(queryResults.Count());

            Console.WriteLine("Max of Numbers > 1000");
            Console.WriteLine(queryResults.Max());

            Console.WriteLine("Min of Numbers > 1000");
            Console.WriteLine(queryResults.Min());

            Console.WriteLine("Average of Numbers > 1000");
            Console.WriteLine(queryResults.Average());

            Console.WriteLine("Sum of Numbers > 1000");
            Console.WriteLine(queryResults.Sum(n => (long)n));

            Console.Write("Program finished, press Enter/Return to continue:");
            Console.ReadLine();
        }


        private static int[] generateLotsOfNumbers(int count)
        {
            Random generator = new Random(0);
            int[] result = new int[count];
            for (int i = 0; i < count; i++)
            {
                result[i] = generator.Next();
            }
            return result;
        }
    }
}
