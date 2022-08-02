using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

using System.Reflection;
using MyExtensionMethods;

namespace ExtensionMethods
{
  class Program
  {
    static void Main(string[] args)
    {
      Console.WriteLine("***** Fun with Extension Methods *****\n");

      #region Display defining assembly extension
      // The int has assumed a new identity!
      int myInt = 12345678;
      myInt.DisplayDefiningAssembly();

      // So does this DataSet!
      System.Data.DataSet d = new System.Data.DataSet();
      d.DisplayDefiningAssembly();

      // And this MediaPlayer!
      System.Media.SoundPlayer sp = new System.Media.SoundPlayer();
      sp.DisplayDefiningAssembly();

      // Remember!  Extension methods can be called as normal static
      // methods. 
      MyExtensions.DisplayDefiningAssembly(false);
      #endregion

      #region New integer functionality
      // Use new integer functionality.
      Console.WriteLine("Value of myInt: {0}", myInt);
      Console.WriteLine("Reversed digits of myInt: {0}", myInt.ReverseDigits());
      myInt.Foo();
      myInt.Foo("Ints that Foo?  Who would have thought it!");
      #endregion

      UseCar();
      Console.ReadLine();
    }

    static void UseCar()
    {
      Car c = new Car();
      Console.WriteLine("Speed: {0}", c.SpeedUp());
      Console.WriteLine("Speed: {0}", c.SlowDown());
    }
  }
}
