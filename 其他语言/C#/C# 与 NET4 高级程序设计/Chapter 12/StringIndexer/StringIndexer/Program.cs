using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Data;

namespace StringIndexer
{

    public interface IStringContainer<Key>
    {
        string this[int Key] { get; set; }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Fun with Indexers *****\n");

            PeopleCollection myPeople = new PeopleCollection();

            myPeople["Homer"] = new Person("Homer", "Simpson", 40);
            myPeople["Marge"] = new Person("Marge", "Simpson", 38);

            // Get "Homer" and print data.
            Person homer = myPeople["Homer"];
            Console.WriteLine(homer.ToString());
            Console.ReadLine();
        }
    }
}
