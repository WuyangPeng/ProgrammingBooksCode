using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml.Linq;
using System.Text;

namespace BegVCSharp_24_7_QueryXML
{
    class Program
    {
        static void Main(string[] args)
        {
            string xmlFileName = @"C:\BegVCSharp\Chapter24\Xml\NorthwindCustomerOrders.xml";
   XDocument customers = XDocument.Load(xmlFileName);
     
   Console.WriteLine("Elements in loaded document:");
   var queryResult = from c in customers.Elements()
                     select c.Name;
   foreach (var item in queryResult)
   {
       Console.WriteLine(item);
   }
   Console.Write("Press Enter/Return to continue:");
   Console.ReadLine();

        }
    }
}
