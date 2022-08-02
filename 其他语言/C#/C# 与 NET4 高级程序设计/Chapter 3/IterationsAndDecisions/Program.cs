using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IterationsAndDecisions
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Loops and Choices *****");
            //ForAndForEachLoop();
            //VarInForeachLoop();
            //ExecuteWhileLoop();
            //ExecuteDoWhileLoop();
            //ExecuteIfElse();
            //ExecuteSwitch();
            ExecuteSwitchOnString();
            
            Console.ReadLine();
        }

        #region For / foreach loops
        // A basic for loop.
        static void ForAndForEachLoop()
        {
            // Note! "i" is only visible within the scope of the for loop.
            for (int i = 0; i < 4; i++)
            {
                Console.WriteLine("Number is: {0} ", i);
            }
            // "i" is not visible here.
            Console.WriteLine();

            string[] carTypes = { "Ford", "BMW", "Yugo", "Honda" };
            foreach (string c in carTypes)
                Console.WriteLine(c);
            Console.WriteLine();

            int[] myInts = { 10, 20, 30, 40 };
            foreach (int i in myInts)
                Console.WriteLine(i);
        }
        #endregion

        #region Var keyword in foreach
        static void VarInForeachLoop()
        {
            int[] myInts = { 10, 20, 30, 40 };

            // Use "var" in a standard foreach loop.
            foreach (var item in myInts)
            {
                Console.WriteLine("Item value: {0}", item);
            }
        }
        #endregion

        #region while loop
        static void ExecuteWhileLoop()
        {
            string userIsDone = "";

            // Test on a lower-class copy of the string.
            while (userIsDone.ToLower() != "yes")
            {
                Console.Write("Are you done? [yes] [no]: ");
                userIsDone = Console.ReadLine();
                Console.WriteLine("In while loop");
            }
        }
        #endregion

        #region do/while loop
        static void ExecuteDoWhileLoop()
        {
            string userIsDone = "";

            do
            {
                Console.WriteLine("In do/while loop");
                Console.Write("Are you done? [yes] [no]: ");
                userIsDone = Console.ReadLine();
            } while (userIsDone.ToLower() != "yes"); // Note the semicolon!
        }
        #endregion

        #region If/else
        static void ExecuteIfElse()
        {
            // This is illegal, given that Length returns an int, not a bool.
            string stringData = "My textual data";
            if (stringData.Length > 0)
            {
                Console.WriteLine("string is greater than 0 characters");
            }
        } 
        #endregion

        #region switch statements
        // Switch on a numerical value.
        static void ExecuteSwitch()
        {
            Console.WriteLine("1 [C#], 2 [VB]");
            Console.Write("Please pick your language preference: ");

            string langChoice = Console.ReadLine();
            int n = int.Parse(langChoice);

            switch (n)
            {
                case 1:
                    Console.WriteLine("Good choice, C# is a fine language.");
                    break;
                case 2:
                    Console.WriteLine("VB .NET: OOP, multithreading, and more!");
                    break;
                default:
                    Console.WriteLine("Well...good luck with that!");
                    break;
            }
        }

        static void ExecuteSwitchOnString()
        {
            Console.WriteLine("C# or VB");
            Console.Write("Please pick your language preference: ");

            string langChoice = Console.ReadLine();
            switch (langChoice)
            {
                case "C#":
                    Console.WriteLine("Good choice, C# is a fine language.");
                    break;
                case "VB":
                    Console.WriteLine("VB .NET: OOP, multithreading and more!");
                    break;
                default:
                    Console.WriteLine("Well...good luck with that!");
                    break;
            }
        }

        #endregion
    }
}
