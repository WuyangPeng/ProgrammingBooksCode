using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AutoProps
{
    class Garage
    {
        // The hidden backing field is set to zero!
        public int NumberOfCars { get; set; }

        // The hidden backing field is set to null!
        public Car MyAuto { get; set; }

        // Must use constructors to override default 
        // values assigned to hidden backing fields.
        public Garage()
        {
            MyAuto = new Car();
            NumberOfCars = 1;
        }
        public Garage(Car car, int number)
        {
            MyAuto = car;
            NumberOfCars = number;
        }
    }

}
