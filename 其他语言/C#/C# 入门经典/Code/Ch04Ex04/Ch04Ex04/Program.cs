using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch04Ex04
{
   class Program
   {
      static void Main(string[] args)
      {
         double balance, interestRate, targetBalance;
         Console.WriteLine("What is your current balance?");
         balance = Convert.ToDouble(Console.ReadLine());
         Console.WriteLine("What is your current annual interest rate (in %)?");
         interestRate = 1 + Convert.ToDouble(Console.ReadLine()) / 100.0;
         Console.WriteLine("What balance would you like to have?");
         targetBalance = Convert.ToDouble(Console.ReadLine());

         int totalYears = 0;
         do
         {
            balance *= interestRate;
            ++totalYears;
         }
         while (balance < targetBalance);
         Console.WriteLine("In {0} year{1} you’ll have a balance of {2}.",
                           totalYears, totalYears == 1 ? "" : "s", balance);
         Console.ReadKey();
      }
   }
}
