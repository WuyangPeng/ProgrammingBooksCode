using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace StringReaderWriterApp
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Fun with StringWriter / StringReader *****\n");

            // Create a StringWriter and emit character data to memory.
            using (StringWriter strWriter = new StringWriter())
            {
                strWriter.WriteLine("Don't forget Mother's Day this year...");
                Console.WriteLine("Contents of StringWriter:\n{0}", strWriter);

                // Read data from the StringWriter.
                using (StringReader strReader = new StringReader(strWriter.ToString()))
                {
                    string input = null;
                    while ((input = strReader.ReadLine()) != null)
                    {
                        Console.WriteLine(input);
                    }
                }
            }
            Console.ReadLine();
        }
    }
}
