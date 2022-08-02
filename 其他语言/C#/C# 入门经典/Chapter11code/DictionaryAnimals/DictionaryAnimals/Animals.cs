using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DictionaryAnimals
{
   public class Animals : DictionaryBase
   {
      public void Add(string newID, Animal newAnimal)
      {
         Dictionary.Add(newID, newAnimal);
      }

      public void Remove(string animalID)
      {
         Dictionary.Remove(animalID);
      }

      public Animals()
      {
      }

      public Animal this[string animalID]
      {
         get
         {
            return (Animal)Dictionary[animalID];
         }
         set
         {
            Dictionary[animalID] = value;
         }
      }

      public new IEnumerator GetEnumerator()
      {
         foreach (object animal in Dictionary.Values)
            yield return (Animal)animal;
      }
   }
}
