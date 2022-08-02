using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace SimpleFileIO
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Simple IO with the File Type *****\n");
            string[] myTasks = {
                  "Fix bathroom sink", "Call Dave",
                  "Call Mom and Dad", "Play Xbox 360"};

            // Write out all data to file on C drive.
            File.WriteAllLines(@"C:\tasks.txt", myTasks);

            // Read it all back and print out.
            foreach (string task in File.ReadAllLines(@"C:\tasks.txt"))
            {
                Console.WriteLine("TODO: {0}", task);
            }
            Console.ReadLine();
        }
    }

}
