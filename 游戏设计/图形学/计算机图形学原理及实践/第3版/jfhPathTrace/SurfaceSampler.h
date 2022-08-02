/**
 @file   SurfaceSampler.h
 @author John Hughes
 @date   2011-04-07
 @edited 2011-04-07

 Description of a surface for use in a sample-based renderer.

  Encodes a BSDF, bump map, and emission function AND a way to find the area and to pick a random point on the surface. 

*/
#ifndef SurfaceSampler_h
#define SurfaceSampler_h

#include <G3D/G3DAll.h>

class SurfaceSampler : public ReferenceCountedObject {
protected:
    double              m_area; 
    Array<float>        m_triangleSummedAreaTable;

    CPUVertexArray      m_vertexArray;
    Array<Tri>          m_triArray;

    GMutex              m_mutex;

    shared_ptr<Surface> m_base;

    void areaPrecompute();
    SurfaceSampler(const shared_ptr<Surface>& base);

public:

    static shared_ptr<SurfaceSampler> fromSurface(const shared_ptr<Surface>& baseSurface);
    virtual ~SurfaceSampler() {}

    static Point3 barycentricSample(Random& r);
    Point3 triangleSample(const Point3& baryCoords, int triangleIndex);
    shared_ptr<Surfel> samplePoint(Random& r);
    double surfaceArea();
};

#endif
