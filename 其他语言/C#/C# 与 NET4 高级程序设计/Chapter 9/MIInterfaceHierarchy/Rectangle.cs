using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MIInterfaceHierarchy
{
    class Rectangle : IShape
    {
        public int GetNumberOfSides()
        { return 4; }

        public void Draw()
        { Console.WriteLine("Drawing..."); }

        public void Print()
        { Console.WriteLine("Prining..."); }
    }
}
