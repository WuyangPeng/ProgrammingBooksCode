using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DictionaryAnimals
{
   class Program
   {
      static void Main(string[] args)
      {
         Animals animalCollection = new Animals();
         animalCollection.Add("Rosie", new Cow("Rosie"));
         animalCollection.Add("Tyrone", new Chicken("Tyrone"));
         animalCollection.Add("Jason", new Chicken("Jason"));
         animalCollection.Add("Molly", new Cow("Molly"));

         foreach (Animal myAnimal in animalCollection)
         {
            Console.WriteLine("New {0} object added to custom collection, " +
                              "Name = {1}", myAnimal.ToString(), myAnimal.Name);
         }

         Console.ReadKey();
      }
   }
}
