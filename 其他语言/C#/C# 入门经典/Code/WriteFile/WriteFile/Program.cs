using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace WriteFile
{
    class Program
    {
        static void Main(string[] args)
        {
            byte[] byData;
            char[] charData;

            try
            {
                FileStream aFile = new FileStream("Temp.txt", FileMode.Create);
                charData = "My pink half of the drainpipe.".ToCharArray();
                byData = new byte[charData.Length];
                Encoder e = Encoding.UTF8.GetEncoder();
                e.GetBytes(charData, 0, charData.Length, byData, 0, true);

                // Move file pointer to beginning of file.
                aFile.Seek(0, SeekOrigin.Begin);
                aFile.Write(byData, 0, byData.Length);
            }
            catch (IOException ex)
            {
                Console.WriteLine("An IO exception has been thrown!");
                Console.WriteLine(ex.ToString());
                Console.ReadKey();
                return;
            }
        }
    }
}
