using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch14Ex01
{
    public class SuperCow : Cow
    {
        public void Fly()
        {
            Console.WriteLine("{0} is flying!", name);
        }

        public override void MakeANoise()
        {
            Console.WriteLine("{0} says 'here I come to save the day!'", name);
        }
    }
}
