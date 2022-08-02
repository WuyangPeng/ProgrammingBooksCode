using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VarianceDemo
{
    public class Cow : Animal, IMethaneProducer<Cow>, IGrassMuncher<Cow>
    {
        public void Milk()
        {
            Console.WriteLine("{0} has been milked.", name);
        }

        public Cow(string newName)
            : base(newName)
        {
        }

        public override void MakeANoise()
        {
            Console.WriteLine("{0} says 'moo!'", name);
        }
    }
}
