using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BegVCSharp_23_5_LargeNumberQuery
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] numbers = generateLotsOfNumbers(12345678);

            Console.WriteLine("Numbers less than 1000:");

            var queryResults =
                from n in numbers
                where n < 1000
                select n
                ;      

            foreach (var item in queryResults)
            {
                Console.WriteLine(item);
            }
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
                //Console.WriteLine(i + " " + result[i]);
            }
            return result;
        }
    }
}
