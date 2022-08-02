using System;
using CorLibDumper;

namespace ConsoleClientApp
{
  public class Program
  {
    public static void Main()
    {
      Console.WriteLine(
         "***** The Type Dumper App *****\n");

      // Ask user for name of type.
      string typeName = "";
      Console.Write("Please enter type name: ");
      typeName = Console.ReadLine();

      // Now send it to the helper library.
      if(TypeDumper.DumpTypeToFile(typeName))
         Console.WriteLine("Data saved into {0}.txt",
         typeName);
      else
        Console.WriteLine("Error!  Can't find that type...");
    }
  }
}
