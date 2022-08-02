using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch12Ex01
{
    class Program
    {
        static void Main(string[] args)
        {
            Vector v1 = GetVector("vector1");
            Vector v2 = GetVector("vector1");
            Console.WriteLine("{0} + {1} = {2}", v1, v2, v1 + v2);
            Console.WriteLine("{0} - {1} = {2}", v1, v2, v1 - v2);
            Console.ReadKey();
        }

        static Vector GetVector(string name)
        {
            Console.WriteLine("Input {0} magnitude:", name);
            double? r = GetNullableDouble();
            Console.WriteLine("Input {0} angle (in degrees):", name);
            double? theta = GetNullableDouble();
            return new Vector(r, theta);
        }

        static double? GetNullableDouble()
        {
            double? result;
            string userInput = Console.ReadLine();
            try
            {
                result = double.Parse(userInput);
            }
            catch
            {
                result = null;
            }
            return result;
        }
    }
}
