using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace CommaValues
{
    class Program
    {
        private static List<Dictionary<string, string>> GetData(
   out List<string> columns)
        {
            string line;
            string[] stringArray;
            char[] charArray = new char[] { ',' };
            List<Dictionary<string, string>> data =
               new List<Dictionary<string, string>>();
            columns = new List<string>();

            try
            {
                FileStream aFile = new FileStream(@"..\..\SomeData.txt", FileMode.Open);
                StreamReader sr = new StreamReader(aFile);

                // Obtain the columns from the first line.
                // Split row of data into string array
                line = sr.ReadLine();
                stringArray = line.Split(charArray);

                for (int x = 0; x <= stringArray.GetUpperBound(0); x++)
                {
                    columns.Add(stringArray[x]);
                }

                line = sr.ReadLine();
                while (line != null)
                {
                    // Split row of data into string array
                    stringArray = line.Split(charArray);
                    Dictionary<string, string> dataRow = new Dictionary<string, string>();

                    for (int x = 0; x <= stringArray.GetUpperBound(0); x++)
                    {
                        dataRow.Add(columns[x], stringArray[x]);
                    }

                    data.Add(dataRow);

                    line = sr.ReadLine();
                }

                sr.Close();
                return data;
            }
            catch (IOException ex)
            {
                Console.WriteLine("An IO exception has been thrown!");
                Console.WriteLine(ex.ToString());
                Console.ReadLine();
                return data;
            }
        }

        static void Main(string[] args)
        {
            List<string> columns;
            List<Dictionary<string, string>> myData = GetData(out columns);

            foreach (string column in columns)
            {
                Console.Write("{0,-20}", column);
            }
            Console.WriteLine();

            foreach (Dictionary<string, string> row in myData)
            {
                foreach (string column in columns)
                {
                    Console.Write("{0,-20}", row[column]);
                }
                Console.WriteLine();
            }
            Console.ReadKey();
        }
    }
}
