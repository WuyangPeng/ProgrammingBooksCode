using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;

namespace MyExtensionMethods
{
  #region MyExtensions type
  static class MyExtensions
  {
    // This method allows any object to display the assembly 
    // it is defined in.
    public static void DisplayDefiningAssembly(this object obj)
    {
      Console.WriteLine("{0} lives here: => {1}\n", obj.GetType().Name,
          Assembly.GetAssembly(obj.GetType()).GetName().Name);
    }

    // This method allows any any integer to reverse its digits.
    // for example, 56 would return 65.
    public static int ReverseDigits(this int i)
    {
      // Translate int into a string, and then
      // get all the characters. 
      char[] digits = i.ToString().ToCharArray();

      // Now reverse items in the array.
      Array.Reverse(digits);

      // Put back into string.
      string newDigits = new string(digits);

      // Finally, return the modified string back as an int.
      return int.Parse(newDigits);
    }
  }
  #endregion

  #region TesterUtilClass type
  static class TesterUtilClass
  {
    // Every Int32 now has a Foo() method...
    public static void Foo(this int i)
    { Console.WriteLine("{0} called the Foo() method.", i); }

    // ...which has been overloaded to take a string!
    public static void Foo(this int i, string msg)
    { Console.WriteLine("{0} called Foo() and told me: {1}", i, msg); }
  }
  #endregion
}