using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch12Ex04
{
   public class Cow : Animal
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
