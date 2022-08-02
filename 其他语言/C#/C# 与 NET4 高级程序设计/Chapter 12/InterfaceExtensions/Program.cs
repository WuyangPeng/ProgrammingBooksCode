using System;
using System.Collections.Generic;
using System.Text;

namespace InterfaceExtensions
{
  #region Types to represent basic math stuff
  // Define a normal CLR interface in C#.
  interface IBasicMath
  {
    int Add(int x, int y);
  }

  // Implementation of IBasicMath.
  class MyCalc : IBasicMath
  {
    public int Add(int x, int y)
    {
      return x + y;
    }
  }

  static class MathExtensions
  {
    // Extend IBasicMath this method and this
    // implementation.
    public static int Subtract(this IBasicMath itf,
      int x, int y)
    {
      return x - y;
    }
  }
  #endregion

  class Program
  {
    static void Main(string[] args)
    {
      Console.WriteLine("***** Extending an interface *****\n");

      // Call IBasicMath members from MyCalc object.
      MyCalc c = new MyCalc();
      Console.WriteLine("1 + 2 = {0}", c.Add(1, 2));
      Console.WriteLine("1 - 2 = {0}", c.Subtract(1, 2));

      // Can also cast into IBasicMath to invoke extension.
      Console.WriteLine("30 - 9 = {0}",
        ((IBasicMath)c).Subtract(30, 9));

      // This would NOT work!
      // IBasicMath itfBM = new IBasicMath();
      // itfBM.Subtract(10, 10);
      Console.ReadLine();
    }
  }
}
