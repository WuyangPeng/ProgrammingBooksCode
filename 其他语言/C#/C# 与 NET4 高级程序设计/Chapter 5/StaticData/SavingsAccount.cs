using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StaticData
{
    // A simple savings account class.
    class SavingsAccount
    {
        public double currBalance;

        // A static point of data.
        public static double currInterestRate = 0.04;

        public SavingsAccount(double balance)
        {
            currBalance = balance;
        }

        // A static constructor!
        static SavingsAccount()
        {
            Console.WriteLine("In static ctor!");
            currInterestRate = 0.04;
        }

        // Static members to get/set interest rate.
        public static void SetInterestRate(double newRate)
        { currInterestRate = newRate; }

        public static double GetInterestRate()
        { return currInterestRate; }

    }
}
