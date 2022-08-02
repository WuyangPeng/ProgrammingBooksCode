using System;
// Import our custom namespace.
using MyExtensionsLibrary;

namespace MyExtnesionsLibraryClient
{
  class Program
  {
    static void Main(string[] args)
    {
      Console.WriteLine("***** Using Library with Extensions *****\n");

      // This time, these extension methods 
      // have been defined within an external
      // .NET class library.
      int myInt = 987;
      myInt.DisplayDefiningAssembly();
      Console.WriteLine("{0} is reversed to {1}",
        myInt, myInt.ReverseDigits());
      Console.ReadLine();
    }
  }
}

