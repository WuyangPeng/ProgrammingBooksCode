using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SimpleClassExample
{
    #region Using constructor chaining
    //class Motorcycle
    //{
    //    public int driverIntensity;
    //    public string driverName;

    //    public void SetDriverName(string name)
    //    { this.driverName = name; }

    //    public void PopAWheely()
    //    {
    //        for (int i = 0; i <= driverIntensity; i++)
    //        {
    //            Console.WriteLine("Yeeeeeee Haaaaaeewww!");
    //        }
    //    }

    //    #region Constructors!
    //    // Constructor chaining.
    //    public Motorcycle()
    //    {
    //        Console.WriteLine("In default ctor");
    //    }

    //    public Motorcycle(int intensity)
    //        : this(intensity, "")
    //    {
    //        Console.WriteLine("In ctor taking an int");
    //    }

    //    public Motorcycle(string name)
    //        : this(0, name)
    //    {
    //        Console.WriteLine("In ctor taking a string");
    //    }

    //    // This is the 'master' constructor that does all the real work.
    //    public Motorcycle(int intensity, string name)
    //    {
    //        Console.WriteLine("In master ctor ");
    //        if (intensity > 10)
    //        {
    //            intensity = 10;
    //        }
    //        driverIntensity = intensity;
    //        driverName = name;
    //    }
    //    #endregion
    //}
    #endregion

    #region Using optional args
    class Motorcycle
    {
        public int driverIntensity;
        public string driverName;

        public void SetDriverName(string name)
        { this.driverName = name; }

        public void PopAWheely()
        {
            for (int i = 0; i <= driverIntensity; i++)
            {
                Console.WriteLine("Yeeeeeee Haaaaaeewww!");
            }
        }

        #region Single constructor using optional args    
        public Motorcycle(int intensity = 0, string name = "")
        {
            if (intensity > 10)
            {
                intensity = 10;
            }
            driverIntensity = intensity;
            driverName = name;
        }
        #endregion
    }

    #endregion

}
