using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CustomEnumerator
{
    class Radio
    {
        public void TurnOn(bool turnRadioOn)
        {
            if (turnRadioOn)
                Console.WriteLine("Jamming...");
            else
                Console.WriteLine("Quiet time...");
        }
    }
}
