using System.Collections.Generic;

namespace Petzold.Windows8.VectorDrawing
{
    public interface IGeometrySegment
    {
        void GetAllX(double y, IList<double> xCollection);
    }
}
