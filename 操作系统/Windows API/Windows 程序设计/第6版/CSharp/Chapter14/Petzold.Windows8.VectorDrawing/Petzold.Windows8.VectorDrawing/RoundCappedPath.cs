using System;
using System.Collections.Generic;
using Windows.Foundation;

namespace Petzold.Windows8.VectorDrawing
{
    public struct RoundCappedPath : IGeometrySegment
    {
        LineSegment lineSegment1;
        ArcSegment arcSegment1;
        LineSegment lineSegment2;
        ArcSegment arcSegment2;

        public RoundCappedPath(Point point1, Point point2, double radius1, double radius2)
            : this()
        {
            Point c0 = point1;
            Point c1 = point2;
            double r0 = radius1;
            double r1 = radius2;

            // Get vector from c1 to c0
            Vector2 vCenters = new Vector2(c0) - new Vector2(c1);

            // Get length and normalized version
            double d = vCenters.Length;
            vCenters = vCenters.Normalized;

            // Create focal point F extending from c0
            double e = d * r0 / (r1 - r0);
            Point F = c0 + e * vCenters;

            // Find angle and length of right-triangle legs
            double alpha = 180 * Math.Asin(r0 / e) / Math.PI;
            double leg0 = Math.Sqrt(e * e - r0 * r0);
            double leg1 = Math.Sqrt((e + d) * (e + d) - r1 * r1);

            // Vectors of tangent lines
            Vector2 vRight = -vCenters.Rotate(alpha);
            Vector2 vLeft = -vCenters.Rotate(-alpha);

            // Find tangent points
            Point t0R = F + leg0 * vRight;
            Point t0L = F + leg0 * vLeft;
            Point t1R = F + leg1 * vRight;
            Point t1L = F + leg1 * vLeft;

            lineSegment1 = new LineSegment(t1R, t0R);
            arcSegment1 = new ArcSegment(c0, r0, t0R, t0L);
            lineSegment2 = new LineSegment(t0L, t1L);
            arcSegment2 = new ArcSegment(c1, r1, t1L, t1R);
        }

        public void GetAllX(double y, IList<double> xCollection)
        {
            arcSegment1.GetAllX(y, xCollection);
            lineSegment1.GetAllX(y, xCollection);
            arcSegment2.GetAllX(y, xCollection);
            lineSegment2.GetAllX(y, xCollection);
        }
    }
}
