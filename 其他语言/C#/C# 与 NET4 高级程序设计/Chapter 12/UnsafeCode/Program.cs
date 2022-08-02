using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace UnsafeCode
{
    #region Unsafe types and members (just for testing purposes)
    // This entire structure is 'unsafe' and can
    // be used only in an unsafe context.
    public unsafe struct Node
    {
        public int Value;
        public Node* Left;
        public Node* Right;
    }

    // This struct is safe, but the Node* members
    // are not. Technically, you may access 'Value' from
    // outside an unsafe context, but not 'Left' and 'Right'.
    public struct Node2
    {
        public int Value;

        // These can be accessed only in an unsafe context!
        public unsafe Node2* Left;
        public unsafe Node2* Right;
    }
    #endregion

    #region Simple Point / PointRef
    struct Point
    {
        public int x;
        public int y;
        public override string ToString()
        { return string.Format("({0}, {1})", x, y); }
    }

    class PointRef
    {
        public int x;
        public int y;
        public override string ToString()
        { return string.Format("({0}, {1})", x, y); }
    }
    #endregion

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Fun with Pointers *****");

            #region Swap 2 ints safely and unsafely
            // Values for swap.
            int i = 10, j = 20;

            // Swap values 'safely'.
            Console.WriteLine("\n***** Safe swap *****");
            Console.WriteLine("Values before safe swap: i = {0}, j = {1}", i, j);
            SafeSwap(ref i, ref j);
            Console.WriteLine("Values after safe swap: i = {0}, j = {1}", i, j);

            // Swap values 'unsafely'.
            Console.WriteLine("\n***** Unsafe swap *****");
            Console.WriteLine("Values before unsafe swap: i = {0}, j = {1}", i, j);
            unsafe { UnsafeSwap(&i, &j); }
            Console.WriteLine("Values after unsafe swap: i = {0}, j = {1}", i, j);
            Console.WriteLine();
            #endregion

            UsePointerToPoint();
            Console.WriteLine();
            UseSizeOfOperator();
            Console.ReadLine();
        }

        public static void SafeSwap(ref int i, ref int j)
        {
            int temp = i;
            i = j;
            j = temp;
        }

        #region Various unsafe methods
        unsafe static void PrintValueAndAddress()
        {
            int myInt;

            // Define an int pointer, and
            // assign it the address of myInt.
            int* ptrToMyInt = &myInt;

            // Assign value of myInt using pointer indirection.
            *ptrToMyInt = 123;

            // Print some stats.
            Console.WriteLine("Value of myInt {0}", myInt);
            Console.WriteLine("Address of myInt {0:X}", (int)&ptrToMyInt);
        }

        unsafe static void SquareIntPointer(int* myIntPointer)
        {
            // Work with pointer types here!
            // Square the value just for a test.
            *myIntPointer *= *myIntPointer;
        }

        unsafe public static void UnsafeSwap(int* i, int* j)
        {
            int temp = *i;
            *i = *j;
            *j = temp;
        }

        unsafe static void UsePointerToPoint()
        {
            // Access members via pointer.
            Point point;
            Point* p = &point;
            p->x = 100;
            p->y = 200;
            Console.WriteLine(p->ToString());

            // Access members via pointer indirection.
            Point point2;
            Point* p2 = &point2;
            (*p2).x = 100;
            (*p2).y = 200;
            Console.WriteLine((*p2).ToString());
        }

        unsafe static void UnsafeStackAlloc()
        {
            char* p = stackalloc char[256];
            for (int k = 0; k < 256; k++)
                p[k] = (char)k;
        }

        unsafe public static void UseAndPinPoint()
        {
            PointRef pt = new PointRef();
            pt.x = 5;
            pt.y = 6;

            // pin pt in place so it will not
            // be moved or GC-ed.
            fixed (int* p = &pt.x)
            {
                // Use int* variable here!
            }

            // pt is now unpinned, and ready to be GC-ed.
            Console.WriteLine("Point is: {0}", pt);
        }
        unsafe static void UseSizeOfOperator()
        {
            Console.WriteLine("The size of short is {0}.", sizeof(short));
            Console.WriteLine("The size of int is {0}.", sizeof(int));
            Console.WriteLine("The size of long is {0}.", sizeof(long));
            Console.WriteLine("The size of Point is {0}.", sizeof(Point));
        }
        #endregion
    }
}
