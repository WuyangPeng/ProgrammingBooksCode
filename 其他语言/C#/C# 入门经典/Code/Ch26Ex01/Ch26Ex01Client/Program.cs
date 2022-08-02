using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Ch26Ex01Client.ServiceReference1;

namespace Ch26Ex01Client
{
   class Program
   {
      static void Main(string[] args)
      {
         string numericInput = null;
         int intParam;
         do
         {
            Console.WriteLine(
               "Enter an integer and press enter to call the WCF service.");
            numericInput = Console.ReadLine();
         }
         while (!int.TryParse(numericInput, out intParam));
         Service1Client client = new Service1Client();
         Console.WriteLine(client.GetData(intParam));
         Console.WriteLine("Press an key to exit.");
         Console.ReadKey();
      }
   }
}
