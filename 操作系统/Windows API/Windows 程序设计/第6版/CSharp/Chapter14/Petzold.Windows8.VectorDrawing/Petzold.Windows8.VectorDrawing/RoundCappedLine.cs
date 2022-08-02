using System.Collections.Generic;
using Windows.Foundation;

namespace Petzold.Windows8.VectorDrawing
{
    public struct RoundCappedLine : IGeometrySegment
    {
        LineSegment lineSegment1;
        ArcSegment arcSegment1;
        LineSegment lineSegment2;
        ArcSegment arcSegment2;

        public RoundCappedLine(Point point1, Point point2, double radius) : this()
        {
            Vector2 vector = new Vector2(point2 - new Vector2(point1));
            Vector2 normVect = vector;
            normVect = normVect.Normalized;

            Point pt1a = point1 + radius * new Vector2(normVect.Y, -normVect.X);
            Point pt2a = pt1a + vector;
            Point pt1b = point1 + radius * new Vector2(-normVect.Y, normVect.X);
            Point pt2b = pt1b + vector;

            lineSegment1 = new LineSegment(pt1a, pt2a);
            arcSegment1 = new ArcSegment(point2, radius, pt2a, pt2b);
            lineSegment2 = new LineSegment(pt2b, pt1b);
            arcSegment2 = new ArcSegment(point1, radius, pt1b, pt1a);
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
