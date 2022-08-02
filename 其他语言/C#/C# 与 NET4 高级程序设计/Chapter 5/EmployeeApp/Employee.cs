using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EmployeeApp
{
    class Employee
    {
        // Field data.
        private string empName;
        private int empID;
        private float currPay;
        private int empAge;
        private string empSSN;
        private static string companyName;

        #region Constructors 
        public Employee() { }
        public Employee(string name, int id, float pay)
            :this(name, 0, id, pay, ""){}
        public Employee(string name, int age, int id, float pay, string ssn)
        {
            // Better!  Use properties when setting class data.
            // This reduces the amount of duplicate error checks.
            Name = name;
            Age = age;
            ID = id;
            Pay = pay;
            SocialSecurityNumber = ssn;
        }
        static Employee()
        {
            companyName = "Intertech Training";
        }

        #endregion

        #region Methods
        public void GiveBonus(float amount)
        { Pay += amount; }

        public void DisplayStats()
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

        #region Properties
        public static string Company
        {
            get { return companyName; }
            set { companyName = value; }
        }

        public string Name
        {
            get { return empName; }            
            set 
            {
                // Here, value is really a string.
                if (value.Length > 15)
                    Console.WriteLine("Error!  Name must be less than 16 characters!");
                else
                    empName = value;
            }
        }

        public int ID
        {
            get { return empID; }
            set { empID = value; }
        }

        public float Pay
        {
            get { return currPay; }
            set { currPay = value; }
        }

        public int Age
        {
            get { return empAge; }
            set { empAge = value; }
        }

        public string SocialSecurityNumber
        {
            get { return empSSN; }
            set { empSSN = value; }
        }

        #endregion
    }
}
