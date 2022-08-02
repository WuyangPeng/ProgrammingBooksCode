using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BegVCSharp_23_1_FirstLINQquery
{
    class Program
    {
        static void Main(string[] args)
        {
            string[] names = { "Alonso", "Zheng", "Smith", "Jones", "Smythe", "Small", "Ruiz", "Hsieh", "Jorgenson", "Ilyich", "Singh", "Samba", "Fatimah" };

            var queryResults =
                from n in names
                where n.StartsWith("S")
                select n;

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
