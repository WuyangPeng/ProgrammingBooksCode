using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization.Formatters.Soap;
using System.Xml.Serialization;
using System.IO;

namespace SimpleSerialize
{
    #region Serializable data
    [Serializable]
    public class Radio
    {
        public bool hasTweeters;
        public bool hasSubWoofers;
        public double[] stationPresets;

        [NonSerialized]
        public string radioID = "XF-552RR6";
    }

    [Serializable]
    public class Car
    {
        public Radio theRadio = new Radio();
        public bool isHatchBack;
    }

    [Serializable,
     XmlRoot(Namespace = "http://www.MyCompany.com")]
    public class JamesBondCar : Car
    {
        public bool canFly;
        public bool canSubmerge;

        public JamesBondCar(bool skyWorthy, bool seaWorthy)
        {
            canFly = skyWorthy;
            canSubmerge = seaWorthy;
        }
        // The XmlSerializer demands a default constructor!
        public JamesBondCar() { }

    }
    #endregion

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("***** Fun with Object Serialization *****\n");

            // Make a JamesBondCar and set state.
            JamesBondCar jbc = new JamesBondCar();
            jbc.canFly = true;
            jbc.canSubmerge = false;
            jbc.theRadio.stationPresets = new double[] { 89.3, 105.1, 97.1 };
            jbc.theRadio.hasTweeters = true;

            // Now save the car to a specific file in a binary format.
            SaveAsBinaryFormat(jbc, "CarData.dat");
            LoadFromBinaryFile("CarData.dat");
            SaveAsSoapFormat(jbc, "CarData.soap");
            SaveAsXmlFormat(jbc, "CarData.xml");
            SaveListOfCars();
            SaveListOfCarsAsBinary();
            Console.WriteLine("All done!");

            Console.ReadLine();
        }

        #region Save as binary
        static void SaveAsBinaryFormat(object objGraph, string fileName)
        {
            // Save object to a file named CarData.dat in binary.
            BinaryFormatter binFormat = new BinaryFormatter();
            
            using (Stream fStream = new FileStream(fileName,
                  FileMode.Create, FileAccess.Write, FileShare.None))
            {
                binFormat.Serialize(fStream, objGraph);
            }
            Console.WriteLine("=> Saved car in binary format!");
        }
        #endregion

        #region Load from binary
        static void LoadFromBinaryFile(string fileName)
        {
            BinaryFormatter binFormat = new BinaryFormatter();

            // Read the JamesBondCar from the binary file.
            using (Stream fStream = File.OpenRead(fileName))
            {
                JamesBondCar carFromDisk =
                  (JamesBondCar)binFormat.Deserialize(fStream);
                Console.WriteLine("Can this car fly? : {0}", carFromDisk.canFly);
            }
        }
        #endregion

        #region Save as SOAP
        static void SaveAsSoapFormat(object objGraph, string fileName)
        {
            // Save object to a file named CarData.soap in SOAP format.
            SoapFormatter soapFormat = new SoapFormatter();

            using (Stream fStream = new FileStream(fileName,
              FileMode.Create, FileAccess.Write, FileShare.None))
            {
                soapFormat.Serialize(fStream, objGraph);
            }
            Console.WriteLine("=> Saved car in SOAP format!");
        }
        #endregion

        #region Save as XML
        static void SaveAsXmlFormat(object objGraph, string fileName)
        {
            // Save object to a file named CarData.xml in XML format.
            XmlSerializer xmlFormat = new XmlSerializer(typeof(JamesBondCar)
              );

            using (Stream fStream = new FileStream(fileName,
              FileMode.Create, FileAccess.Write, FileShare.None))
            {
                xmlFormat.Serialize(fStream, objGraph);
            }
            Console.WriteLine("=> Saved car in XML format!");
        }
        #endregion

        #region Save list of objects as XML
        static void SaveListOfCars()
        {
            // Now persist a List<T> of JamesBondCars.
            List<JamesBondCar> myCars = new List<JamesBondCar>();
            myCars.Add(new JamesBondCar(true, true));
            myCars.Add(new JamesBondCar(true, false));
            myCars.Add(new JamesBondCar(false, true));
            myCars.Add(new JamesBondCar(false, false));

            using (Stream fStream = new FileStream("CarCollection.xml",
              FileMode.Create, FileAccess.Write, FileShare.None))
            {
                XmlSerializer xmlFormat = new XmlSerializer(typeof(List<JamesBondCar>),
                  new Type[] { typeof(JamesBondCar), typeof(Car), typeof(Radio) });
                xmlFormat.Serialize(fStream, myCars);
            }
            Console.WriteLine("=> Saved list of cars!");
        }
        #endregion

        #region Save list of objects in binary
        static void SaveListOfCarsAsBinary()
        {
            // Save ArrayList object (myCars) as binary.
            List<JamesBondCar> myCars = new List<JamesBondCar>();

            BinaryFormatter binFormat = new BinaryFormatter();
            using (Stream fStream = new FileStream("AllMyCars.dat",
              FileMode.Create, FileAccess.Write, FileShare.None))
            {
                binFormat.Serialize(fStream, myCars);
            }
            Console.WriteLine("=> Saved list of cars in binary!");
        }
        #endregion
    }
}
