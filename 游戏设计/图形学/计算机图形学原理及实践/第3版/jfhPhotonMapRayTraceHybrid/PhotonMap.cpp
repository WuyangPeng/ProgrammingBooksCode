#include "PhotonMap.h"


PhotonMap::PhotonMap(float gatherRadius) 
    : PointHashGrid<IPhoton, IPhoton::PosFunc, EqualsTrait<IPhoton> >(gatherRadius), m_gatherRadius(gatherRadius)
{
}


PhotonMap::~PhotonMap(void)
{
}

/*
float PhotonMap::kernel(Point3 center, Point3 sample) {
    return (1.0f / (pif() * m_gatherRadius * m_gatherRadius));
}
*/

float PhotonMap::kernel(Point3 center, Point3 sample) {
    float r = (sample - center).length();
    float x = r / m_gatherRadius;
    float h = max(1.0f - x, 0.0f); 

    // Cone filter: the integral over the gather disk is 1/3 pi r^2,
    // so we must divide by that quantity to normalize the filter.
    return h * (3.0f / (pif() * m_gatherRadius * m_gatherRadius));
}

float PhotonMap::gatherRadius() {
    return m_gatherRadius;
}
