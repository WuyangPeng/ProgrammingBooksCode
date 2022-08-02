using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace InterfaceHierarchy
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Simple Interface Hierarchy *****");
            // Call from object level.
            BitmapImage myBitmap = new BitmapImage();
            myBitmap.Draw();
            myBitmap.DrawInBoundingBox(10, 10, 100, 150);
            myBitmap.DrawUpsideDown();

            // Get IAdvancedDraw explicitly.
            IAdvancedDraw iAdvDraw;
            iAdvDraw = (IAdvancedDraw)myBitmap;
            iAdvDraw.DrawUpsideDown();

            Console.ReadLine();
        }
    }
}
