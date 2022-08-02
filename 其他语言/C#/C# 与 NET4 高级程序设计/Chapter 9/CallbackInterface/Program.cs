using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CallbackInterface
{
    class Program
    {
        // Make a car and listen to the events.
        static void Main(string[] args)
        {
            Console.WriteLine("***** Interfaces as event enablers *****\n");
            Car c1 = new Car("SlugBug", 100, 10);

            // Make 2 sink objects.
            Console.WriteLine("***** Creating sinks *****");
            CarEventSink sink = new CarEventSink("First sink");
            CarEventSink myOtherSink = new CarEventSink("Other sink");

            // Hand sinks to Car.
            Console.WriteLine("\n***** Sending 2 sinks into Car *****");
            c1.Advise(sink);
            c1.Advise(myOtherSink);

            // Speed up (this will generate the events).
            Console.WriteLine("\n***** Speeding up *****");
            for (int i = 0; i < 10; i++)
                c1.Accelerate(20);

            // Detach first sink from events.
            Console.WriteLine("\n***** Removing first sink *****");
            c1.Unadvise(sink);

            // Speed up again (only myOtherSink will be called).
            Console.WriteLine("\n***** Speeding up again *****");
            for (int i = 0; i < 10; i++)
                c1.Accelerate(20);

            // Detach other sink from events.
            Console.WriteLine("\n***** Removing second sink *****");
            c1.Unadvise(myOtherSink);
            Console.ReadLine();
        }


    }
}
