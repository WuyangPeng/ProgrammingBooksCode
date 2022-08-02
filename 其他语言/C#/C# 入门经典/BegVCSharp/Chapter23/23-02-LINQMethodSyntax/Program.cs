using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BegVCSharp_23_2_LINQMethodSyntax
{
    class Program
    {
        static void Main(string[] args)
        {
            string[] names = { "Alonso", "Zheng", "Smith", "Jones", "Smythe", "Small", "Rodriguez", "Hsieh", "Jorgenson", "Ilyich", "Singh", "Samba", "Fatimah" };

            var queryResults = names.Where(n => n.StartsWith("S"));

            Console.WriteLine("Names beginning with S:");
            foreach (var item in queryResults)
            {
                Console.WriteLine(item);
            }

            Console.Write("Program finished, press Enter/Return to continue:");
            Console.ReadLine();

        }
    }
}
