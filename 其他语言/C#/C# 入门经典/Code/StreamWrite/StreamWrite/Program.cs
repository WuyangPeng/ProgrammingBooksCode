using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace StreamWrite
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                FileStream aFile = new FileStream("Log.txt", FileMode.OpenOrCreate);
                StreamWriter sw = new StreamWriter(aFile);

                bool truth = true;
                // Write data to file.
                sw.WriteLine("Hello to you.");
                sw.WriteLine("It is now {0} and things are looking good.",
                             DateTime.Now.ToLongDateString());
                sw.Write("More than that,");
                sw.Write(" it's {0} that C# is fun.", truth);
                sw.Close();
            }
            catch (IOException e)
            {
                Console.WriteLine("An IO exception has been thrown!");
                Console.WriteLine(e.ToString());
                Console.ReadLine();
                return;
            }
        }
    }
}
