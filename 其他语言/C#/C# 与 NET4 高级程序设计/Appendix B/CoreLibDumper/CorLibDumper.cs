// CoreLibDumper.cs
using System;
using System.Reflection;
using System.IO;

// Define assembly version.
[assembly:AssemblyVersion("1.0.0.0")]

namespace CorLibDumper
{
  public class TypeDumper
  {
    public static bool DumpTypeToFile(string typeToDisplay)
    {
      // Attempt to load type into memory.
      Type theType = null;
      try
      {
         // Throw exception if we can't find it.
         theType = Type.GetType(typeToDisplay, true);
      } catch { return false; }

      // Create local *.txt file.
      using(StreamWriter sw =
         File.CreateText(string.Format("{0}.txt",
         theType.FullName)))
      {
        // Now dump type to file.
        sw.WriteLine("Type Name: {0}", theType.FullName);
        sw.WriteLine("Members:");
        foreach(MemberInfo mi in theType.GetMembers())
          sw.WriteLine("\t-> {0}", mi.ToString());

      }
      return true;
    }
  }
}
