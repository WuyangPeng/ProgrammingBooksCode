using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VarianceDemo
{
   public class Chicken : Animal
   {
      public void LayEgg()
      {
         Console.WriteLine("{0} has laid an egg.", name);
      }

      public Chicken(string newName)
         : base(newName)
      {
      }

      public override void MakeANoise()
      {
          Console.WriteLine("{0} says 'cluck!'", name);
      }
   }
}
