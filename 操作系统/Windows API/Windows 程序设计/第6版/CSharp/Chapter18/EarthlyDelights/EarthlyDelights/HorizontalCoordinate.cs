using System;
using Windows.UI.Xaml.Media.Media3D;

namespace Petzold.Windows8.VectorDrawing
{
    public struct HorizontalCoordinate
    {
        public HorizontalCoordinate(double azimuth, double altitude, double tilt)
            : this()
        {
            this.Azimuth = azimuth;
            this.Altitude = altitude;
            this.Tilt = tilt;
        }

        public HorizontalCoordinate(double azimuth, double altitude)
            : this(azimuth, altitude, 0)
        {
        }

        // Eastward from north
        public double Azimuth { private set; get; }

        public double Altitude { private set; get; }

        public double Tilt { private set; get; }

        public static HorizontalCoordinate FromVector(Vector3 vector)
        {
            double altitude = 180 * Math.Asin(vector.Z) / Math.PI;
            double azimuth = 180 * Math.Atan2(vector.X, vector.Y) / Math.PI;

            return new HorizontalCoordinate(azimuth, altitude);
        }

        public static HorizontalCoordinate FromMotionMatrix(Matrix3D matrix)
        {
            // Invert the matrix 
            matrix.Invert();

            // Transform (0, 0, -1) -- the vector extending from the lens
            Vector3 zAxisTransformed = Vector3.Transform(-Vector3.UnitZ, matrix);

            // Get the horizontal coordinates
            HorizontalCoordinate horzCoord = FromVector(zAxisTransformed);

            // Find the theoretical HorizontalCoordinate for the transformed +Y vector 
            //     if the device is upright
            double yUprightAltitude = 0;
            double yUprightAzimuth = 0;

            if (horzCoord.Altitude > 0)
            {
                yUprightAltitude = 90 - horzCoord.Altitude;
                yUprightAzimuth = 180 + horzCoord.Azimuth;
            }
            else
            {
                yUprightAltitude = 90 + horzCoord.Altitude;
                yUprightAzimuth = horzCoord.Azimuth;
            }
            Vector3 yUprightVector = 
                new HorizontalCoordinate(yUprightAzimuth, yUprightAltitude).ToVector();

            // Find the real transformed +Y vector
            Vector3 yAxisTransformed = Vector3.Transform(Vector3.UnitY, matrix);

            // Get the angle between the upright +Y vector and the real transformed +Y vector
            double dotProduct = Vector3.Dot(yUprightVector, yAxisTransformed);
            Vector3 crossProduct = Vector3.Cross(yUprightVector, yAxisTransformed);
            crossProduct = crossProduct.Normalized;

            // Sometimes dotProduct is slightly greater than 1, which 
            // raises an exception in the angleBetween calculation, so....
            dotProduct = Math.Min(dotProduct, 1);
            double angleBetween = 180 * Vector3.Dot(zAxisTransformed, crossProduct) 
                                      * Math.Acos(dotProduct) / Math.PI;
            horzCoord.Tilt = angleBetween;

            return horzCoord;
        }

        public Vector3 ToVector()
        {
            double x = Math.Cos(Math.PI * this.Altitude / 180) * 
                       Math.Sin(Math.PI * this.Azimuth / 180);
            double y = Math.Cos(Math.PI * this.Altitude / 180) * 
                       Math.Cos(Math.PI * this.Azimuth / 180);
            double z = Math.Sin(Math.PI * this.Altitude / 180);

            return new Vector3((float)x, (float)y, (float)z);
        }

        public override string ToString()
        {
            return String.Format("Azi: {0} Alt: {1} Tilt: {2}", 
                                 this.Azimuth, this.Altitude, this.Tilt);
        }
    }
}