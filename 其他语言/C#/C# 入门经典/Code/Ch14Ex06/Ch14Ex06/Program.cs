﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch14Ex06
{
   delegate int TwoIntegerOperationDelegate(int paramA, int paramB);

   class Program
   {
      static void PerformOperations(TwoIntegerOperationDelegate del)
      {
         for (int paramAVal = 1; paramAVal <= 5; paramAVal++)
         {
            for (int paramBVal = 1; paramBVal <= 5; paramBVal++)
            {
               int delegateCallResult = del(paramAVal, paramBVal);
               Console.Write("f({0},{1})={2}",
                  paramAVal, paramBVal, delegateCallResult);
               if (paramBVal != 5)
               {
                  Console.Write(", ");
               }
            }
            Console.WriteLine();
         }
      }

      static void Main(string[] args)
      {
         Console.WriteLine("f(a, b) = a + b:");
         PerformOperations((paramA, paramB) => paramA + paramB);
         Console.WriteLine();
         Console.WriteLine("f(a, b) = a * b:");
         PerformOperations((paramA, paramB) => paramA * paramB);
         Console.WriteLine();
         Console.WriteLine("f(a, b) = (a - b) % b:");
         PerformOperations((paramA, paramB) => (paramA - paramB)
            % paramB);
         Console.ReadKey();
      }
   }
}
