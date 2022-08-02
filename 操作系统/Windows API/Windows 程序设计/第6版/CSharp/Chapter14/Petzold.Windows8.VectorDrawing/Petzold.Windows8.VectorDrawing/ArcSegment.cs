using System;
using System.Collections.Generic;
using Windows.Foundation;

namespace Petzold.Windows8.VectorDrawing
{
    public struct ArcSegment : IGeometrySegment
    {
        readonly Point center, point1, point2;
        readonly double radius;
        readonly double angle1, angle2;

        public ArcSegment(Point center, double radius, 
                          Point point1, Point point2) : 
            this()
        {
            this.center = center;
            this.radius = radius;
            this.point1 = point1;
            this.point2 = point2;
            this.angle1 = Math.Atan2(point1.Y - center.Y, point1.X - center.X);
            this.angle2 = Math.Atan2(point2.Y - center.Y, point2.X - center.X);
        }

        public void GetAllX(double y, IList<double> xCollection)
        {
            double sqrtArg = radius * radius - Math.Pow(y - center.Y, 2);

            if (sqrtArg >= 0)
            {
                double sqrt = Math.Sqrt(sqrtArg);
                TryY(y, center.X + sqrt, xCollection);
                TryY(y, center.X - sqrt, xCollection);
            }
        }

        void TryY(double y, double x, IList<double> xCollection)
        {
            double angle = Math.Atan2(y - center.Y, x - center.X);

            if ((angle1 < angle2 && (angle1 <= angle && angle < angle2)) ||
                (angle1 > angle2 && (angle1 <= angle || angle < angle2)))
            {
                xCollection.Add((float)x);
            }
        }
    }
}
