﻿using System;
using Windows.Foundation;
using Windows.UI.Xaml.Media;

namespace Petzold.Windows8.VectorDrawing
{
    public struct Vector2
    {
        // Constructors
        public Vector2(double x, double y)
            : this()
        {
            X = x;
            Y = y;
        }

        public Vector2(Point p)
            : this()
        {
            X = p.X;
            Y = p.Y;
        }

        public Vector2(double angle)
            : this()
        {
            X = Math.Cos(Math.PI * angle / 180);
            Y = Math.Sin(Math.PI * angle / 180);
        }

        // Properties
        public double X { private set; get; }
        public double Y { private set; get; }

        public double LengthSquared
        {
            get { return X * X + Y * Y; }
        }

        public double Length
        {
            get { return Math.Sqrt(LengthSquared); }
        }

        public Vector2 Normalized
        {
            get
            {
                double length = this.Length;

                if (length != 0)
                {
                    return new Vector2(this.X / length,
                                       this.Y / length);
                }
                return new Vector2();
            }
        }

        // Methods
        public Vector2 Rotate(double angle)
        {
            RotateTransform xform = new RotateTransform { Angle = angle };
            Point pt = xform.TransformPoint(new Point(X, Y));
            return new Vector2(pt.X, pt.Y);
        }

        // Static methods
        public static double AngleBetween(Vector2 v1, Vector2 v2)
        {
            return 180 * (Math.Atan2(v2.Y, v2.X) - Math.Atan2(v1.Y, v1.X)) / Math.PI;
        }

        // Operators
        public static Vector2 operator +(Vector2 v1, Vector2 v2)
        {
            return new Vector2(v1.X + v2.X, v1.Y + v2.Y);
        }

        public static Point operator +(Vector2 v, Point p)
        {
            return new Point(v.X + p.X, v.Y + p.Y);
        }

        public static Point operator +(Point p, Vector2 v)
        {
            return new Point(v.X + p.X, v.Y + p.Y);
        }

        public static Vector2 operator -(Vector2 v1, Vector2 v2)
        {
            return new Vector2(v1.X - v2.X, v1.Y - v2.Y);
        }

        public static Point operator -(Point p, Vector2 v)
        {
            return new Point(p.X - v.X, p.Y - v.Y);
        }

        public static Vector2 operator *(Vector2 v, double d)
        {
            return new Vector2(d * v.X, d * v.Y);
        }

        public static Vector2 operator *(double d, Vector2 v)
        {
            return new Vector2(d * v.X, d * v.Y);
        }

        public static Vector2 operator /(Vector2 v, double d)
        {
            return new Vector2(v.X / d, v.Y / d);
        }

        public static Vector2 operator -(Vector2 v)
        {
            return new Vector2(-v.X, -v.Y);
        }

        public static explicit operator Point(Vector2 v)
        {
            return new Point(v.X, v.Y);
        }

        // Overrides
        public override string ToString()
        {
            return String.Format("({0} {1})", X, Y);
        }
    }
}
