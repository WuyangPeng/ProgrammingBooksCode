using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

// Spacing added here so that line numbers match with the chapter description.




namespace Ch07Ex02
{
   class Program
   {
      static string[] eTypes = { "none", "simple", "index", "nested index" };

      static void Main(string[] args)
      {
         foreach (string eType in eTypes)
         {
            try
            {
               Console.WriteLine("Main() try block reached.");      // Line 23
               Console.WriteLine("ThrowException(\"{0}\") called.", eType); // Line 24
               ThrowException(eType);
               Console.WriteLine("Main() try block continues.");      // Line 26
            }
            catch (System.IndexOutOfRangeException e)                 // Line 28
            {
               Console.WriteLine("Main() System.IndexOutOfRangeException catch"
                                 + " block reached. Message:\n\"{0}\"",
                                 e.Message);
            }
            catch                                                   // Line 34
            {
               Console.WriteLine("Main() general catch block reached.");
            }
            finally
            {
               Console.WriteLine("Main() finally block reached.");
            }
            Console.WriteLine();
         }
         Console.ReadKey();
      }

      static void ThrowException(string exceptionType)
      {
         Console.WriteLine("ThrowException(\"{0}\") reached.", exceptionType); // Line 49
         switch (exceptionType)
         {
            case "none":
               Console.WriteLine("Not throwing an exception.");
               break;                                               // Line 54
            case "simple":
               Console.WriteLine("Throwing System.Exception.");
               throw (new System.Exception());                      // Line 57
            case "index":
               Console.WriteLine("Throwing System.IndexOutOfRangeException.");
               eTypes[4] = "error";                                 // Line 60
               break;
            case "nested index":
               try                                                  // Line 63
               {
                  Console.WriteLine("ThrowException(\"nested index\") " +
                                    "try block reached.");
                  Console.WriteLine("ThrowException(\"index\") called.");
                  ThrowException("index");                          // Line 68
               }
               catch                                                // Line 70
               {
                  Console.WriteLine("ThrowException(\"nested index\") general"
                                    + " catch block reached.");
                  //throw;
               }
               finally
               {
                  Console.WriteLine("ThrowException(\"nested index\") finally"
                                    + " block reached.");
               }
               break;
         }
      }
   }
}
