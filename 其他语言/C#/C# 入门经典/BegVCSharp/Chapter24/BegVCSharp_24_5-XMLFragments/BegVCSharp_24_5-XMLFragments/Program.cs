using System;
using System.Collections.Generic;
using System.Xml.Linq;
using System.Text;

namespace BegVCSharp_24_5_XMLFragments
{
    class Program
    {
        static void Main(string[] args)
        {
                        XElement xcust =
                new XElement("customers",
                    new XElement("customer",
                        new XAttribute("ID", "A"),
                        new XAttribute("City", "New York"),
                        new XAttribute("Region", "North America"),
                        new XElement("order",
                            new XAttribute("Item", "Widget"),
                            new XAttribute("Price", 100)
                      ),
                      new XElement("order",
                        new XAttribute("Item", "Tire"),
                        new XAttribute("Price", 200)
                      )
                    ),
                    new XElement("customer",
                        new XAttribute("ID", "B"),
                        new XAttribute("City", "Mumbai"),
                        new XAttribute("Region", "Asia"),
                        new XElement("order",
                             new XAttribute("Item", "Oven"),
                             new XAttribute("Price", 501)
                        )
                    )
                );

            string xmlFileName = @"c:\BegVCSharp\Chapter24\Xml\example3.xml";
            xcust.Save(xmlFileName);
     
            XElement xcust2 = XElement.Load(xmlFileName);
     
            Console.WriteLine("Contents of xcust:");
            Console.WriteLine(xcust);
     
            Console.Write("Program finished, press Enter/Return to continue:");
            Console.ReadLine();


        }
    }
}
