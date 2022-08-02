#region Using directives

using System;
using System.Collections.Generic;
using System.Text;

#endregion

namespace DelegateCovariance
{
    public class Car
    {
        #region Basic Car state data / constructors
        // Internal state data.
        public int CurrentSpeed { get; set; }
        public int MaxSpeed { get; set; }
        public string PetName { get; set; }

        // Is the car alive or dead?
        private bool carIsDead;

        public Car()
        {
            MaxSpeed = 100;
        }

        public Car(string name, int maxSp, int currSp)
        {
            CurrentSpeed = currSp;
            MaxSpeed = maxSp;
            PetName = name;
        }
        #endregion

        #region Delegate infrastructure
        // 1) Define the delegate type.
        public delegate void CarEngineHandler(string msgForCaller);

        // 2) Define a member variable of the delegate.
        private CarEngineHandler listOfHandlers;

        // 3) Add registration functions for the caller.
        public void RegisterWithCarEngine(CarEngineHandler methodToCall)
        { listOfHandlers += methodToCall; }

        public void UnRegisterWithCarEngine(CarEngineHandler methodToCall)
        { listOfHandlers -= methodToCall; }
        #endregion

        #region Accelerate method
        public void Accelerate(int delta)
        {
            // If this car is 'dead', send dead message.
            if (carIsDead)
            {
                // Anybody listening?
                if (listOfHandlers != null)
                    listOfHandlers("Sorry, this car is dead...");
            }
            else
            {
                CurrentSpeed += delta;

                // Is this car 'almost dead'?
                if (10 == (MaxSpeed - CurrentSpeed)
                  && listOfHandlers != null)
                {
                    listOfHandlers("Careful buddy!  Gonna blow!");
                }

                if (CurrentSpeed >= MaxSpeed)
                    carIsDead = true;
                else
                    Console.WriteLine("CurrentSpeed = {0}", CurrentSpeed);
            }
        }
        #endregion
    }

    // No need to add any members here, 
    // just need a derived class to test.
    public class SportsCar : Car
    { }
}
