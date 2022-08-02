using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VarianceDemo
{
    public class SuperCow : Cow
    {
        public void Fly()
        {
            Console.WriteLine("{0} is flying!", name);
        }

        public SuperCow(string newName)
            : base(newName)
        {
        }

        public override void MakeANoise()
        {
            Console.WriteLine("{0} says 'here I come to save the day!'", name);
        }
    }
}
