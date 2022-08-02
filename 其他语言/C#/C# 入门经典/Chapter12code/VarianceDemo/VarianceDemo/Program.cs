using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VarianceDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            Cow myCow = new Cow("Geronimo");

            IMethaneProducer<Cow> cowMethaneProducer = myCow;
            IMethaneProducer<Animal> animalMethaneProducer = cowMethaneProducer;

            IGrassMuncher<Cow> cowGrassMuncher = myCow;
            IGrassMuncher<SuperCow> superCowGrassMuncher = cowGrassMuncher;

            List<Cow> cows = new List<Cow>();
            cows.Add(myCow);
            cows.Add(new SuperCow("Tonto"));
            cows.Add(new Cow("Gerald"));
            cows.Add(new Cow("Phil"));

            cows.Sort(new AnimalNameLengthComparer());

            ListAnimals(cows);

            Console.ReadKey();
        }

        static void ListAnimals(IEnumerable<Animal> animals)
        {
            foreach (Animal animal in animals)
            {
                Console.WriteLine(animal.Name);
            }
        }
    }
}
