using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BegVCSharp_24_2_NavigatingData
{
    class Program
    {
        static void Main(string[] args)
        {
            NORTHWNDEntities northWindEntities = new NORTHWNDEntities();

            var queryResults = from c in northWindEntities.Customers
                               where c.Country == "USA"
                               select new
                               {
                                   ID = c.CustomerID,
                                   Name = c.CompanyName,
                                   City = c.City,
                                   State = c.Region,
                                   Orders = c.Orders

                               };

            foreach (var item in queryResults)
            {

                Console.WriteLine(
                    "Customer: {0} {1}, {2}\n{3} orders:\tOrder ID\tOrder Date",
                       item.Name, item.City, item.State, item.Orders.Count
                );
                foreach (Order o in item.Orders)
                {
                    Console.WriteLine("\t\t{0}\t{1}", o.OrderID, o.OrderDate);
                }

            }
        }
    }
}
