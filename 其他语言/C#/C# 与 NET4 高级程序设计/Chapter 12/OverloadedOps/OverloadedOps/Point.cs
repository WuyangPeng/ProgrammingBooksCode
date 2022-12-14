using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace OverloadedOps
{
    public class Point : IComparable
    {
        public int X { get; set; }
        public int Y { get; set; }

        public Point(int xPos, int yPos)
        {
            X = xPos;
            Y = yPos;
        }

        public override string ToString()
        {
            return string.Format("[{0}, {1}]", this.X, this.Y);
        }

        #region Binary ops
        // overloaded operator +
        public static Point operator +(Point p1, Point p2)
        { return new Point(p1.X + p2.X, p1.Y + p2.Y); }

        // overloaded operator -
        public static Point operator -(Point p1, Point p2)
        { return new Point(p1.X - p2.X, p1.Y - p2.Y); }

        public static Point operator +(Point p1, int change)
        {
            return new Point(p1.X + change, p1.Y + change);
        }

        public static Point operator +(int change, Point p1)
        {
            return new Point(p1.X + change, p1.Y + change);
        }
        #endregion

        #region Unary ops
        // Add 1 to the X/Y values incoming Point.
        public static Point operator ++(Point p1)
        { return new Point(p1.X + 1, p1.Y + 1); }

        // Subtract 1 from the X/Y values incoming Point.
        public static Point operator --(Point p1)
        { return new Point(p1.X - 1, p1.Y - 1); }
        #endregion

        #region Equality logic
        public override bool Equals(object o)
        {
            return o.ToString() == this.ToString();
        }

        public override int GetHashCode()
        { return this.ToString().GetHashCode(); }

        // Now let's overload the == and != operators.
        public static bool operator ==(Point p1, Point p2)
        { return p1.Equals(p2); }

        public static bool operator !=(Point p1, Point p2)
        { return !p1.Equals(p2); }
        #endregion

        #region Compare ops
        public int CompareTo(object obj)
        {
            if (obj is Point)
            {
                Point p = (Point)obj;
                if (this.X > p.X && this.Y > p.Y)
                    return 1;
                if (this.X < p.X && this.Y < p.Y)
                    return -1;
                else
                    return 0;
            }
            else
                throw new ArgumentException();
        }

        public static bool operator <(Point p1, Point p2)
        { return (p1.CompareTo(p2) < 0); }

        public static bool operator >(Point p1, Point p2)
        { return (p1.CompareTo(p2) > 0); }

        public static bool operator <=(Point p1, Point p2)
        { return (p1.CompareTo(p2) <= 0); }

        public static bool operator >=(Point p1, Point p2)
        { return (p1.CompareTo(p2) >= 0); }

        #endregion
    }
}
