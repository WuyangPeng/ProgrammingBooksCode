using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PrimAndProperCarEvents
{
    public class CarEventArgs : EventArgs
    {
        public readonly string msg;
        public CarEventArgs(string message)
        {
            msg = message;
        }
    }

}
