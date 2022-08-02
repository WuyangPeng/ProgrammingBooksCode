using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.IO.Compression;

namespace Compressor
{
    class Program
    {
        static void SaveCompressedFile(string filename, string data)
        {
            FileStream fileStream =
               new FileStream(filename, FileMode.Create, FileAccess.Write);
            GZipStream compressionStream =
               new GZipStream(fileStream, CompressionMode.Compress);
            StreamWriter writer = new StreamWriter(compressionStream);
            writer.Write(data);
            writer.Close();
        }

        static string LoadCompressedFile(string filename)
        {
            FileStream fileStream =
               new FileStream(filename, FileMode.Open, FileAccess.Read);
            GZipStream compressionStream =
               new GZipStream(fileStream, CompressionMode.Decompress);
            StreamReader reader = new StreamReader(compressionStream);
            string data = reader.ReadToEnd();
            reader.Close();
            return data;
        }

        static void Main(string[] args)
        {
            try
            {
                string filename = "compressedFile.txt";

                Console.WriteLine(
                   "Enter a string to compress (will be repeated 100 times):");
                string sourceString = Console.ReadLine();
                StringBuilder sourceStringMultiplier =
                   new StringBuilder(sourceString.Length * 100);
                for (int i = 0; i < 100; i++)
                {
                    sourceStringMultiplier.Append(sourceString);
                }
                sourceString = sourceStringMultiplier.ToString();
                Console.WriteLine("Source data is {0} bytes long.", sourceString.Length);

                SaveCompressedFile(filename, sourceString);
                Console.WriteLine("\nData saved to {0}.", filename);

                FileInfo compressedFileData = new FileInfo(filename);
                Console.WriteLine("Compressed file is {0} bytes long.",
                                  compressedFileData.Length);

                string recoveredString = LoadCompressedFile(filename);
                recoveredString = recoveredString.Substring(
                   0, recoveredString.Length / 100);
                Console.WriteLine("\nRecovered data: {0}", recoveredString);

                Console.ReadKey();
            }
            catch (IOException ex)
            {
                Console.WriteLine("An IO exception has been thrown!");
                Console.WriteLine(ex.ToString());
                Console.ReadKey();
            }
        }
    }
}
