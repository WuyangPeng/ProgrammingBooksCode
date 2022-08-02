#include "AreaLight.h"

AreaLight::AreaLight(void) {
}

shared_ptr<AreaLight> AreaLight::fromSampler(const shared_ptr<SurfaceSampler>& baseSampler, const Power3& power) {
    shared_ptr<AreaLight> s(new AreaLight());
    s->m_baseSampler = baseSampler;
    s->m_power = power; 

    return s;
}


Radiance3 AreaLight::radiance() {
    return m_power / (m_baseSampler->surfaceArea() * pif());
}


Radiance3 AreaLight::power() {
    return m_power;
}


shared_ptr<Surfel> AreaLight::samplePoint(Random& r) {
    return m_baseSampler->samplePoint(r);
}


