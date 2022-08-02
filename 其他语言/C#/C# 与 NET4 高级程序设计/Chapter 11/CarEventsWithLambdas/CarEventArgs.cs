using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CarEvents
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
