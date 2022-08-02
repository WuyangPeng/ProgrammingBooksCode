using System;
using MyShapes;
using My3DShapes;

// Resolve the ambiguity using a custom alias.
using The3DHexagon = My3DShapes.Hexagon;

using bfHome = System.Runtime.Serialization.Formatters.Binary;

namespace CustomNamespaces
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Custom Namespaces *****");
            Console.WriteLine("This program has no real output,");
            Console.WriteLine("but the code files illustrate how");
            Console.WriteLine("to work with custom namespaces.");

            // This is really creating a My3DShapes.Hexagon type.
            The3DHexagon h2 = new The3DHexagon();

            bfHome.BinaryFormatter b = new bfHome.BinaryFormatter();

            Console.ReadLine();
        }
    }
}
