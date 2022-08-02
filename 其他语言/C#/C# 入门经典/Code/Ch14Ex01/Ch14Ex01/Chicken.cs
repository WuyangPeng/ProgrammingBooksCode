using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch14Ex01
{
   public class Chicken : Animal
   {
      public void LayEgg()
      {
         Console.WriteLine("{0} has laid an egg.", name);
      }

      public override void MakeANoise()
      {
          Console.WriteLine("{0} says 'cluck!'", name);
      }
   }
}
