/**
 @file   SurfaceSampler.cpp
 @author John Hughes
 @date   2011-04-07
 @edited 2011-04-07
*/

#include "SurfaceSampler.h"
#include "G3D/Random.h"

SurfaceSampler::SurfaceSampler(const shared_ptr<Surface>& base) : m_base(base) {    
    areaPrecompute();
}


shared_ptr<SurfaceSampler> SurfaceSampler::fromSurface(const shared_ptr<Surface>& baseSurface) {
    return shared_ptr<SurfaceSampler>(new SurfaceSampler(baseSurface));
}


Point3 SurfaceSampler::barycentricSample(Random& r){
    float x = r.uniform();
    float y = r.uniform();
    if (x < y) {
        x = 1.0f - x;
        y = 1.0f - y;
    }
    // w = x, v = y; yu = 1 - (x+y); 
    return Point3(x - y, y, 1.0f - x);
}


double SurfaceSampler::surfaceArea() {
    return m_area;
}
    

Point3 SurfaceSampler::triangleSample(const Point3& baryCoords, int triIndex) {
    const Tri& t = m_triArray[triIndex];
    const Point3& z = baryCoords[0] * t.vertex(m_vertexArray, 0).position + baryCoords[1] * t.vertex(m_vertexArray, 1).position + baryCoords[2] * t.vertex(m_vertexArray, 2).position;
    return z;
}


void SurfaceSampler::areaPrecompute() {
    double areaSoFar = 0.0;

    Surface::getTris(Array<shared_ptr<Surface>>(m_base), m_vertexArray, m_triArray);
    for (int i = 0; i < m_triArray.size(); ++i) {
        const Tri& t = m_triArray[i];
        double area = t.area();
        areaSoFar += area;
        m_triangleSummedAreaTable.append(areaSoFar);
    }
    m_area = areaSoFar; // total of all triangles
}


shared_ptr<Surfel> SurfaceSampler::samplePoint(Random& r) {
    // find a random point on triangle i, where 
    // a random number 0 <= x < totalArea
    // satisfies SAT(i-1) < x <= SAT(i)

    double x = r.uniform(0.0f, m_area);
    int k = m_triangleSummedAreaTable.size();
    // invariant: SAT(mini-1) <= x < SAT(maxi), so mini < maxi
    int mini = -1; // we (conceptually) enlarge SAT so that SAT(-1) = 0.  
    int maxi = k-1; 
    int split = mini + (1 + maxi - mini) / 2; // obsn: mini < split <= maxi.
    while ((maxi - mini) > 1) {
        if (x < m_triangleSummedAreaTable[split]) {
            maxi = split;
        } else {
            mini = split;
        }
        split = mini + 1 + (maxi - mini) / 2;
    }
    
    Tri::Intersector intersection;
    intersection.cpuVertexArray = &m_vertexArray;
    intersection.tri = &m_triArray[maxi];

    const Vector3& B = barycentricSample(r);
    intersection.u = B.x;
    intersection.v = B.y;
    intersection.backside = false;

    alwaysAssertM(maxi >= 0 && maxi < m_triArray.size(), format("Index out of bounds: maxi = %d, m_triArray.size() = %d", maxi, m_triArray.size()));
    const shared_ptr<Material>& m = m_triArray[maxi].material();
    return m->sample(intersection);
}
