using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch11Ex05
{
    class Program
    {
        static void Main(string[] args)
        {
            ArrayList list = new ArrayList();
            list.Add(new Person("Jim", 30));
            list.Add(new Person("Bob", 25));
            list.Add(new Person("Bert", 27));
            list.Add(new Person("Ernie", 22));

            Console.WriteLine("Unsorted people:");
            for (int i = 0; i < list.Count; i++)
            {
                Console.WriteLine("{0} ({1})",
                   (list[i] as Person).Name, (list[i] as Person).Age);
            }
            Console.WriteLine();

            Console.WriteLine(
               "People sorted with default comparer (by age):");
            list.Sort();
            for (int i = 0; i < list.Count; i++)
            {
                Console.WriteLine("{0} ({1})",
                   (list[i] as Person).Name, (list[i] as Person).Age);
            }
            Console.WriteLine();

            Console.WriteLine(
               "People sorted with nondefault comparer (by name):");
            list.Sort(PersonComparerName.Default);
            for (int i = 0; i < list.Count; i++)
            {
                Console.WriteLine("{0} ({1})",
                   (list[i] as Person).Name, (list[i] as Person).Age);
            }

            Console.ReadKey();
        }
    }
}
