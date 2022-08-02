using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch12Ex04
{
    class Program
    {
        static void Main(string[] args)
        {
            Farm<Animal> farm = new Farm<Animal>();
            farm.Animals.Add(new Cow("Jack"));
            farm.Animals.Add(new Chicken("Vera"));
            farm.Animals.Add(new Chicken("Sally"));
            farm.Animals.Add(new SuperCow("Kevin"));
            farm.MakeNoises();

            Farm<Cow> dairyFarm = farm.GetCows();
            dairyFarm.FeedTheAnimals();

            foreach (Cow cow in dairyFarm)
            {
                if (cow is SuperCow)
                {
                    (cow as SuperCow).Fly();
                }
            }
            Console.ReadKey();

            #region Code for "Generic Operators" section
            //Farm<Animal> newFarm = farm + dairyFarm;
            #endregion

            #region Code for "Generic Operators" section
            //Farm<Cow> anotherDairyFarm = farm.GetSpecies<Cow>();
            //Farm<Chicken> poultryFarm = farm.GetSpecies<Chicken>();
            #endregion
        }
    }
}
