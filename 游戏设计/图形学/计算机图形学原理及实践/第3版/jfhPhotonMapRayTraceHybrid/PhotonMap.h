/**
  @file PhotonMap.h

 A class to represent a photon map, based on a fixed-radius gathering strategy. 
 The underlying structure is a PointHashGrid, which makes finding photons near a query-point
 very fast. 
 */
#ifndef PhotonMap_h
#define PhotonMap_h

#include "IPhoton.h"

class PhotonMap : 
    public PointHashGrid<IPhoton, IPhoton::PosFunc, EqualsTrait<IPhoton> >
{
private:
    float    m_gatherRadius; // radius we'll use for gathering photons

public:
    float kernel(Point3 center, Point3 sample);
    float gatherRadius();

    PhotonMap(float gatherRadius);
    ~PhotonMap(void);
};

#endif
