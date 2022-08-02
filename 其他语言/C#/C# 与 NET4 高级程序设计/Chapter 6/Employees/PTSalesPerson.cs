using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Employees
{
    sealed class PTSalesPerson : SalesPerson
    {
        public PTSalesPerson(string fullName, int age, int empID,
         float currPay, string ssn, int numbOfSales)
            : base(fullName, age, empID, currPay, ssn, numbOfSales)
        {
        }

        // No bonus for you! Error!
        //public override void GiveBonus(float amount)
        //{
        //    // Rats. Can't change this method any further.
        //}
    }


}
