using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch13Ex02
{
    class Program
    {
        static void Main(string[] args)
        {
            Connection myConnection = new Connection();
            Display myDisplay = new Display();
            myConnection.MessageArrived +=
                    new MessageHandler(myDisplay.DisplayMessage);
            myConnection.Connect();
            Console.ReadKey();
        }
    }
}
