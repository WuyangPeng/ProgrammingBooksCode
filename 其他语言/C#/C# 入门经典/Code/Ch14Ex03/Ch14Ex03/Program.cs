using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.CSharp.RuntimeBinder;

namespace Ch14Ex03
{
   class MyClass1
   {
      public int Add(int var1, int var2)
      {
         return var1 + var2;
      }
   }

   class MyClass2
   {
   }

   class Program
   {
      static int callCount = 0;

      static dynamic GetValue()
      {
         if (callCount++ == 0)
         {
            return new MyClass1();
         }

         return new MyClass2();
      }

      static void Main(string[] args)
      {
         try
         {
            dynamic firstResult = GetValue();
            dynamic secondResult = GetValue();
            Console.WriteLine("firstResult is: {0}", firstResult.ToString());
            Console.WriteLine("secondResult is: {0}", secondResult.ToString());
            Console.WriteLine("firstResult call: {0}", firstResult.Add(2, 3));
            Console.WriteLine("secondResult call: {0}", secondResult.Add(2, 3));
         }
         catch (RuntimeBinderException ex)
         {
            Console.WriteLine(ex.Message);
         }

         Console.ReadKey();
      }
   }
}
