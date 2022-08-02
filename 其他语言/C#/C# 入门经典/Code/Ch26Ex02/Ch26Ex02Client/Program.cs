using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using Ch26Ex02Contracts;

namespace Ch26Ex02Client
{
   class Program
   {
      static void Main(string[] args)
      {
         Person[] people = new Person[]
         {
            new Person { Mark = 46, Name="Jim" },
            new Person { Mark = 73, Name="Mike" },
            new Person { Mark = 92, Name="Stefan" },
            new Person { Mark = 84, Name="George" },
            new Person { Mark = 24, Name="Arthur" },
            new Person { Mark = 58, Name="Nigel" }
         };

         Console.WriteLine("People:");
         OutputPeople(people);

         IAwardService client = ChannelFactory<IAwardService>.CreateChannel(
            new WSHttpBinding(),
            new EndpointAddress("http://localhost:51425/AwardService.svc"));
         client.SetPassMark(70);
         Person[] awardedPeople = client.GetAwardedPeople(people);

         Console.WriteLine();
         Console.WriteLine("Awarded people:");
         OutputPeople(awardedPeople);

         Console.ReadKey();
      }

      static void OutputPeople(Person[] people)
      {
         foreach (Person person in people)
         {
            Console.WriteLine("{0}, mark: {1}", person.Name, person.Mark);
         }
      }
   }
}
