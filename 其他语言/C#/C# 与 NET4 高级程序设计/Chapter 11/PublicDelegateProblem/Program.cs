using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PublicDelegateProblem
{
    #region Simple Car & public delegate
    public class Car
    {
        public delegate void CarEngineHandler(string msgForCaller);

        // Now a public member!
        public CarEngineHandler listOfHandlers;

        // Just fire out the Exploded notification.
        public void Accelerate(int delta)
        {
            if (listOfHandlers != null)
                listOfHandlers("Sorry, this car is dead...");
        }
    } 
    #endregion

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Agh!  No Encapsulation! *****\n");
            // Make a Car.
            Car myCar = new Car();

            // We have direct access to the delegate!
            myCar.listOfHandlers = new Car.CarEngineHandler(CallWhenExploded);
            myCar.Accelerate(10);

            // We can now assign to a whole new object...
            // confusing at best.
            myCar.listOfHandlers = new Car.CarEngineHandler(CallHereToo);
            myCar.Accelerate(10);

            // The caller can also directly invoke the delegate!
            myCar.listOfHandlers.Invoke("hee, hee, hee...");

            Console.ReadLine();
        }

        #region Targets for delegates
        static void CallWhenExploded(string msg)
        { Console.WriteLine(msg); }

        static void CallHereToo(string msg)
        { Console.WriteLine(msg); }
        #endregion
    }
}
