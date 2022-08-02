using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DynamicKeyword
{
    #region Simple person class
    class Person
    {
        public string FirstName { get; set; }
        public string LastName { get; set; }
    }
    #endregion

    #region Very dynamic class!
    class VeryDynamicClass
    {
        // A dynamic field.
        private static dynamic myDynamicField;

        // A dynamic property.
        public dynamic DynamicProperty { get; set; }

        // A dynamic return type and a dynamic paramater type.
        public dynamic DynamicMethod(dynamic dynamicParam)
        {
            // A dynamic local variable.
            dynamic dynamicLocalVar = "Local variable";

            int myInt = 10;

            if (dynamicParam is int)
            {
                return dynamicLocalVar;
            }
            else
            {
                return myInt;
            }
        }
    }
    #endregion

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Fun with the dynamic keyword *****");
            ImplicitlyTypedVariable();
            Console.WriteLine();

            UseObjectVarible();
            Console.WriteLine();

            PrintThreeStrings();
            Console.WriteLine();

            ChangeDynamicDataType();
            Console.WriteLine();

            InvokeMembersOnDynamicData();
            Console.WriteLine();

            Console.ReadLine();
        }

        #region Implicit typing review...
        static void ImplicitlyTypedVariable()
        {
            // a is of type List<int>.
            var a = new List<int>();
            a.Add(90);

            // This would be an error!
            // a = "Hello";
        }
        #endregion

        #region Object has reference review...
        static void UseObjectVarible()
        {
            // Assume we have a class named Person. 
            object o = new Person() { FirstName = "Mike", LastName = "Larson" };

            // Must cast object as Person to gain access 
            // to the Person properties. 
            Console.WriteLine("Person's first name is {0}", ((Person)o).FirstName);
        }
        #endregion

        #region implict, obj ref and dynamic string data
        static void PrintThreeStrings()
        {
            var s1 = "Greetings";
            object s2 = "From";
            dynamic s3 = "Minneapolis";

            Console.WriteLine("s1 is of type: {0}", s1.GetType());
            Console.WriteLine("s2 is of type: {0}", s2.GetType());
            Console.WriteLine("s3 is of type: {0}", s3.GetType());
        }
        #endregion

        #region Change a dynamic local variable on the fly. 
        static void ChangeDynamicDataType()
        {
            // Declare a single dynamic data point
            // named 't'.
            dynamic t = "Hello!";
            Console.WriteLine("t is of type: {0}", t.GetType());

            t = false;
            Console.WriteLine("t is of type: {0}", t.GetType());

            t = new List<int>();
            Console.WriteLine("t is of type: {0}", t.GetType());
        }
        #endregion

        #region Invoke members on dynamic data
        static void InvokeMembersOnDynamicData()
        {
            dynamic textData1 = "Hello";

            try
            {
                Console.WriteLine(textData1.ToUpper());
                Console.WriteLine(textData1.toupper());
                Console.WriteLine(textData1.Foo(10, "ee", DateTime.Now));
            }
            catch (Microsoft.CSharp.RuntimeBinder.RuntimeBinderException ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
        #endregion

    }
}
