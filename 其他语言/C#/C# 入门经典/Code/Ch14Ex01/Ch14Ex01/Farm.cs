using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch14Ex01
{
   public class Farm<T> : IEnumerable<T>
         where T : Animal
   {
      public void Add(T animal)
      {
         animals.Add(animal);
      }

      private List<T> animals = new List<T>();

      public List<T> Animals
      {
         get
         {
            return animals;
         }
      }

      public IEnumerator<T> GetEnumerator()
      {
         return animals.GetEnumerator();
      }

      IEnumerator IEnumerable.GetEnumerator()
      {
         return animals.GetEnumerator();
      }

      public void MakeNoises()
      {
         foreach (T animal in animals)
         {
            animal.MakeANoise();
         }
      }

      public void FeedTheAnimals()
      {
         foreach (T animal in animals)
         {
            animal.Feed();
         }
      }

      public Farm<Cow> GetCows()
      {
         Farm<Cow> cowFarm = new Farm<Cow>();
         foreach (T animal in animals)
         {
            if (animal is Cow)
            {
               cowFarm.Animals.Add(animal as Cow);
            }
         }
         return cowFarm;
      }

      #region Code for "Generic Operators" section
      //public static Farm<T> operator +(Farm<T> farm1, Farm<T> farm2)
      //{
      //    Farm<T> result = new Farm<T>();
      //    foreach (T animal in farm1)
      //    {
      //        result.Animals.Add(animal);
      //    }
      //    foreach (T animal in farm2)
      //    {
      //        if (!result.Animals.Contains(animal))
      //        {
      //            result.Animals.Add(animal);
      //        }
      //    }
      //    return result;
      //}

      //public static implicit operator Farm<Animal>(Farm<T> farm)
      //{
      //    Farm<Animal> result = new Farm<Animal>();
      //    foreach (T animal in farm)
      //    {
      //        result.Animals.Add(animal);
      //    }
      //    return result;
      //} 
      #endregion

      #region Code for "Generic Methods" section
      //public Farm<U> GetSpecies<U>() where U : T
      //{
      //    Farm<U> speciesFarm = new Farm<U>();
      //    foreach (T animal in animals)
      //    {
      //        if (animal is U)
      //        {
      //            speciesFarm.Animals.Add(animal as U);
      //        }
      //    }
      //    return speciesFarm;
      //} 
      #endregion

   }
}