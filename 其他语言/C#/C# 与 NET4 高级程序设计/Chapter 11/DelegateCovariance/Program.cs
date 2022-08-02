using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DelegateCovariance
{
    class Program
    {
        // Define a single delegate that may return a Car
        // or SportsCar.
        public delegate Car ObtainVehicalDelegate();

        public static Car GetBasicCar()
        { return new Car(); }

        public static SportsCar GetSportsCar()
        { return new SportsCar(); }

        static void Main(string[] args)
        {
            Console.WriteLine("***** Delegate Covariance *****\n");
            ObtainVehicalDelegate targetA = new ObtainVehicalDelegate(GetBasicCar);
            Car c = targetA();
            Console.WriteLine("Obtained a {0}", c);

            // Covariance allows this target assignment.
            ObtainVehicalDelegate targetB = new ObtainVehicalDelegate(GetSportsCar);
            SportsCar sc = (SportsCar)targetB();
            Console.WriteLine("Obtained a {0}", sc);
            Console.ReadLine();
        }
    }

}
