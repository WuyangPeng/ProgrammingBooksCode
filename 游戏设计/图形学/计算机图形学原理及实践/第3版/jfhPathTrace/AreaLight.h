/**
  @file AreaLight.h

 */
#ifndef AreaLight_h
#define AreaLight_h

#include <G3D/G3DAll.h>
#include "SurfaceSampler.h"

/**
  A class to represent area lights, given a mechanism for sampling 
  from the light. The light is assumed to be planar, so that no normal-interpolation is needed. 
*/
class AreaLight : public ReferenceCountedObject {
private:
    Power3                      m_power;

protected:

    shared_ptr<SurfaceSampler>  m_baseSampler;

    AreaLight();

public:

    static shared_ptr<AreaLight> fromSampler(const shared_ptr<SurfaceSampler>& baseSampler, const Power3& power);

    virtual ~AreaLight(){};

    shared_ptr<Surfel> samplePoint(Random& r);

    Radiance3 radiance();

    Power3    power();
};

#endif
