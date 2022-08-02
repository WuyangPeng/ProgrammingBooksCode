using System;
using System.Collections.Generic;
using System.Xml.Linq;
using System.Text;

namespace BegVCSharp_24_4_SaveLoadXML
{
    class Program
    {
        static void Main(string[] args)
        {
                        XDocument xdoc = new XDocument(
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
                )
            );
            string xmlFileName = @"c:\BegVCSharp\Chapter24\Xml\example2.xml";
     
            xdoc.Save(xmlFileName);
     
            XDocument xdoc2 = XDocument.Load(xmlFileName);
     
            Console.WriteLine("Contents of xdoc2:");
            Console.WriteLine(xdoc2);
     
            Console.Write("Program finished, press Enter/Return to continue:");
            Console.ReadLine();

        }
    }
}
