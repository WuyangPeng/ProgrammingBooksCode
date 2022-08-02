using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch13Ex03
{
    public class Display
    {
        public void DisplayMessage(Connection source, MessageArrivedEventArgs e)
        {
            Console.WriteLine("Message arrived from: {0}", source.Name);
            Console.WriteLine("Message Text: {0}", e.Message);
        }
    }
}
