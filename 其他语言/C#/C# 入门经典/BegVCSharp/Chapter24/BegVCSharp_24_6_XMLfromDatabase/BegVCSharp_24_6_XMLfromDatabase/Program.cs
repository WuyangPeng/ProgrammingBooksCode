using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml.Linq;
using System.Text;

namespace BegVCSharp_24_6_XMLfromDatabase
{
    class Program
    {
        static void Main(string[] args)
        {
            NORTHWNDEntities northWindEntities = new NORTHWNDEntities();
     
            XElement northwindCustomerOrders =
               new XElement("customers",
                from c in northWindEntities.Customers.AsEnumerable()
                select new XElement("customer",
                   new XAttribute("ID", c.CustomerID),
                   new XAttribute("City", c.City),
                   new XAttribute("Company", c.CompanyName),
                     from o in c.Orders
                     select new XElement("order",
                        new XAttribute("orderID", o.OrderID),
                        new XAttribute("orderDay",
                                o.OrderDate.Value.Day),
                        new XAttribute("orderMonth",
                                o.OrderDate.Value.Month),
                        new XAttribute("orderYear",
                                o.OrderDate.Value.Year),
                        new XAttribute("orderTotal",
                            o.Order_Details.Sum(od => od.Quantity * od.UnitPrice))
                      ) //end order
                 ) // end customer
            ); // end customers
     
            string xmlFileName =
                       @"C:\BegVCSharp\Chapter24\Xml\NorthwindCustomerOrders.xml";
            northwindCustomerOrders.Save(xmlFileName);
     
            Console.WriteLine("Successfully saved Northwind customer orders to:");
            Console.WriteLine(xmlFileName);
            Console.Write("Program finished, press Enter/Return to continue:");
            Console.ReadLine();

        }
    }
}
