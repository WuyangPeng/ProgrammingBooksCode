using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch11Ex02
{
   class Program
   {
      static void Main(string[] args)
      {
         Animals animalCollection = new Animals();
         animalCollection.Add(new Cow("Jack"));
         animalCollection.Add(new Chicken("Vera"));
         foreach (Animal myAnimal in animalCollection)
         {
            myAnimal.Feed();
         }
         Console.ReadKey();
      }
   }
}
