using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CallbackInterface
{
    // Car event sink.
    public class CarEventSink : IEngineNotification
    {
        private string name;
        public CarEventSink() { }
        public CarEventSink(string sinkName)
        { name = sinkName; }

        public void AboutToBlow(string msg)
        {
            Console.WriteLine("{0} reporting: {1}", name, msg);
        }
        public void Exploded(string msg)
        {
            Console.WriteLine("{0} reporting: {1}", name, msg);
        }
    }

}
