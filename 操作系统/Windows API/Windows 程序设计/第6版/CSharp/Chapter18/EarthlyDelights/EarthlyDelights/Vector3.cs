using System;
using Windows.Foundation;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Media3D;

namespace Petzold.Windows8.VectorDrawing
{
    public struct Vector3
    {
        // Constructors
        public Vector3(double x, double y, double z)
            : this()
        {
            X = x;
            Y = y;
            Z = z;
        }

        // Properties
        public double X { private set; get; }
        public double Y { private set; get; }
        public double Z { private set; get; }

        public double LengthSquared
        {
            get { return X * X + Y * Y + Z * Z; }
        }

        public double Length
        {
            get { return Math.Sqrt(LengthSquared); }
        }

        public Vector3 Normalized
        {
            get
            {
                double length = this.Length;

                if (length != 0)
                {
                    return new Vector3(this.X / length,
                                       this.Y / length,
                                       this.Z / length);
                }
                return new Vector3();
            }
        }

        // Static properties
        public static Vector3 UnitX
        {
            get { return new Vector3(1, 0, 0); }
        }

        public static Vector3 UnitY
        {
            get { return new Vector3(0, 1, 0); }
        }

        public static Vector3 UnitZ
        {
            get { return new Vector3(0, 0, 1); }
        }

        // Static methods
        public static Vector3 Cross(Vector3 v1, Vector3 v2)
        {
            return new Vector3(v1.Y * v2.Z - v1.Z * v2.Y,
                               v1.Z * v2.X - v1.X * v2.Z,
                               v1.X * v2.Y - v1.Y * v2.X);
        }

        public static double Dot(Vector3 v1, Vector3 v2)
        {
            return v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z;
        }

        public static double AngleBetween(Vector3 v1, Vector3 v2)
        {
            return 180 / Math.PI * Math.Acos(Vector3.Dot(v1, v2) /
                                                v1.Length * v2.Length);
        }

        public static Vector3 Transform(Vector3 v, Matrix3D m)
        {
            double x = m.M11 * v.X + m.M21 * v.Y + m.M31 * v.Z + m.OffsetX;
            double y = m.M12 * v.X + m.M22 * v.Y + m.M32 * v.Z + m.OffsetY;
            double z = m.M13 * v.X + m.M23 * v.Y + m.M33 * v.Z + m.OffsetZ;
            double w = m.M14 * v.X + m.M24 * v.Y + m.M34 * v.Z + m.M44;
            return new Vector3(x / w, y / w, z / w);
        }

        // Operators
        public static Vector3 operator +(Vector3 v1, Vector3 v2)
        {
            return new Vector3(v1.X + v2.X, v1.Y + v2.Y, v1.Z + v2.Z);
        }

        public static Vector3 operator -(Vector3 v1, Vector3 v2)
        {
            return new Vector3(v1.X - v2.X, v1.Y - v2.Y, v1.Z - v2.Z);
        }

        public static Vector3 operator *(Vector3 v, double d)
        {
            return new Vector3(d * v.X, d * v.Y, d * v.Z);
        }

        public static Vector3 operator *(double d, Vector3 v)
        {
            return new Vector3(d * v.X, d * v.Y, d * v.Z);
        }

        public static Vector3 operator /(Vector3 v, double d)
        {
            return new Vector3(v.X / d, v.Y / d, v.Z / d);
        }

        public static Vector3 operator -(Vector3 v)
        {
            return new Vector3(-v.X, -v.Y, -v.Z);
        }

        // Overrides
        public override string ToString()
        {
            return String.Format("({0} {1} {2})", X, Y, Z);
        }
    }
}
