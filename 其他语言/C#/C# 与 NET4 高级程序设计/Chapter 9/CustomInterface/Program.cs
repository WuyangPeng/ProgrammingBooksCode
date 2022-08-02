using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CustomInterface
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Fun with Interfaces *****\n");

            // Make an array of Shapes.
            Shape[] myShapes = { new Hexagon(), new Circle(), new Triangle("Joe"),
                          new Circle("JoJo")};
            // Get first pointy item.
            IPointy firstPointyItem = FindFirstPointyShape(myShapes);
            Console.WriteLine("The item has {0} points", firstPointyItem.Points);

            for (int i = 0; i < myShapes.Length; i++)
            {
                // Recall the Shape base class defines an abstract Draw()
                // member, so all shapes know how to draw themselves.
                myShapes[i].Draw();

                // Who's pointy?
                if (myShapes[i] is IPointy)
                    Console.WriteLine("-> Points: {0}", ((IPointy)myShapes[i]).Points);
                else
                    Console.WriteLine("-> {0}\'s not pointy!", myShapes[i].PetName);

                // Can I draw you in 3D?
                if (myShapes[i] is IDraw3D)
                    DrawIn3D((IDraw3D)myShapes[i]);

                Console.WriteLine();
            }

            // This array can only contain types that
            // implement the IPointy interface.
            IPointy[] myPointyObjects = {new Hexagon(), new Knife(),
                    new Triangle(), new Fork(), new PitchFork()};

            foreach (IPointy i in myPointyObjects)
                Console.WriteLine("Object has {0} points.", i.Points);

            Console.ReadLine();
        }

        // I'll draw anyone supporting IDraw3D.
        static void DrawIn3D(IDraw3D itf3d)
        {
            Console.WriteLine("-> Drawing IDraw3D compatible type");
            itf3d.Draw3D();
        }

        static IPointy FindFirstPointyShape(Shape[] shapes)
        {
            foreach (Shape s in shapes)
            {
                if (s is IPointy)
                    return s as IPointy;
            }
            return null;
        }



    }
}
