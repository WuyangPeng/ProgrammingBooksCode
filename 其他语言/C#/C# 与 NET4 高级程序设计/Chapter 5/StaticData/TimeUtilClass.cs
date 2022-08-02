using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StaticData
{
    // Static classes can only
    // contain static members!
    static class TimeUtilClass
    {
        public static void PrintTime()
        { Console.WriteLine(DateTime.Now.ToShortTimeString()); }
        public static void PrintDate()
        { Console.WriteLine(DateTime.Today.ToShortDateString()); }
    }
    class TimeUtilClass2
    {
        // Redefine the default ctor as private
        // to prevent creation.
        private TimeUtilClass2() { }

        public static void PrintTime()
        { Console.WriteLine(DateTime.Now.ToShortTimeString()); }
        public static void PrintDate()
        { Console.WriteLine(DateTime.Today.ToShortDateString()); }
    }

    // Define type as abstract to prevent
    // creation
    abstract class TimeUtilClass3
    {
        public static void PrintTime()
        { Console.WriteLine(DateTime.Now.ToShortTimeString()); }
        public static void PrintDate()
        { Console.WriteLine(DateTime.Today.ToShortDateString()); }
    }


}
