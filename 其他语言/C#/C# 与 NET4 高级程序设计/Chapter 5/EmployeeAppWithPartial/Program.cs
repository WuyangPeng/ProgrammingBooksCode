using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EmployeeAppWithPartial
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Fun with Partial Classes *****\n");
            Console.WriteLine("These folks work at {0}", Employee.Company);

            Employee emp = new Employee("Marvin", 456, 30000);
            emp.GiveBonus(1000);
            emp.DisplayStats();

            // Use the get/set methods to interact with the object's name.
            emp.Name = "Marv";
            Console.WriteLine("Employee is named: {0}", emp.Name);

            Employee emp2 = new Employee();
            // Longer than 15 characters!  Error will print to console. 
            emp2.Name = "Xena the warrior princess";

            Console.ReadLine();
        }
    }
}
