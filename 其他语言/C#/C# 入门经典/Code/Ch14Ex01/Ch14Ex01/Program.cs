using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch14Ex01
{
   class Program
   {
      static void Main(string[] args)
      {
         Farm<Animal> farm = new Farm<Animal>
    {
        new Cow { Name="Norris" },
        new Chicken { Name="Rita" },
        new Chicken(),
        new SuperCow { Name="Chesney" }
    };
         farm.MakeNoises();
         Console.ReadKey();
      }
   }
}
