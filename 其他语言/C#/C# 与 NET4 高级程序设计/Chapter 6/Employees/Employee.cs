using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Employees
{
    abstract partial class Employee
    {
        // Field data.
        private string empName;
        private int empID;
        private float currPay;
        private int empAge;
        private string empSSN;
        private static string companyName;

        // Contain a BenefitPackage object.
        protected BenefitPackage empBenefits = new BenefitPackage();

        // Expose certain benefit behaviors of object.
        public double GetBenefitCost()
        { return empBenefits.ComputePayDeduction(); }

        // Expose object through a custom property.
        public BenefitPackage Benefits
        {
            get { return empBenefits; }
            set { empBenefits = value; }
        }

        #region Methods
        public virtual void GiveBonus(float amount)
        { Pay += amount; }

        public virtual void DisplayStats()
        {
            Console.WriteLine("Name: {0}", Name);
            Console.WriteLine("ID: {0}", ID);
            Console.WriteLine("Age: {0}", Age);
            Console.WriteLine("Pay: {0}", Pay);
            Console.WriteLine("SSN: {0}", SocialSecurityNumber);
        }

        // This would be a compiler error if you uncomment,
        // as the SocialSecurityNumber property resolves to 
        // these methods internally!
        //public string get_SocialSecurityNumber()
        //{
        //    return empSSN;
        //}
        //public void set_SocialSecurityNumber(string ssn)
        //{
        //    empSSN = ssn;
        //}

        #endregion

        // BenefitPackage nests BenefitPackageLevel.
        public class BenefitPackage
        {
            public enum BenefitPackageLevel
            {
                Standard, Gold, Platinum
            }
            public double ComputePayDeduction()
            {
                return 125.0;
            }
        }

    }
}
