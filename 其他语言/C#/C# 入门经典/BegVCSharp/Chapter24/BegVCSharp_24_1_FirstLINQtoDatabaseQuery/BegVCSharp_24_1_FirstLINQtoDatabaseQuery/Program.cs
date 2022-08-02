using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BegVCSharp_24_1_FirstLINQtoDatabaseQuery
{
    class Program
    {
        static void Main(string[] args)
        {
                 NORTHWNDEntities northWindEntities = new NORTHWNDEntities();
            
     var queryResults = from c in northWindEntities.Customers
                        where c.Country == "USA"
                        select new {
                                   ID=c.CustomerID,
                                   Name=c.CompanyName,
                                   City=c.City,
                                   State=c.Region
                               };
            foreach (var item in queryResults) {
                Console.WriteLine(item);
            };
            
            Console.WriteLine("Press Enter/Return to continue..");
            Console.ReadLine();

        }
    }
}
